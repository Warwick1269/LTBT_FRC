// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <math.h>

#include <frc/smartdashboard/SmartDashboard.h>
// Variables:
double deadzone = 0.01;
double triggerDeadzone = 0.01;
double maxSpeed = 0.6;
bool Shoot_toggle = false;//moved up here


void Robot::RobotInit() {
	std::cout << "-- CJ Robot Program Start --" << std::endl;
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
	

}

void Robot::AutonomousPeriodic() {
	using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;
	using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

	frontL.Set(-1);
	backL.Set(1);
	sleep_for(seconds(10)); // nanoseconds changed to seconds.
	frontL.Set(0);
	backL.Set(0);
	spinner.Set(0.5);
	load.Set(1);
	sleep_for(seconds(3)); // nanoseconds changed to seconds.
	spinner.Set(0);
	load.Set(0);  
						

}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
	using namespace std::this_thread;     // sleep_for, sleep_until
    using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
    using std::chrono::system_clock;
	using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
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

	int LeftBumper = controller.GetRawButton(5);
	int rightBumper = controller.GetRawButton(6);

	int yButton = controller.GetRawButton(4);
	int aButton = controller.GetRawButton(2);
	int xButton = controller.GetRawButton(1);

	//int lShoot = controller.GetRawButton(5);
	//int rShoot = controller.GetRawButton(6);

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
	// intake  
	if (LeftBumper != 0) {
		intake.Set(1);
	} else if (rightBumper != 0) {
		intake.Set(-1);
	} else {
		intake.Set(0);
	}
	int buttonState;
	int lastButtonState;
	// read the pushbutton input pin:
  	buttonState = aButton;

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (Shoot_toggle != true) {
		Shoot_toggle = true;
	}
	sleep_for(milliseconds(500));
	if (Shoot_toggle != false) {
		Shoot_toggle = false;
	}
    // Delay a little bit to avoid bouncing
    sleep_for(milliseconds(50));
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState; //have to test this code to know if it works.
	// spinner be shoot
	// make toggle-able [ ]
	//A turns the spinner on when pressed, then turns it off when pressed again
	// have two separate if statments, one takes an input from the controller setting SHoot_toggle 'true' and the other reads Shoot_toggle stting the 'spinner's' speed
	if (Shoot_toggle) {
		spinner.Set(0.5);
	}
	else {
		spinner.Set(0);
	}
	


	// load
	if (yButton != 0) {
		load.Set(1);
	} else if (xButton != 0) {
		load.Set(-1);
	} else {
		load.Set(0);
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
