#include "Robot.h"
#include <frc/Joystick.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>


/// @brief This is the class containing all the drive functions and *exposed* variables.
/// Drive constructor: 
/// @param deadZone is 0.02 default, 
/// @param maxSpeed is 0.8 suggested; is between 0-1; 
/// will multiply the value of joystick input by this to change the max speed while keeping the same range of joystick movement as 0 * 0.8 = 0, and 1 * 0.8 = 0.8.
class Drive
{
private:
	// Left
	WPI_VictorSPX frontL {4};
	WPI_VictorSPX backL {5};


	// Right
	WPI_VictorSPX frontR {3};
	WPI_VictorSPX backR {2};

	// controller declarations
	// frc::Joystick controller{1};
	frc::Joystick joystick{2};

	// Drive train	
	// frc::MotorControllerGroup m_left{frontL, backL};
	// frc::MotorControllerGroup m_right{frontR, backR};
	
	// frc::DifferentialDrive tank_drive{m_left, m_right};

	// Mecanum Drive
	frc::MecanumDrive mec_drive{frontL, backL, frontR, backR};


	// Other
	double _deadZone;
	double _maxSpeed;

public:
    Drive(double joySense, double deadZone); // This is the constructor function, which is called when the class is instantiated
	
	void MecDrive(); // Call this for MecanumDrive bases 
	void TrainDrive(); // Call this for Drive Trains

	// RAW FUNCTIONS for interfacing with drive base 
	void RawMecDrive(double speedX, double speedY, double rotationZ);
	void RawTrainDrive(double speedL, double speedR);
	void StopDrives();
	void SetDriveSafety(bool enabled);
	
	
};

