// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>

#include <frc/smartdashboard/SmartDashboard.h>


double deadzone = 0.01;
double triggerDeadzone = 0.01;
double maxSpeed = 0.6;
// bool lock = false;
double flyspeed = 0;

void Robot::RobotInit() {
	std::cout << "-- CJ Robot Program Start --" << std::endl;
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {
	using namespace std::this_thread;
	using namespace std::chrono;
	

	
	frontL.Set(0.3);
	backL.Set(0.3);
	frontR.Set(-0.3);
	backR.Set(-0.3);

	sleep_for(nanoseconds(1000000000));
	// delay 1 sec
	frontL.Set(0);
	backL.Set(0);
	frontR.Set(0);
	backR.Set(0);
		
	flywheel.Set(1);

	sleep_for(nanoseconds(2000000000)); // conversion is 1000,000,000n = 1s
	//delay 2 sec

	feed.Set(0.9);

	
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
	double leftJoy = -controller.GetRawAxis(1);
	double rightJoy = controller.GetRawAxis(5);

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
	} 

	if (fabs(rightPower) > maxSpeed) {
		if (rightPower < 0) {
			rightPower = -maxSpeed;
		} else {
			rightPower = maxSpeed;
		}
	}

	int leftTrigger = controller.GetRawAxis(2);
	int rightTrigger = controller.GetRawAxis(3);

	int xButton = controller.GetRawButton(3);
	int bButton = controller.GetRawButton(2);

	int lBumper = controller.GetRawButton(5);
	int rBumper = controller.GetRawButton(6);

	int fwheelspeed = 0;

	// Left drivetrain
	if (fabs(leftJoy) > deadzone) {
		frontL.Set(leftPower);
		backL.Set(leftPower);
	} else {
		frontL.Set(0);
		backL.Set(0);
	}

	// right drivetrain
	if (fabs(rightJoy) > deadzone) {
		frontR.Set(rightPower);
		backR.Set(rightPower);
	} else {
		frontR.Set(0);
		backR.Set(0);
	}

		
	// Lifter
	//FINE TUNE DELAYS
	using namespace std::this_thread;
	using namespace std::chrono;
	
//sleep_set(nanoseconds())
 
	
	if (rightTrigger != 0) {
		lifter.Set(0.9);
	} else if (leftTrigger != 0) {
		lifter.Set(-0.9);
	} else {
		lifter.Set(0);
	}


	// feed wheel
	if (rBumper != 0) {
		feed.Set(0.7);
	} else if (lBumper != 0) {
		feed.Set(-0.7);
	} else {
		feed.Set(0);
	}
	// flywheel
	if (bButton !=0){//on
		for (int i =0; i < 100; i++) {
			flyspeed += 0.01;
			flywheel.Set(-flyspeed);
			sleep_for(nanoseconds(100000000));
		};
		

	} else if (xButton !=0) {//off
		flywheel.Set(0);
		flyspeed = 0;
	}
	

}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {
	using namespace std::this_thread;
	using namespace std::chrono;
	// test and debug code
	frontL.Set(0.3); //left on
	backL.Set(0.3);
	sleep_for(nanoseconds(2000000000)); //2s
	frontL.Set(0); //left off
	backL.Set(0);
	sleep_for(nanoseconds(2000000000)); //2s break
	frontR.Set(0.3); //right on
	backR.Set(0.3);
	sleep_for(nanoseconds(2000000000)); //2s
	frontR.Set(0); //right off
	backR.Set(0);
	sleep_for(nanoseconds(2000000000)); //2s break
	flywheel.Set(1); //flywheel on
	sleep_for(nanoseconds(2000000000)); //2s
	flywheel.Set(0); //flywheel off
	sleep_for(nanoseconds(2000000000)); //2s break
	lifter.Set(1); //lifter on
	sleep_for(nanoseconds(2000000000)); //2s
	lifter.Set(0); //lifter off
	sleep_for(nanoseconds(2000000000)); //2s break
	feed.Set(0.3); //feed on
	sleep_for(nanoseconds(2000000000)); //2s
	feed.Set(0); //feed off
	sleep_for(nanoseconds(2000000000)); //2s break
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
