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
void Arm::ArmBendOne(double maxSpeed)
{
    double leftPower = _leftJoy * fabs(_leftJoy);
    
    if (_bButton)
    {
        bendOne.Set(0);
    }
    else
    {
        bendOne.Set(leftPower * maxSpeed);
    }

}

/**
 * Bend the arm joint two.
 *
 * @param speed the speed at which to bend the arm (double)
 * @param smooth the smoothness of the arm movement (double)
 */
void Arm::ArmBendTwo(double maxSpeed) 
{
    double rightPower = _rightJoy * fabs(_rightJoy);

    if (_bButton)
    {
        bendTwo.Set(0);
    }
    else
    {
        bendTwo.Set(rightPower * maxSpeed);
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
        intake1.Set(speed);
        intake2.Set(speed);
    }
    if (_lBumper)
    {
        intake1.Set(-speed);
        intake2.Set(-speed);
    }
    else
    {
        intake1.Set(0);
        intake2.Set(0);
    }
}

void Arm::RawIntake(double speed)
{
    intake1.Set(-speed);
    intake2.Set(speed);
}

void Arm::RawBendTwo(double speed)
{
    bendTwo.Set(speed);
}

void Arm::ArmSafety(bool enabled)
{
    bendOne.SetSafetyEnabled(enabled);
    bendTwo.SetSafetyEnabled(enabled);
}