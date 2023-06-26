#include "Drive.h"
#include <frc/drive/MecanumDrive.h>
#include <frc/filter/SlewRateLimiter.h>


Drive::Drive(double joySense)
{

	leftJoy = -controller.GetRawAxis(1); 
	rightJoy = controller.GetRawAxis(5);

	// Squares joystick intensity for better control, 
	

}

void Drive::MecDrive(double deadZone, double maxSpeed){
	// Smooth the joystick Y for every unit of time
	frc::SlewRateLimiter<units::scalar> filterY{0.5 / 1_s};	
	// Smooth the joystick X for every unit of time
	frc::SlewRateLimiter<units::scalar> filterX{0.5 / 1_s};
	//NOTE: You need to create a new SlewRateLimiter for each value you want to smooth. 
	//They will collide if you use the same SlewRateLimiter for multiple values.

	double joyY = filterY.Calculate(-joystick.GetY());
	double joyX = filterX.Calculate(-joystick.GetX());

	double joyYPower = joyY * fabs(joyY) * joySense;
	double joyXPower = joyX * fabs(joyX) * joySense;
	
	// y speed, x speed, rotation, feild orientation compensation
	mec_drive.DriveCartesian(joyYPower, joyXPower, -joystick.GetZ(), 0);

}

void Drive::TrainDrive(double deadZone, double maxSpeed){

	leftPower = leftJoy * fabs(leftJoy) * joySense;
	rightPower = rightJoy * fabs(rightJoy) * joySense;

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