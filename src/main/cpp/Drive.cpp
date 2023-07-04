#include "Drive.h"
#include <frc/drive/MecanumDrive.h>
#include <frc/filter/SlewRateLimiter.h>


Drive::Drive(double joySense)
{
	_joySense = joySense;	
	leftJoy = -controller.GetRawAxis(1); 
	rightJoy = controller.GetRawAxis(5);

	// Squares joystick intensity for better control, 
	

}

// MecDrive: deadZone is 0.015 default, maxSpeed is 0.9 default; is between 0-1.
void Drive::MecDrive(double deadZone, double maxSpeed){
	//NOTE: You need to create a new SlewRateLimiter for each value you want to smooth. 
	//They will collide if you use the same SlewRateLimiter for multiple values.

	// Smooth the joystick Y for every unit of time
	frc::SlewRateLimiter<units::scalar> filterY{0.5 / 1_s};	
	// Smooth the joystick X for every unit of time
	frc::SlewRateLimiter<units::scalar> filterX{0.5 / 1_s};

	// Limits the joystick to the dead zone using a turnery. 
	// i.e. if abs of joystick is greater than dead zone, use joystick value. else 0	
	double joyZonedY = fabs(joystick.GetY()) > deadZone ? joystick.GetY() : 0;
	double joyZonedX = fabs(joystick.GetX()) > deadZone ? joystick.GetX() : 0;
	double joyZonedZ = fabs(joystick.GetZ()) > deadZone ? joystick.GetZ() : 0;

	//Applies the slew rate limiter
	double joyY = filterY.Calculate(-joyZonedY);
	double joyX = filterX.Calculate(-joyZonedX);

	// squares joystick intensity for finer control and then adjusts for joy sense.
	// joySense is essentially the speed multiplier, feel free to rename it if that makes more sense.
	double joyYPower = joyY * fabs(joyY) * _joySense;
	double joyXPower = joyX * fabs(joyX) * _joySense;

	// limit joy power to max speed.
	if (fabs(joyYPower) > maxSpeed) {
		joyYPower = joyYPower < 0 ? -maxSpeed : maxSpeed;
	}
	if (fabs(joyXPower) > maxSpeed) {
		joyXPower = joyXPower < 0 ? -maxSpeed : maxSpeed;
	}
	
	// y speed, x speed, rotation, feild orientation compensation angle
	mec_drive.DriveCartesian(joyYPower, joyXPower, -joyZonedZ, _manualGyro);

}

void Drive::TrainDrive(double deadZone, double maxSpeed){

	leftPower = leftJoy * fabs(leftJoy) * _joySense;
	rightPower = rightJoy * fabs(rightJoy) * _joySense;

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

	if (fabs(leftJoy) > deadZone) {
		frontR.Set(leftPower);
		backR.Set(leftPower);
	} else {
		frontR.Set(0);
		backR.Set(0);
	}

	// right drivetrain>
	if (fabs(rightJoy) > deadZone) {
		frontL.Set(rightPower);
		backL.Set(rightPower);
	} else {
		frontL.Set(0);
		backL.Set(0);
	}
    
}