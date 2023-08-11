#include "Auto.h"
#include "Drive.h"
#include "Arm.h"

Auto::Auto(/* args */)
{

}

/**
 * TimedAutoTrainDrive is a function that drives the DriveTrain for a specified amount of time
 * at a given speed on the left and right sides.
 *
 * @param timeMS the duration of time to drive the train in milliseconds
 * @param speedL the speed of the left side of the DriveTrain, [-1.0..1.0]
 * @param speedR the speed of the right side of the DriveTrain, [-1.0..1.0]
 */
void Auto::TimedAutoTrainDrive(int timeMS, double speedL, double speedR) 
{
	Drive autoTrainDrive(0.02, 0.8);
    
    using namespace std::this_thread;
	using namespace std::chrono;

	// // autoTrainDrive.SetSafetyEnabled(false);

	autoTrainDrive.RawTrainDrive(speedL, speedR);
		
	sleep_for(milliseconds(timeMS));
		
    autoTrainDrive.StopDrives();
		
	// autoTrainDrive.SetDriveSafety(true);
}

/**
 * @brief The function for timed auto drive when using MecanumDrive 
 * @param timeMS: The time it takes to complete the drive in miliseconds
 * @param speedX: The speed for x axis, [-1.0..1.0]
 * @param speedY: The speed for y axis, [-1.0..1.0]
 * @param rotationZ: The robot's rotation rate around the Z axis [-1.0..1.0]. Clockwise is positive.
 * gyroAngle – The current angle reading from the gyro in degrees around the Z axis. Use this to implement field-oriented controls.
 * @param fieldOrient in Rads.
 */
void Auto::TimedAutoMecDrive(int timeMS, double speedX, double speedY, double rotationZ, double fieldOrient)
{
    Drive autoMecDrive(0.02, 0.8);

	using namespace std::this_thread;
	using namespace std::chrono;
	
	// // autoMecDrive.SetDriveSafety(false);

    autoMecDrive.RawMecDrive(speedX, speedY, rotationZ, fieldOrient);
	
	sleep_for(milliseconds(timeMS));

    autoMecDrive.StopDrives();

	// autoMecDrive.SetDriveSafety(true);
}

void Auto::TimedAutoIntake(int timeMS, double speed)
{
	Arm autoIntake;

	using namespace std::this_thread;
	using namespace std::chrono;

	autoIntake.RawIntake(speed);

	sleep_for(milliseconds(timeMS));

	autoIntake.RawIntake(0);
}

void TimedAutoArmBend(int timeMS, double speed)
{
	Arm autoArmBend;

	using namespace std::this_thread;
	using namespace std::chrono;

	autoArmBend.RawBendOne(speed);

	sleep_for(milliseconds(timeMS));

	autoArmBend.RawBendOne(0);


}