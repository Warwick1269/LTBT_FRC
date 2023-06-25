#include "Drive.h"


Drive::Drive(double joySense)
{

	leftJoy = -controller.GetRawAxis(1); 
	rightJoy = controller.GetRawAxis(5);

	// Squares joystick intensity for better control, 
	
	leftPower = leftJoy * fabs(leftJoy) * joySense;
	rightPower = rightJoy * fabs(rightJoy) * joySense;

}


void Drive::MecDrive(double deadZone, double maxSpeed){
	
}

void Drive::TrainDrive(double deadZone, double maxSpeed){

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