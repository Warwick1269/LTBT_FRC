#include "Robot.h"

class Arm
{
private:

    frc::Joystick controller{0};

public:
    Arm(/* args */);
    void ArmBendOne();
    void ArmBendTwo();

};

