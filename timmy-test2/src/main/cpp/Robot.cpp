// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <iostream>
#include <math.h>

#include <frc/smartdashboard/SmartDashboard.h>

double deadzone = 0.01;
double triggerDeadzone = 0.01;
double maxSpeed = 0.6;

void Robot::RobotInit() {
	std::cout << "-- CJ Robot Program Start --" << std::endl;
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
	double leftJoy = -controller.GetRawAxis(1);
	double rightJoy = controller.GetRawAxis(3);

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

	int leftTrigger = controller.GetRawButton(1);
	int rightTrigger = controller.GetRawButton(3);

	int yButton = controller.GetRawButton(4);
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
	if (leftTrigger != 0) {
		flooper.Set(1);
	} else if (rightTrigger != 0) {
		flooper.Set(-1);
	} else {
		flooper.Set(0);
	}


	// spinner
	if (rBumper != 0) {
		spinner.Set(0.5);
	} else if (lBumper != 0) {
		spinner.Set(-0.5);
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
