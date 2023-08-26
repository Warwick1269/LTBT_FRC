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
	Drive autoTrainDrive(0.02, 1);
	autoTrainDrive.SetDriveSafety(false);

    
    using namespace std::this_thread;
	using namespace std::chrono;

	
	autoTrainDrive.RawTrainDrive(speedL, speedR);
		
	sleep_for(milliseconds(timeMS));
		
    autoTrainDrive.StopDrives();
		
	autoTrainDrive.SetDriveSafety(true);
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
void Auto::TimedAutoMecDrive(int timeMS, double speedX, double speedY, double rotationZ)
{
    Drive autoMecDrive(0.02, 1);

	using namespace std::this_thread;
	using namespace std::chrono;
	
	autoMecDrive.SetDriveSafety(false);

    autoMecDrive.RawMecDrive(speedX, speedY, rotationZ);
	
	sleep_for(milliseconds(timeMS));

    autoMecDrive.StopDrives();

	autoMecDrive.SetDriveSafety(true);
}

/**
 * @brief the Auto Timed Auto Intake routine.
 *
 * @param timeMS the duration in milliseconds to run the intake
 * @param speed the speed at which to run the intake
 */
void Auto::TimedAutoIntake(int timeMS, double speed)
{
	Arm autoIntake;

	using namespace std::this_thread;
	using namespace std::chrono;

	autoIntake.RawIntake(speed);

	sleep_for(milliseconds(timeMS));

	autoIntake.RawIntake(0);
}

/**
 * @brief The TimedAutoArmBendTwo function is used to perform a timed auto arm bending movement. 
 * The function takes in two parameters: `timeMS` (the duration of the arm bending movement in milliseconds) 
 * and `speed` (the speed of the arm bending movement). 
 * 
 * @param timeMS The duration of the arm bending movement in milliseconds.
 * @param speed The speed of the arm bending movement.
 */
void Auto::TimedAutoArmBendTwo(int timeMS, double speed)
{
	Arm autoArmBend;

	autoArmBend.ArmSafety(false);

	using namespace std::this_thread;
	using namespace std::chrono;

	autoArmBend.RawBendTwo(speed);

	sleep_for(milliseconds(timeMS));

}

void Auto::ArmStop()
{
	Arm autoArmBend;

	autoArmBend.RawBendTwo(0);

	autoArmBend.ArmSafety(true);
}