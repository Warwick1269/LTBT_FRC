#include "Robot.h"
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
#include <frc/Joystick.h>

class Drive
{
private:
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
    Drive(/* args */);
    ~Drive();
};

Drive::Drive(/* args */)
{
    using namespace frc;
	using namespace std::this_thread;
	using namespace std::chrono;

	double leftJoy = -controller.GetRawAxis(1) * joySense;
	double rightJoy = controller.GetRawAxis(5) * joySense;

	// double leftPower = pow(leftJoy, 3);
	// double rightPower = pow(rightJoy, 3);

	double leftPower = leftJoy * fabs(leftJoy);
	double rightPower = rightJoy * fabs(rightJoy);

	// leftPower *= maxSpeed;
	// rightPower *= maxSpeed;

	if (fabs(leftPower) > maxSpeed) {
		if (leftPower < 0) {
			leftPower = -maxSpeed;
		} else {
			leftPower = maxSpeed;
		}
	};

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
