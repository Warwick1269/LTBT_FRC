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
    // Tuning vars:
    double deadZone = 0.01;
    double maxSpeed = 0.6;
    double joySense = 0.75;
	// Left
	WPI_VictorSPX frontL {1};
	WPI_VictorSPX backL {2};


	// Right
	WPI_VictorSPX frontR {3};
	WPI_VictorSPX backR {4};
	frc::Joystick controller{0};

	// Controller
	double leftPower;
	double rightPower;
	double leftJoy;
	double rightJoy;

public:
    Drive(); // This is the constructor function, which is called when the class is instantiated
	void MecDrive(double deadZone, double maxSpeed, double joySense); // Call this for MecunumDrive bases 
	void TrainDrive(double deadZone, double maxSpeed, double joySense); // Call this for Drive Trains
};

