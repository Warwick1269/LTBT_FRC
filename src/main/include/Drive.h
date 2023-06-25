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
public:
    Drive(double deadZone, double maxSpeed, double joySense);
    ~Drive();
};

Drive::Drive(double deadZone, double maxSpeed, double joySense)
{
    using namespace frc;

	double leftJoy = -controller.GetRawAxis(1); 
	double rightJoy = controller.GetRawAxis(5);

	// Squares joystick intensity for better control, 
	//while keeping sign (neg and pos)
	double leftPower = leftJoy * fabs(leftJoy) * joySense;
	double rightPower = rightJoy * fabs(rightJoy) * joySense;

	// leftPower *= maxSpeed;
	// rightPower *= maxSpeed;

	if (fabs(leftPower) > maxSpeed) {
		if (leftPower < 0) {
			leftPower = -maxSpeed;
		} else {
			leftPower = maxSpeed;
		}
	}

	if (fabs(rightPower) > maxSpeed) {
		if (rightPower < 0) {
			rightPower = -maxSpeed;
		} else {
			rightPower = maxSpeed;
		}
	}

	if (fabs(leftJoy) > deadZone) {
		frontR.Set(leftPower);
		backR.Set(leftPower);
	} else {
		frontR.Set(0);
		backR.Set(0);
	}

	// right drivetrain
	if (fabs(rightJoy) > deadZone) {
		frontL.Set(rightPower);
		backL.Set(rightPower);
	} else {
		frontL.Set(0);
		backL.Set(0);
	}
}

Drive::~Drive()
{
}
