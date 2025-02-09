/* Copyright (c) 2013-2020, MUSEN Development Team. All rights reserved.
   This file is part of MUSEN framework http://msolids.net/musen.
   See LICENSE file for license and warranty information. */

#include "ModelSBThermal.h"

CModelSBThermal::CModelSBThermal()
{
	m_name = "Thermal bond";
	m_uniqueKey = "0CA458A6CCEF45C09BECD0D49306B86D";
	m_helpFileName = "/Solid Bond/Thermal.pdf";

	AddParameter("THERM_DIFF", "Temp. difference [K]", 800);
	AddParameter("MU", "MU", 1);
	m_hasGPUSupport = true;
}

void CModelSBThermal::CalculateSBForce(double _time, double _timeStep, size_t _iLeft, size_t _iRight, size_t _iBond, SSolidBondStruct& _bonds, unsigned* _pBrockenBondsNum)   const
{
	double  deltaT = m_parameters[0].value;

	// relative angle velocity of contact partners
	CVector3 relAngleVel = Particles().AnglVel(_iLeft) - Particles().AnglVel(_iRight);

	// the bond in the global coordinate system
	CVector3 currentBond = GetSolidBond(Particles().Coord(_iRight), Particles().Coord(_iLeft), m_PBC);
	double dDistanceBetweenCenters = currentBond.Length();
	CVector3	rAC = currentBond * 0.5;

	// !! do not delete source equation
	//relativeVelocity = (m_ParticleVelocities[ nLeftParticleID ]-m_ParticleAnglVel[ nLeftParticleID ]*rAC)
	//	- ( m_ParticleVelocities[ nRightParticleID ] + m_ParticleAnglVel[ nRightParticleID ]*rAC);

	// optimized
	CVector3 sumAngleVelocity = Particles().AnglVel(_iLeft) + Particles().AnglVel(_iRight);
	CVector3 relativeVelocity = Particles().Vel(_iLeft) - Particles().Vel(_iRight) - sumAngleVelocity * rAC;

	CVector3 currentContact = currentBond / dDistanceBetweenCenters;
	CVector3 tempVector = _bonds.PrevBond(_iBond)*currentBond;

	CVector3 Phi = currentContact * (DotProduct(sumAngleVelocity, currentContact)*_timeStep*0.5);

	CMatrix3 M(1 + tempVector.z*Phi.z + tempVector.y*Phi.y, Phi.z - tempVector.z - tempVector.y*Phi.x, -Phi.y - tempVector.z*Phi.x + tempVector.y,
		tempVector.z - Phi.z - tempVector.x*Phi.y, tempVector.z*Phi.z + 1 + tempVector.x*Phi.x, -tempVector.z*Phi.y + Phi.x - tempVector.x,
		-tempVector.y - tempVector.x*Phi.z + Phi.y, -tempVector.y*Phi.z + tempVector.x - Phi.x, tempVector.y*Phi.y + tempVector.x*Phi.x + 1);

	CVector3 normalVelocity = currentContact * DotProduct(currentContact, relativeVelocity);
	CVector3 tangentialVelocity = relativeVelocity - normalVelocity;

	// normal angle velocity
	CVector3 normalAngleVel = currentContact * DotProduct(currentContact, relAngleVel);
	CVector3 tangAngleVel = relAngleVel - normalAngleVel;

	// calculate the force
	double dInitLength = _bonds.InitialLength(_iBond)*(1 + deltaT * _bonds.TimeThermExpCoeff(_iBond)*_time);
	double dStrainTotal = (dDistanceBetweenCenters - dInitLength) / dInitLength;

	CVector3 vNormalForce = currentContact * (-1 * _bonds.CrossCut(_iBond)*_bonds.NormalStiffness(_iBond)*dStrainTotal);
	double dMu = m_parameters[1].value;

	CVector3 vDampingForce = -dMu * normalVelocity*_bonds.CrossCut(_iBond)*_bonds.NormalStiffness(_iBond)*fabs(dStrainTotal);
	if (vDampingForce.Length() > vNormalForce.Length())
		vDampingForce *= vNormalForce.Length() / vDampingForce.Length();
	vNormalForce += vDampingForce;

	_bonds.TangentialOverlap(_iBond) = M * _bonds.TangentialOverlap(_iBond) - tangentialVelocity * _timeStep;
	_bonds.TangentialForce(_iBond) = _bonds.TangentialOverlap(_iBond)*(_bonds.TangentialStiffness(_iBond)*_bonds.CrossCut(_iBond) / _bonds.InitialLength(_iBond));
	CVector3 vDampingTangForce = -dMu * tangentialVelocity*_bonds.TangentialOverlap(_iBond)*(_bonds.TangentialStiffness(_iBond)*_bonds.CrossCut(_iBond) / _bonds.InitialLength(_iBond));
	if (vDampingTangForce.Length() > _bonds.TangentialForce(_iBond).Length())
		vDampingTangForce *= _bonds.TangentialForce(_iBond).Length() / vDampingTangForce.Length();
	_bonds.TangentialForce(_iBond) += vDampingTangForce;

	_bonds.NormalMoment(_iBond) = M * _bonds.NormalMoment(_iBond) - normalAngleVel * (_timeStep* 2 * _bonds.AxialMoment(_iBond)*_bonds.TangentialStiffness(_iBond) / _bonds.InitialLength(_iBond));
	_bonds.TangentialMoment(_iBond) = M * _bonds.TangentialMoment(_iBond) - tangAngleVel * (_timeStep*_bonds.NormalStiffness(_iBond)*_bonds.AxialMoment(_iBond) / _bonds.InitialLength(_iBond));
	_bonds.TotalForce(_iBond) = vNormalForce + _bonds.TangentialForce(_iBond);

	_bonds.UnsymMoment(_iBond) = rAC * _bonds.TangentialForce(_iBond);
	_bonds.PrevBond(_iBond) = currentBond;

	// check the bond destruction
	double dForceLength = vNormalForce.Length();
	if (dStrainTotal <= 0)	// compression
		dForceLength *= -1;
	double dMaxStress = dForceLength / _bonds.CrossCut(_iBond) + _bonds.TangentialMoment(_iBond).Length()*_bonds.Diameter(_iBond) / (2 * _bonds.AxialMoment(_iBond));
	double dMaxTorque = _bonds.TangentialForce(_iBond).Length() / _bonds.CrossCut(_iBond) + _bonds.NormalMoment(_iBond).Length()*_bonds.Diameter(_iBond) / (2 * 2 * _bonds.AxialMoment(_iBond));

	if (( dMaxStress >= _bonds.NormalStrength(_iBond) ) || ( dMaxTorque >= _bonds.TangentialStrength(_iBond)))
	{
		_bonds.Active(_iBond) = false;
		_bonds.EndActivity(_iBond) = _time;
		*_pBrockenBondsNum += 1;
	}
}

