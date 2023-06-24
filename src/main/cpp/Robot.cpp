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


double deadZone = 0.01;
double triggerDeadZone = 0.01;
double maxSpeed = 0.6;
// bool lock = false;
double flySpeed = 0;
double feedSpeed = 0.75;
bool latch = true;
double sens = 0.75;
void Robot::RobotInit() {
	std::cout << "-- LTBT Robot Program Start --" << std::endl;
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}

void Robot::AutonomousPeriodic() {
	using namespace std::this_thread;
	using namespace std::chrono;
	
	if (latch == true) {
	
	frontL.Set(0.3);
	backL.Set(0.3);
	frontR.Set(-0.3);
	backR.Set(-0.3);
	lifter.Set(-0.7);

	sleep_for(nanoseconds(3000000000));
	// delay 1 sec
	frontL.Set(0);
	backL.Set(0);
	frontR.Set(0);
	backR.Set(0);
	lifter.Set(0);
		
	for (int i =0; i < 90; i++) {
		flySpeed += 0.01;
		flywheel.Set(-flySpeed);
		sleep_for(nanoseconds(100000000));
	};
	sleep_for(nanoseconds());
	feed.Set(feedSpeed);
	lifter.Set(-0.7);

	sleep_for(nanoseconds(700000000));
	flySpeed = 0;
	feed.Set(0);
	flywheel.Set(0);
	lifter.Set(0);
	latch = false;

	}
}

void Robot::TeleopInit() {
}

void Robot::TeleopPeriodic() {
	using namespace frc;

	int leftTrigger = controller.GetRawAxis(2);
	int rightTrigger = controller.GetRawAxis(3);

	int xButton = controller.GetRawButton(3);
	int bButton = controller.GetRawButton(2);
	int yButton = controller.GetRawButton(4);

	int lBumper = controller.GetRawButton(5);
	int rBumper = controller.GetRawButton(6);

	int fwheelspeed = 0;

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
