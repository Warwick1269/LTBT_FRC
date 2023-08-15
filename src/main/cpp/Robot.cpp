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
#include "Auto.h"
#include "Arm.h"

#include <frc/smartdashboard/SmartDashboard.h>


bool latch = true;
void Robot::RobotInit() {
	std::cout << "-- LTBT Robot Program Start --" << std::endl;
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() 
{
	Auto newAuto;

	newAuto.TimedAutoMecDrive(1000, 0, 0.1, 0, 0);

	// newAuto.TimedAutoArmBendTwo(1000, 0.1);
	newAuto.TimedAutoIntake(2000, 0.75);
}

void Robot::AutonomousPeriodic() 
{
	// Auto newAuto;
	
	
	// if (latch == true) 
	// {	
	// 	newAuto.TimedAutoMecDrive(1000, 0, 0.1, 0, 0);

	// 	latch = false;

	// }

}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() 
{
	// Note for Teleop, DONT USE FOR LOOPS OR WHILE LOOPS! (unless it is really fast / no sleep_for() in the loop) 
	// it will stay at the loop until it is completed (essentially freezing your robot).
	// Teleop is already called every cycle, so use this to your advantage.


	using namespace frc;
	// create drive object	
	// DeadZone, MaxSpeed
	Drive newMec(0.02, 0.8);
	// // call MecDrive for mecanum drive control
	newMec.MecDrive();

	// Create new arm object
	Arm newArm;

	// Drive bend one
	newArm.ArmBendOne(0.5, 0.5);
	// Drive bend two
	newArm.ArmBendTwo(0.5, 0.5);
	// Drive intake
	newArm.Intake(0.75);



}


void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() 
{
  return frc::StartRobot<Robot>();
}
#endif
