#include "Robot.h"
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
#include <frc/Joystick.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>

// This is the class containing all the drive functions and *exposed* variables.
// Drive constructor: joySense is the speed multiplier or joystick sensitivity; suggested 0.6, deadZone is 0.015 suggested, maxSpeed is 0.9 suggested; is between 0-1.
// arguments in order: joySense, deadZone, maxSpeed
class Drive
{
private:
	// Left
	WPI_VictorSPX frontL {1};
	WPI_VictorSPX backL {2};


	// Right
	WPI_VictorSPX frontR {3};
	WPI_VictorSPX backR {4};

	// controller declarations
	frc::Joystick controller{0};
	frc::Joystick joystick{1};

	// Drive train	
	frc::MotorControllerGroup m_left{frontL, backL};
	frc::MotorControllerGroup m_right{frontR, backR};
	frc::DifferentialDrive m_drive{m_left, m_right};

	// Mecanum Drive
	frc::MecanumDrive mec_drive{frontL, backL, frontR, backR};
	double _manualGyro = 0;


	// Other
	double _deadZone;
	double _maxSpeed;
	double _joySense;

public:
    Drive(double joySense, double deadZone, double maxSpeed); // This is the constructor function, which is called when the class is instantiated
	void MecDrive(); // Call this for MecunumDrive bases 
	void TrainDrive(); // Call this for Drive Trains

	
	
};

