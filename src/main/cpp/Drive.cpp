#include "Drive.h"
#include <frc/filter/SlewRateLimiter.h>


// Drive constructor: joySense is the speed multiplier or joystick sensitivity; default 0.6, deadZone is 0.015 default, maxSpeed is 0.9 default; is between 0-1.
Drive::Drive(double joySense, double deadZone, double maxSpeed)
{
	_joySense = joySense;	
	_deadZone = deadZone;
	_maxSpeed = maxSpeed;
	// Squares joystick intensity for better control, 
	

}

void Drive::MecDrive(){
	//NOTE: You need to create a new SlewRateLimiter for each value you want to smooth. 
	//They will collide if you use the same SlewRateLimiter for multiple values.

	// Smooth the joystick Y for every unit of time
	frc::SlewRateLimiter<units::scalar> filterY{0.5 / 1_s};	
	// Smooth the joystick X for every unit of time
	frc::SlewRateLimiter<units::scalar> filterX{0.5 / 1_s};

	// Limits the joystick to the dead zone using a turnery. 
	// i.e. if abs of joystick is greater than dead zone, use joystick value. else 0	
	double joyZonedY = fabs(joystick.GetY()) > _deadZone ? joystick.GetY() : 0;
	double joyZonedX = fabs(joystick.GetX()) > _deadZone ? joystick.GetX() : 0;
	double joyZonedZ = fabs(joystick.GetZ()) > _deadZone ? joystick.GetZ() : 0;

	//Applies the slew rate limiter
	double joyY = filterY.Calculate(-joyZonedY);
	double joyX = filterX.Calculate(-joyZonedX);

	// squares joystick intensity for finer control and then adjusts for joy sense.
	// joySense is essentially the speed multiplier, feel free to rename it if that makes more sense.
	double joyYPower = joyY * fabs(joyY) * _joySense;
	double joyXPower = joyX * fabs(joyX) * _joySense;

	// limit joy power to max speed.
	if (fabs(joyYPower) > _maxSpeed) {
		joyYPower = joyYPower < 0 ? -_maxSpeed : _maxSpeed;
	}
	if (fabs(joyXPower) > _maxSpeed) {
		joyXPower = joyXPower < 0 ? -_maxSpeed : _maxSpeed;
	}
	
	// y speed, x speed, rotation, feild orientation compensation angle
	mec_drive.DriveCartesian(joyYPower, joyXPower, -joyZonedZ, _manualGyro);

}

void Drive::TrainDrive(){
	double leftJoy = -controller.GetRawAxis(1); 
	double rightJoy = controller.GetRawAxis(5);

	double joyZonedL = fabs(leftJoy) > _deadZone ? leftJoy : 0;
	double joyZonedR = fabs(rightJoy) > _deadZone ? rightJoy : 0;	

	double leftPower = joyZonedL * fabs(joyZonedL) * _joySense;
	double rightPower = joyZonedR * fabs(joyZonedR) * _joySense;

	if (fabs(leftPower) > _maxSpeed) {
		leftPower = leftPower < 0 ? -_maxSpeed : _maxSpeed;
	}
	if (fabs(rightPower) > _maxSpeed) {
		rightPower = rightPower < 0 ? -_maxSpeed : _maxSpeed;
	}

	m_drive.TankDrive(leftPower, rightPower);	
}