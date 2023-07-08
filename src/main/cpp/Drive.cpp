#include "Drive.h"
#include <frc/filter/SlewRateLimiter.h>
#include <thread>
#include <chrono>

Drive::Drive(double deadZone, double maxSpeed)
{
	// assign arguments to private variables (hance the underscores)
	_deadZone = deadZone;
	_maxSpeed = maxSpeed;

	// Set DeadZones for MecanumDrive and DriveTrain	
	mec_drive.SetDeadband(deadZone);
	tank_drive.SetDeadband(deadZone);
	
	// Set MaxOutput for MecanumDrive and DriveTrain
	mec_drive.SetMaxOutput(maxSpeed);
	tank_drive.SetMaxOutput(maxSpeed);
	

}

void Drive::MecDrive()
{
	//NOTE: You need to create a new SlewRateLimiter for each value you want to smooth. 
	//They will collide if you use the same SlewRateLimiter for multiple values.

	// Smooth the joystick Y for every unit of time
	frc::SlewRateLimiter<units::scalar> filterY{0.5 / 1_s};	
	// Smooth the joystick X for every unit of time
	frc::SlewRateLimiter<units::scalar> filterX{0.5 / 1_s};

	//Applies the slew rate limiter
	double joyY = filterY.Calculate(-joystick.GetY());
	double joyX = filterX.Calculate(-joystick.GetX());

	// squares joystick intensity for finer control. This is not done for mecanum drive but is automatically done for drive train
	double joyYPower = joyY * fabs(joyY);
	double joyXPower = joyX * fabs(joyX);
	
	// y speed, x speed, rotation, feild orientation compensation angle
	mec_drive.DriveCartesian(joyYPower, joyXPower, -joystick.GetZ(), _gyro);
	

}


void Drive::TrainDrive()
{
	// assign joystick values
	double leftJoy = -controller.GetRawAxis(1); 
	double rightJoy = controller.GetRawAxis(5);
	
	// left motor speed, right motor speed, square joystick intensity true/false
	tank_drive.TankDrive(leftJoy, rightJoy, true);	
}

/// RAW FUNCTIONS

void Drive::RawMecDrive(double speedX, double speedY, double rotationZ, double fieldOrient)
{
	mec_drive.DriveCartesian(speedX, speedY, rotationZ, fieldOrient);
}

void Drive::RawTrainDrive(double speedL, double speedR)
{
	tank_drive.TankDrive(speedL, speedR, false);
}

void Drive::StopDrives()
{
	tank_drive.StopMotor();
	mec_drive.StopMotor();
}

void Drive::SetDriveSafety(bool enabled)
{
	tank_drive.SetSafetyEnabled(enabled);
	mec_drive.SetSafetyEnabled(enabled);
}