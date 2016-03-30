// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutonomousChassisAim.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutonomousChassisAim::AutonomousChassisAim():
	Command(), m_RotationGain(
			Preferences::GetInstance()->GetFloat("RotationGain",
					kDefaultGain)), m_TargetTolerance(
			Preferences::GetInstance()->GetInt("TargetTolerance",
					kDefaultTolerance)), m_TargetLockLimit(
			Preferences::GetInstance()->GetInt("TargetLockLimit",
					kDefaultLockLimit)) {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveTrain.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutonomousChassisAim::Initialize() {
	Robot::driveTrain->SetChassisMode(CANTalon::ControlMode::kSpeed);
}

// Called repeatedly when this Command is scheduled to run
void AutonomousChassisAim::Execute() {
	float TargetError = Robot::ve->GetHorizonatlError();
	float RotateCommand = TargetError * m_RotationGain;

	if ((TargetError < m_TargetTolerance) &&
			(TargetError > -m_TargetTolerance)) {
		m_OnTargetCount++;
	}
	else {
		m_OnTargetCount = 0;
	}
	Robot::driveTrain->Rotate(RotateCommand);
}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousChassisAim::IsFinished() {
    return (m_OnTargetCount > m_TargetLockLimit);
}

// Called once after isFinished returns true
void AutonomousChassisAim::End() {
	Robot::driveTrain->SetChassisMode(CANTalon::ControlMode::kPercentVbus);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousChassisAim::Interrupted() {
	End();
}
