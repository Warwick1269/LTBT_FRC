// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
#include "Drive.h"

#include <frc/smartdashboard/SmartDashboard.h>


double triggerDeadZone = 0.01;
// bool lock = false;
double flySpeed = 0;
double feedSpeed = 0.75;
bool latch = true;
void Robot::RobotInit() {
	std::cout << "-- LTBT Robot Program Start --" << std::endl;
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {
	using namespace std::this_thread;
	using namespace std::chrono;
	Drive newMec(0.02, 0.8);
	
	
	if (latch == true) 
	{
		newMec.TimedAutoMecDrive(500, 0.1, 0, 0, 0);
		newMec.TimedAutoMecDrive(500, -0.1, 0, 0, 0);
		newMec.TimedAutoMecDrive(500, 0, -0.1, 0, 0);
		newMec.TimedAutoMecDrive(500, 0, 0.1, 0, 0);

	
		latch = false;
	}
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
	// Note for Teleop, DONT USE FOR LOOPS OR WHILE LOOPS! (unless it is really fast / no sleep_for() in the loop) 
	// it will stay at the loop until it is completed (essentially freezing your robot).
	// Teleop is already called every cycle, so use this to your advantage instead of making loops yourself.


	using namespace frc;
	// create drive object	
	// DeadZone, MaxSpeed
	Drive newMec(0.02, 0.8);
	// call MecDrive for mecanum drive control
	newMec.MecDrive();


	int leftTrigger = controller.GetRawAxis(2);
	int rightTrigger = controller.GetRawAxis(3);

	int xButton = controller.GetRawButton(3);
	int bButton = controller.GetRawButton(2);
	int yButton = controller.GetRawButton(4);

	int lBumper = controller.GetRawButton(5);
	int rBumper = controller.GetRawButton(6);


	// Left drivetrain

		
	// Lifter
	//FINE TUNE DELAYS
	using namespace std::this_thread;
	using namespace std::chrono;
	
//sleep_set(nanoseconds())
 
	
	if (rightTrigger != 0) {
		lifter.Set(-0.7);
	} else if (leftTrigger != 0) {
		lifter.Set(0.7);
	} else {
		lifter.Set(0);
	}


	// feed wheel
	if (rBumper != 0) {
		feed.Set(feedSpeed);
	} else if (lBumper != 0) {
		feed.Set(-feedSpeed);
	} else {
		feed.Set(0);
	}
	// flywheel

	if (yButton !=0 && flySpeed <= 0.01){//on
	for (int i =0; i < 100; i++) {
		flySpeed += 0.01;
		flywheel.Set(-flySpeed);
		SmartDashboard::PutString("DB/String 0", "Spinning wheel");
		sleep_for(nanoseconds(50000000));
		if (flySpeed > 0.98) {
			SmartDashboard::PutString("DB/String 0", "Ready!");
		}
		if (bButton !=0) {
			break;
		}
	};

	} 
	else if (xButton !=0 && flySpeed <= 0.01) {
	for (int i =0; i < 60; i++) {
		flySpeed += 0.01;
		flywheel.Set(-flySpeed);
		SmartDashboard::PutString("DB/String 0", "Spinning wheel");
		sleep_for(nanoseconds(50000000));
		if (flySpeed > 0.58) {
			SmartDashboard::PutString("DB/String 0", "Ready!");
		}
		if (bButton !=0) {
			break;
		}
	};
			
	}

	else if (bButton !=0) {//off
		flywheel.Set(0);
		flySpeed = 0;
	}
	

}


void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {
	using namespace std::this_thread;
	using namespace std::chrono;
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
