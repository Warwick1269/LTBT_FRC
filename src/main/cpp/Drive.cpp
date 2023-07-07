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
	mec_drive.DriveCartesian(joyYPower, joyXPower, -joystick.GetZ(), _manualGyro);
	

}

/// @brief The function for timed auto drive when using MecanumDrive 
/// @param timeMS: The time it takes to complete the drive in miliseconds
/// @param speedX: The speed for x axis, [-1.0..1.0]
/// @param speedY: The speed for y axis, [-1.0..1.0]
/// @param rotationZ: The robot's rotation rate around the Z axis [-1.0..1.0]. Clockwise is positive.
// gyroAngle – The current angle reading from the gyro in degrees around the Z axis. Use this to implement field-oriented controls.
/// @param fieldOrient in Rads.
void Drive::TimedAutoMecDrive(int timeMS, double speedX, double speedY, double rotationZ, double fieldOrient)
{
	using namespace std::this_thread;
	using namespace std::chrono;
	
	// mec_drive.SetSafetyEnabled(false);

	mec_drive.DriveCartesian(speedX, speedY, rotationZ, fieldOrient);
	sleep_for(milliseconds(timeMS));
	mec_drive.StopMotor();

	//mec_drive.SetSafetyEnabled(true);
}

void Drive::TrainDrive()
{
	// assign joystick values
	double leftJoy = -controller.GetRawAxis(1); 
	double rightJoy = controller.GetRawAxis(5);
	
	// left motor speed, right motor speed, square joystick intensity true/false
	tank_drive.TankDrive(leftJoy, rightJoy, true);	
}