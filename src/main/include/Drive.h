#include "Robot.h"
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
#include <frc/Joystick.h>
#include <frc/drive/MecanumDrive.h>

class Drive
{
private:
	// Left
	WPI_VictorSPX frontL {1};
	WPI_VictorSPX backL {2};


	// Right
	WPI_VictorSPX frontR {3};
	WPI_VictorSPX backR {4};
	frc::Joystick controller{0};
	frc::Joystick joystick{1};

	frc::MecanumDrive mec_drive{frontL, backL, frontR, backR};

	// Controller
	double leftPower;
	double rightPower;
	double leftJoy;
	double rightJoy;
	double _joySense;

public:
    Drive(double joySense); // This is the constructor function, which is called when the class is instantiated
	void MecDrive(double deadZone, double maxSpeed); // Call this for MecunumDrive bases 
	void TrainDrive(double deadZone, double maxSpeed); // Call this for Drive Trains
	
	
};

