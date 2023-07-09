#include "Robot.h"

class Arm
{
private:

    frc::Joystick controller{0};

	WPI_VictorSPX bendOne {5};
	WPI_VictorSPX bendTwo {6};
	WPI_VictorSPX intake {7};


	int _leftTrigger = controller.GetRawAxis(2);
	int _rightTrigger = controller.GetRawAxis(3);

	int _xButton = controller.GetRawButton(3);
	int _bButton = controller.GetRawButton(2);
	int _yButton = controller.GetRawButton(4);

	int _lBumper = controller.GetRawButton(5);
	int _rBumper = controller.GetRawButton(6);

	double _leftJoy = -controller.GetRawAxis(1); 
	double _rightJoy = controller.GetRawAxis(5);

public:
    Arm(/* args */);
    void ArmBendOne(double speed, double smooth);
    void ArmBendTwo(double speed, double smooth);
    void Intake(double speed);

};

