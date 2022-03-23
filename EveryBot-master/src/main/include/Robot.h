// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/Spark.h>
#include <ctre/Phoenix.h>

#include <frc/Joystick.h>

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

	// Left
	WPI_VictorSPX frontL{1};
	WPI_VictorSPX backL{2};

	// Right
	WPI_VictorSPX frontR{3};
	WPI_VictorSPX backR{4};

	WPI_VictorSPX flooper{5};
	WPI_VictorSPX spinner{6};
	WPI_VictorSPX climber{7};

	frc::Joystick controller{0};
};
