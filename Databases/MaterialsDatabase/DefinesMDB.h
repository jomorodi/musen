/* Copyright (c) 2013-2020, MUSEN Development Team. All rights reserved.
   This file is part of MUSEN framework http://msolids.net/musen.
   See LICENSE file for license and warranty information. */

#pragma once

#include <limits>

//////////////////////////////////////////////////////////////////////////
/// Correlations

enum class ECorrelationTypes : unsigned
{
	CONSTANT	= 0,	// y = k0
	LINEAR		= 1,	// y = k2*T + k1*P + k0
	EXPONENT_1	= 2,	// y = exp(k0 + k1 / (T + k2))
	POW_1		= 3,	// y = k0*(T)^k1
	UNDEFINED	= 31	//
};

#define _COR_CONSTANT_NAME		"Constant"
#define _COR_LINEAR_NAME		"Linear"
#define _COR_EXPONENT_1_NAME	"Exponential 1"
#define _COR_POW_1_NAME			"Power function 1"
#define _COR_UNDEFINED_NAME		"Undefined"

#define _COR_TYPES_NUMBER	4
#define _COR_TYPES			{ ECorrelationTypes::CONSTANT, ECorrelationTypes::LINEAR, ECorrelationTypes::EXPONENT_1, ECorrelationTypes::POW_1 }
#define _COR_TYPES_NAMES	{ _COR_CONSTANT_NAME, _COR_LINEAR_NAME, _COR_EXPONENT_1_NAME, _COR_POW_1_NAME }


//////////////////////////////////////////////////////////////////////////
/// Temperatures [K] and pressures [Pa]

#define DEFAULT_T1	0
#define DEFAULT_T2	500
#define DEFAULT_P1	0
#define DEFAULT_P2	1000000

#define NORMAL_TEMPERATURE	273.15
#define NORMAL_PRESSURE		101325

//////////////////////////////////////////////////////////////////////////
/// Default values

#define DEFAULT_CORR_VALUE		1
#define DEFAULT_MDB_FILE_NAME	"MASmaterials.mdb"

#define PROPERTY_UNDEFINED_TYPE				999
#define PROPERTY_UNDEFINED_NAME				"Undefined"
#define PROPERTY_UNDEFINED_UNITS			""
#define COMPOUND_UNDEFINED_NAME				"Unspecified"
#define COMPOUND_UNDEFINED_AUTHOR			"Unspecified"
#define MIXTURE_UNDEFINED_NAME				"Unspecified"
#define COMPOUND_FRACTION_UNDEFINED_NAME	"Unspecified"
#define COMPOUND_FRACTION_DEFAULT_DIAMETER	1e-3

//////////////////////////////////////////////////////////////////////////
/// Phases

#define COMPOUND_PHASE_LIQUID	0
#define COMPOUND_PHASE_VAPOR	1
#define COMPOUND_PHASE_SOLID	2
#define COMPOUND_PHASE_UNKNOWN	5

#define _PHASE_TYPE_DEFAULT		COMPOUND_PHASE_SOLID


//////////////////////////////////////////////////////////////////////////
///////// Properties

/// TP Properties
#define _TP_PROPERTIES_NUMBER	16

enum ETPPropertyTypes	// [0..99]
{
	PROPERTY_DENSITY = 0,
	PROPERTY_HEAT_CAPACITY = 1,
	PROPERTY_DYNAMIC_VISCOSITY = 2,
	PROPERTY_THERMAL_CONDUCTIVITY = 3,
	PROPERTY_SATURATED_VAPOR_PRESSURE = 4,
	PROPERTY_VAPOR_HEAT_CAPACITY = 5,
	PROPERTY_VAPORIZATION_ENTHALPY = 6,
	PROPERTY_YOUNG_MODULUS = 7,
	PROPERTY_NORMAL_STRENGTH = 8,
	PROPERTY_TANGENTIAL_STRENGTH = 9,
	PROPERTY_POISSON_RATIO = 10,
	PROPERTY_SURFACE_ENERGY = 11,
	PROPERTY_ATOMIC_VOLUME = 12,
	PROPERTY_SURFACE_TENSION = 13,
	PROPERTY_TIME_THERM_EXP_COEFF = 14,
	PROPERTY_YIELD_STRENGTH = 15,
	PROPERTY_NO_PROPERTY = 100
};

#define _MUSEN_ACTIVE_PROPERTIES { PROPERTY_DENSITY, PROPERTY_HEAT_CAPACITY, PROPERTY_DYNAMIC_VISCOSITY, PROPERTY_YOUNG_MODULUS, PROPERTY_NORMAL_STRENGTH, PROPERTY_TANGENTIAL_STRENGTH, PROPERTY_POISSON_RATIO, \
PROPERTY_SURFACE_ENERGY, PROPERTY_ATOMIC_VOLUME, PROPERTY_SURFACE_TENSION, PROPERTY_TIME_THERM_EXP_COEFF, PROPERTY_YIELD_STRENGTH }
#define _MUSEN_ACTIVE_INTERACTIONS { PROPERTY_RESTITUTION_COEFFICIENT, PROPERTY_STATIC_FRICTION, PROPERTY_ROLLING_FRICTION }

#define _TP_PROPERTIES { PROPERTY_DENSITY, PROPERTY_HEAT_CAPACITY, PROPERTY_DYNAMIC_VISCOSITY, PROPERTY_THERMAL_CONDUCTIVITY, PROPERTY_SATURATED_VAPOR_PRESSURE, \
	PROPERTY_VAPOR_HEAT_CAPACITY, PROPERTY_VAPORIZATION_ENTHALPY, PROPERTY_YOUNG_MODULUS, PROPERTY_NORMAL_STRENGTH,	PROPERTY_TANGENTIAL_STRENGTH, PROPERTY_POISSON_RATIO, PROPERTY_SURFACE_ENERGY, \
	PROPERTY_ATOMIC_VOLUME,	PROPERTY_SURFACE_TENSION, PROPERTY_TIME_THERM_EXP_COEFF, PROPERTY_YIELD_STRENGTH }

#define _DENSITY_NAME					"Density"
#define _HEAT_CAPACITY_NAME				"Heat capacity"
#define _VISCOSITY_NAME					"Dynamic viscosity"
#define _THERMAL_CONDUCTIVITY_NAME		"Thermal conductivity"
#define _SATURATED_VAPOR_PRESSURE_NAME	"Saturated vapor pressure"
#define _VAPOR_HEAT_CAPACITY_NAME		"Vapor heat capacity"
#define _VAPORIZATION_ENTHALPY_NAME		"Enthalpy of vaporization"
#define _YOUNG_MODULUS_NAME				"Young modulus"
#define _NORMAL_STRENGTH_NAME          	"Normal strength"
#define _TANGENTIAL_STRENGTH_NAME      	"Tangential strength"
#define _POISSON_RATIO_NAME            	"Poisson ratio"
#define _SURFACE_ENERGY_NAME           	"Surface energy"
#define _ATOMIC_VOLUME_NAME            	"Atomic volume"
#define _SURFACE_TENSION_NAME          	"Surface tension"
#define _TIME_THERM_EXP_COEFF          	"Time-related therm. exp. coeff."
#define _YIELD_STRENGTH					"Yield strength"

#define _TP_PROPERTIES_NAMES { _DENSITY_NAME, _HEAT_CAPACITY_NAME, _VISCOSITY_NAME, _THERMAL_CONDUCTIVITY_NAME, _SATURATED_VAPOR_PRESSURE_NAME, _VAPOR_HEAT_CAPACITY_NAME, \
	_VAPORIZATION_ENTHALPY_NAME, _YOUNG_MODULUS_NAME, _NORMAL_STRENGTH_NAME, _TANGENTIAL_STRENGTH_NAME, _POISSON_RATIO_NAME, _SURFACE_ENERGY_NAME, _ATOMIC_VOLUME_NAME, _SURFACE_TENSION_NAME, \
	_TIME_THERM_EXP_COEFF, _YIELD_STRENGTH }

#define _DENSITY_UNITS					"kg/m3"
#define _HEAT_CAPACITY_UNITS			"J/(kg*K)"
#define _VISCOSITY_UNITS				"Pa*s"
#define _THERMAL_CONDUCTIVITY_UNITS		"W/(m*K)"
#define _SATURATED_VAPOR_PRESSURE_UNITS	"Pa"
#define _VAPOR_HEAT_CAPACITY_UNITS		"J/(kg*K)"
#define _VAPORIZATION_ENTHALPY_UNITS	"J/kg"
#define _YOUNG_MODULUS_UNITS			"Pa"
#define _NORMAL_STRENGTH_UNITS          "Pa"
#define _TANGENTIAL_STRENGTH_UNITS      "Pa"
#define _POISSON_RATIO_UNITS            "-"
#define _SURFACE_ENERGY_UNITS           "J/m2"
#define _ATOMIC_VOLUME_UNITS            "m3/mol"
#define _SURFACE_TENSION_UNITS          "N/m"
#define _TIME_THERM_EXP_UNITS			"1/(K*s)"
#define _YIELD_UNITS					"Pa"

#define _TP_PROPERTIES_UNITS { _DENSITY_UNITS, _HEAT_CAPACITY_UNITS, _VISCOSITY_UNITS, _THERMAL_CONDUCTIVITY_UNITS, _SATURATED_VAPOR_PRESSURE_UNITS, _VAPOR_HEAT_CAPACITY_UNITS, \
	_VAPORIZATION_ENTHALPY_UNITS, _YOUNG_MODULUS_UNITS, _NORMAL_STRENGTH_UNITS, _TANGENTIAL_STRENGTH_UNITS, _POISSON_RATIO_UNITS, _SURFACE_ENERGY_UNITS, _ATOMIC_VOLUME_UNITS, _SURFACE_TENSION_UNITS, \
	 _TIME_THERM_EXP_UNITS, _YIELD_UNITS }

#define _DENSITY_DEFAULT					1000
#define _HEAT_CAPACITY_DEFAULT				1000
#define _VISCOSITY_DEFAULT					0.1
#define _THERMAL_CONDUCTIVITY_DEFAULT		0.5
#define _SATURATED_VAPOR_PRESSURE_DEFAULT	0
#define _VAPOR_HEAT_CAPACITY_DEFAULT		1000
#define _VAPORIZATION_ENTHALPY_DEFAULT		2260000
#define _YOUNG_MODULUS_DEFAULT				1e+09
#define _NORMAL_STRENGTH_DEFAULT			1e+07
#define _TANGENTIAL_STRENGTH_DEFAULT		1e+07
#define _POISSON_RATIO_DEFAULT				0.2
#define _SURFACE_ENERGY_DEFAULT				1
#define _ATOMIC_VOLUME_DEFAULT				2e-5
#define _SURFACE_TENSION_DEFAULT			0.7
#define _TIME_THERM_EXP_DEFAULT			    1.7e-5
#define _YIELD_DEFAULT						20e+9

#define _TP_PROPERTIES_DEFAULTS { _DENSITY_DEFAULT, _HEAT_CAPACITY_DEFAULT, _VISCOSITY_DEFAULT, _THERMAL_CONDUCTIVITY_DEFAULT, _SATURATED_VAPOR_PRESSURE_DEFAULT, _VAPOR_HEAT_CAPACITY_DEFAULT, \
	_VAPORIZATION_ENTHALPY_DEFAULT, _YOUNG_MODULUS_DEFAULT, _NORMAL_STRENGTH_DEFAULT, _TANGENTIAL_STRENGTH_DEFAULT, _POISSON_RATIO_DEFAULT, _SURFACE_ENERGY_DEFAULT, _ATOMIC_VOLUME_DEFAULT, \
	_SURFACE_TENSION_DEFAULT, _TIME_THERM_EXP_DEFAULT, _YIELD_DEFAULT }

/// Const Properties

#define _CONST_PROPERTIES_NUMBER	1

enum EConstPropertyTypes // [100..199]
{
	PROPERTY_MOLAR_MASS = 100
};

#define _CONST_PROPERTIES { PROPERTY_MOLAR_MASS }

#define _MOLAR_MASS_NAME	"Molar mass"

#define _CONST_PROPERTIES_NAMES { _MOLAR_MASS_NAME }

#define _MOLAR_MASS_UNITS	"kg/mol"

#define _CONST_PROPERTIES_UNITS { _MOLAR_MASS_UNITS }

#define _MOLAR_MASS_DEFAULT	0.018

#define _CONST_PROPERTIES_DEFAULTS { _MOLAR_MASS_DEFAULT }

/// Interaction Properties

#define _INT_PROPERTIES_NUMBER	5

enum EIntPropertyTypes	// [200..299]
{
	PROPERTY_RESTITUTION_COEFFICIENT = 200,
	PROPERTY_STATIC_FRICTION         = 201,
	PROPERTY_ROLLING_FRICTION        = 202,
	PROPERTY_CONTACT_ANGLE           = 203,	/// Contact angle between liquid and solid surfaces.
	PROPERTY_DIFFUSION_COEFFICIENT   = 204,	/// Proportionality constant between the molar flux due to molecular diffusion and the gradient in the concentration of the species.
	PROPERTY_INT_NO_PROPERTY         = 300
};

#define _INT_PROPERTIES { PROPERTY_RESTITUTION_COEFFICIENT, PROPERTY_STATIC_FRICTION, PROPERTY_ROLLING_FRICTION, PROPERTY_CONTACT_ANGLE, PROPERTY_DIFFUSION_COEFFICIENT }

#define _RESTITUTION_COEFFICIENT_NAME	"Restitution coefficient"
#define _STATIC_FRICTION_NAME			"Sliding friction"
#define _ROLLING_FRICTION_NAME			"Rolling friction"
#define _CONTACT_ANGLE_NAME				"Contact angle"
#define _DIFFUSION_COEFFICIENT_NAME		"Diffusion coefficient"

#define _INT_PROPERTIES_NAMES { _RESTITUTION_COEFFICIENT_NAME, _STATIC_FRICTION_NAME, _ROLLING_FRICTION_NAME, _CONTACT_ANGLE_NAME, _DIFFUSION_COEFFICIENT_NAME }

#define _RESTITUTION_COEFFICIENT_UNITS	"-"
#define _STATIC_FRICTION_UNITS			"-"
#define _ROLLING_FRICTION_UNITS			"-"
#define _CONTACT_ANGLE_UNITS			"Deg"
#define _DIFFUSION_COEFFICIENT_UNITS	"m2/s"

#define _INT_PROPERTIES_UNITS { _RESTITUTION_COEFFICIENT_UNITS, _STATIC_FRICTION_UNITS, _ROLLING_FRICTION_UNITS, _CONTACT_ANGLE_UNITS, _DIFFUSION_COEFFICIENT_UNITS }

#define _RESTITUTION_COEFFICIENT_DEFAULT	0.6
#define _STATIC_FRICTION_DEFAULT			0.45
#define _ROLLING_FRICTION_DEFAULT			0.05
#define _CONTACT_ANGLE_DEFAULT				45
#define _DIFFUSION_COEFFICIENT_DEFAULT		2e-9

#define _INT_PROPERTIES_DEFAULTS { _RESTITUTION_COEFFICIENT_DEFAULT, _STATIC_FRICTION_DEFAULT, _ROLLING_FRICTION_DEFAULT, _CONTACT_ANGLE_DEFAULT, _DIFFUSION_COEFFICIENT_DEFAULT }

//////////////////////////////////////////////////////////////////////////
/// Other

#define _NOT_A_NUMBER std::numeric_limits<double>::quiet_NaN()