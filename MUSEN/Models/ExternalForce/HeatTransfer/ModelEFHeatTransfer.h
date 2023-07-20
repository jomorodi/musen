/* Copyright (c) 2023, MUSEN Development Team. All rights reserved.
   This file is part of MUSEN framework http://msolids.net/musen.
   See LICENSE file for license and warranty information. */

#pragma once

#include "AbstractDEMModel.h"

class CModelEFHeatTransfer : public CExternalForceModel
{
public:
	CModelEFHeatTransfer();

	void CalculateEF(double _time, double _timeStep, size_t _iPart, SParticleStruct& _particles) const override;

	void SetParametersGPU(const std::vector<double>& _parameters, const SPBC& _pbc) override;
	void CalculateEFGPU(double _time, double _timeStep, SGPUParticles& _particles) override;
};