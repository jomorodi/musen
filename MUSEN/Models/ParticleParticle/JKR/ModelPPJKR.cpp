/* Copyright (c) 2013-2020, MUSEN Development Team. All rights reserved.
   This file is part of MUSEN framework http://msolids.net/musen.
   See LICENSE file for license and warranty information. */

#include "ModelPPJKR.h"

CModelPPJKR::CModelPPJKR()
{
	m_name = "JKR";
	m_uniqueKey = "8AC39F3E9D054A548CEB9CD44ACFE751";
	m_helpFileName = "/Contact Models/JKR.pdf";

	m_hasGPUSupport = true;
}

void CModelPPJKR::CalculatePPForce(double _time, double _timeStep, size_t _iSrc, size_t _iDst, const SInteractProps& _interactProp, SCollision* _pCollision) const
{
	const CVector3 srcAnglVel   = Particles().AnglVel(_iSrc);
	const CVector3 dstAnglVel   = Particles().AnglVel(_iDst);
	const double dPartSrcRadius = Particles().Radius(_iSrc);
	const double dPartDstRadius = Particles().Radius(_iDst);

	const CVector3 vRcSrc        = _pCollision->vContactVector * ( dPartSrcRadius / (dPartSrcRadius + dPartDstRadius));
	const CVector3 vRcDst        = _pCollision->vContactVector * (-dPartDstRadius / (dPartSrcRadius + dPartDstRadius));
	const CVector3 vNormalVector = _pCollision->vContactVector.Normalized();

	// relative velocity (normal and tangential)
	const CVector3 vRelVel       = Particles().Vel(_iDst) + dstAnglVel * vRcDst - (Particles().Vel(_iSrc) + srcAnglVel * vRcSrc);
	const double   dRelVelNormal = DotProduct(vNormalVector, vRelVel);
	const CVector3 vRelVelNormal = dRelVelNormal * vNormalVector;
	const CVector3 vRelVelTang   = vRelVel - vRelVelNormal;

	// normal and tangential overlaps
	const double dContactRadius = std::sqrt(_pCollision->dNormalOverlap * _pCollision->dEquivRadius);

	// normal force with damping
	const double Kn = 2 * _interactProp.dEquivYoungModulus * dContactRadius;
	const double dNormalForce = -1 * (4. * std::pow(dContactRadius, 3.) * _interactProp.dEquivYoungModulus / (3. * _pCollision->dEquivRadius) -
		std::sqrt(8 * PI * _interactProp.dEquivYoungModulus * _interactProp.dEquivSurfaceEnergy * std::pow(dContactRadius, 3.)));
	const double dDampingForce = -1.8257 * _interactProp.dAlpha * dRelVelNormal * std::sqrt(Kn * _pCollision->dEquivMass);

	// increment of tangential force with damping
	const double Kt = 8 *  _interactProp.dEquivShearModulus * dContactRadius;
	const CVector3 vDampingTangForce = vRelVelTang * (-1.8257 * _interactProp.dAlpha * std::sqrt(Kt * _pCollision->dEquivMass));

	// rotate old tangential force
	CVector3 vTangOverlap = _pCollision->vTangOverlap - vNormalVector * DotProduct(vNormalVector, _pCollision->vTangOverlap);
	if (vTangOverlap.IsSignificant())
		vTangOverlap = vTangOverlap * _pCollision->vTangOverlap.Length() / vTangOverlap.Length();
	_pCollision->vTangOverlap = vTangOverlap + vRelVelTang * _timeStep;

	CVector3 vTangForce = _pCollision->vTangOverlap * Kt;

	// check slipping condition
	const double dNewTangForce = vTangForce.Length();
	if (dNewTangForce > _interactProp.dSlidingFriction * std::abs(dNormalForce))
	{
		vTangForce = vTangForce * _interactProp.dSlidingFriction * std::abs(dNormalForce) / dNewTangForce;
		_pCollision->vTangOverlap = vTangForce / Kt;
	}
	else
		vTangForce += vDampingTangForce;

	// calculate rolling friction
	const CVector3 vRollingTorque1 = srcAnglVel.IsSignificant() ? // if it is not zero, but small enough, its Length() can turn into zero and division fails
		srcAnglVel * (-_interactProp.dRollingFriction * std::abs(dNormalForce) * dPartSrcRadius / srcAnglVel.Length()) : CVector3{ 0 };
	const CVector3 vRollingTorque2 = dstAnglVel.IsSignificant() ? // if it is not zero, but small enough, its Length() can turn into zero and division fails
		dstAnglVel * (-_interactProp.dRollingFriction * std::abs(dNormalForce) * dPartDstRadius / dstAnglVel.Length()) : CVector3{ 0 };

	// calculate moment of TangForce
	const CVector3 vMoment1 = vNormalVector * _pCollision->vTangForce * dPartSrcRadius + vRollingTorque1;
	const CVector3 vMoment2 = vNormalVector * _pCollision->vTangForce * dPartDstRadius + vRollingTorque2;

	_pCollision->vTangForce     = vTangForce;
	_pCollision->vTotalForce    = vNormalVector * (dNormalForce + dDampingForce) + _pCollision->vTangForce;
	_pCollision->vResultMoment1 = vMoment1;
	_pCollision->vResultMoment2 = vMoment2;
}
