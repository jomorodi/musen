/* Copyright (c) 2013-2020, MUSEN Development Team. All rights reserved.
   This file is part of MUSEN framework http://msolids.net/musen.
   See LICENSE file for license and warranty information. */

#pragma once

#define MDEM_FILE_VERSION 2		// Current version of .mdem-file (+quaternion, +stress tensor, -angles, -accelerations).

#define PI          3.14159265358979323846
#define PI_180      0.0174532925
#define _180_PI     57.295779579
#define _2_SQRT_5_6 1.825741858350553711523232609336

#define DEFAULT_MAX_CELLS 50

#define DEFAULT_ACTIVITY_END 1e+300

enum class ERunningStatus
{
	IDLE          = 0,
	RUNNING       = 1,
	TO_BE_STOPPED = 2,
	TO_BE_PAUSED  = 3,
	PAUSED        = 4,
	FAILED        = 5,
};

// **********       types of geometrical objects
#define UNKNOWN_OBJECT              0
#define SPHERE                      1
#define SOLID_BOND					9
#define LIQUID_BOND					13
#define TRIANGULAR_WALL				14

// Defines command delimiters and commands in structure file.
enum class ETXTCommands : unsigned
{
	OBJECT_ID                = 0,
	OBJECT_TYPE              = 1,
	OBJECT_TIME              = 2,
	OBJECT_GEOMETRY          = 5,
	OBJECT_ACCEL             = 10,
	OBJECT_ANGL_ACCEL        = 11,
	OBJECT_COORD             = 12,
	OBJECT_VELOCITY          = 15,
	OBJECT_ANG_VEL           = 16,
	OBJECT_ANGL              = 17,
	OBJECT_FORCE_AMPL        = 18,
	OBJECT_FORCE             = 20,
	SIMULATION_DOMAIN        = 22,
	OBJECT_COMPOUND_TYPE     = 23, // material type of the local object
	OBJECT_ACTIV_INTERV      = 24,
	GEOMETRY                 = 25,
	GEOMETRY_TDVEL           = 26,
	GEOMETRY_PLANES          = 27,
	PERIODIC_BOUNDARIES      = 28,
	ANISOTROPY               = 29,
	CONTACT_RADIUS           = 30,
	OBJECT_ORIENT            = 31,
	MATERIALS_COMPOUNDS      = 32,
	MATERIALS_INTERACTIONS   = 33,
	MATERIALS_MIXTURES       = 34,
	OBJECT_STRESS_TENSOR     = 36,
	OBJECT_TEMPERATURE       = 37,
	ANALYSIS_VOLUME          = 38,
	PACKAGE_GENERATOR        = 39,
	PACKAGE_GENERATOR_CONFIG = 40,
	BONDS_GENERATOR          = 41,
	OBJECT_PRINC_STRESS      = 42,
	OBJECT_TOT_TORQUE        = 43,
	OBJECT_PLANE_COORD       = 44,
	OBJECT_TANG_OVERLAP      = 45,
};

// ********* physical constants
#define GRAVITY_CONSTANT				9.81
#define ANGLE_GRAVITY_CONSTANT_PHI		0
#define ANGLE_GRAVITY_CONSTANT_THETA	0
#define ANGLE_GRAVITY_CONSTANT_PSI		0
#define BOLTZMANN_CONSTANT              1.38064852e-23
#define GAS_CONSTANT                    8.314462618 // [J/(mol*K)]

// ********* DEFAULT PARAMETERS
#define DEFAULT_SIMULATION_STEP 1e-6
#define DEFAULT_SAVING_STEP 1e-3
#define DEFAULT_END_TIME 1
