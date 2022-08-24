// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>

// #include <frc/smartdashboard/SmartDashboard.h>


double deadzone = 0.01;
double triggerDeadzone = 0.01;
double maxSpeed = 0.6;
bool lock = false;
void Robot::RobotInit() {
	std::` << "-- CJ Robot Program Start --" << std::endl;
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

	sleep_for(nanoseconds(10000000));
	frontL.Set(0);
	backL.Set(0);
	frontR.Set(0);
	backR.Set(0);
	
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

	int yButton = controller.GetRawButton(1);
	int aButton = controller.GetRawButton(2);

	int lBumper = controller.GetRawButton(5);
	int rBumper = controller.GetRawButton(6);

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

		
	// Flooper
	//FINE TUNE DELAYS
	using namespace std::this_thread;
	using namespace std::chrono;
	
//sleep_set(nanoseconds())
 
	
	if (rightTrigger != 0) {
		flooper.Set(0.4);
		sleep_for(nanoseconds(2000000000));
		flooper.Set(0);
		lock = true;
	
		
	}
	if (leftTrigger != 0) {
		if (lock == true)
		{
			flooper.Set(-0.3);
			sleep_for(nanoseconds(200000000));
			flooper.Set(0);
			lock = false;
		}
		
	} 


	// spinner
	if (rBumper != 0) {
		spinner.Set(0.7);
	} else if (lBumper != 0) {
		spinner.Set(-0.7);
	} else {
		spinner.Set(0);
	}


	// climber
	if (yButton != 0) {
		climber.Set(1);
	} else if (aButton != 0) {
		climber.Set(-1);
	} else {
		climber.Set(0);
	}
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
