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
#include <frc/filter/SlewRateLimiter.h>
#include <thread>
#include <chrono>


#include <frc/smartdashboard/SmartDashboard.h>


bool latch = true;
double maxSpeed = 0.5;
double speed = 0.5;
frc::SlewRateLimiter<units::scalar> filter{0.1 / 1_s};	
void Robot::RobotInit() {
	std::cout << "-- LTBT Robot Program Start --" << std::endl;
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() 
{
	Auto newAuto;

	

	newAuto.TimedAutoArmBendTwo(3000, -0.5);

	newAuto.TimedAutoIntake(2000, -0.5);

	newAuto.ArmStop();

	newAuto.TimedAutoMecDrive(1000, 0.0, -0.2, 0.0);
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
	// Drive newMec(0.02, 0.8);
	double joyYPower = joystick.GetY() * fabs(joystick.GetY());
	double joyZPower = joystick.GetZ() * fabs(joystick.GetZ());
	double joyXPower;

	if (joyYPower > 0.1)
	{
		joyXPower = joystick.GetX() * fabs(joystick.GetX()) * 0.15;
	}
	else
	{
		joyXPower = 0;
	}

	mec_drive.DriveCartesian(-joyZPower, joyYPower, joyXPower);

	// Create new arm object
	double _leftJoy = -controller.GetRawAxis(1); 

    double leftJoy = filter.Calculate(_leftJoy); 

	double _rightJoy = controller.GetRawAxis(5);
	int _bButton = controller.GetRawButton(2);


    double leftPower = leftJoy;
    double rightPower = _rightJoy;
    
    if (_bButton)
    {
        bendOne.Set(0);
		bendTwo.Set(0);
    }
    else
    {
        bendOne.Set(leftPower * maxSpeed);
        bendTwo.Set(rightPower * maxSpeed);
    }


    if (_rBumper)
    {
        intake1.Set(speed);
        intake2.Set(-speed);
    }
    if (_lBumper)
    {
        intake1.Set(-speed);
        intake2.Set(speed);
    }
    else
    {
        intake1.Set(0);
        intake2.Set(0);
    }

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
