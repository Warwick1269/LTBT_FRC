#include "Arm.h"
#include <frc/filter/SlewRateLimiter.h>

Arm::Arm(/* args */)
{
    bendOne.SetSafetyEnabled(true);
    bendTwo.SetSafetyEnabled(true);
}

/**
 * Bend the arm joint one.
 *
 * @param speed the speed at which to bend the arm (double)
 * @param smooth the smoothness of the arm movement (double)
 */
void Arm::ArmBendOne(double maxSpeed, double smooth)
{
    frc::SlewRateLimiter<units::scalar> filter{smooth / 1_s};	

    double leftJoy = filter.Calculate(_leftJoy); 
    

    if (_bButton)
    {
        bendOne.Set(0);
    }
    else
    {
        bendOne.Set(leftJoy * maxSpeed);
    }

}

/**
 * Bend the arm joint two.
 *
 * @param speed the speed at which to bend the arm (double)
 * @param smooth the smoothness of the arm movement (double)
 */
void Arm::ArmBendTwo(double maxSpeed, double smooth) 
{
    frc::SlewRateLimiter<units::scalar> filter{smooth / 1_s};

    double rightJoy = filter.Calculate(_rightJoy);

    if (_bButton)
    {
        bendTwo.Set(0);
    }
    else
    {
        bendTwo.Set(rightJoy * maxSpeed);
    } 
}

/**
 * Set the intake speed based on the state of the right bumper.
 *
 * @param speed: the speed to set the intake to (double)
 */
void Arm::Intake(double speed)
{
    if (_rBumper)
    {
        intake.Set(speed);
    }
    else
    {
        intake.Set(0);
    }
}

void Arm::RawIntake(double speed)
{
    intake.Set(speed);
}