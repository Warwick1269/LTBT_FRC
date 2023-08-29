// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/motorcontrol/Spark.h>
#include <ctre/Phoenix.h>

#include <frc/Joystick.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/filter/SlewRateLimiter.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  
 private:

	frc::Joystick joystick{1};

	frc::Joystick controller{3};
 
    
	WPI_VictorSPX frontL {4};
	WPI_VictorSPX backR {5};


	// Right
	WPI_VictorSPX frontR {3};
	WPI_VictorSPX backL {2};

	frc::MecanumDrive mec_drive{frontL, backR, frontR, backL};

	WPI_VictorSPX bendOne {6};
	WPI_VictorSPX bendTwo {1};
	WPI_VictorSPX intake1 {0};
	WPI_VictorSPX intake2 {7};


	int _leftTrigger = controller.GetRawAxis(2);
	int _rightTrigger = controller.GetRawAxis(3);

	int _xButton = controller.GetRawButton(3);
	int _yButton = controller.GetRawButton(4);


	
	double maxSpeed = 0.65;
	double speed = 0.55;
	double autoSpeed = -0.5; 
	double reducedSpeed = 0.5;

	frc::SlewRateLimiter<units::scalar> filter{0.9 / 1_s};	
};
