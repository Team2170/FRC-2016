// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ShooterFlywheelHigh.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ShooterFlywheelHigh::ShooterFlywheelHigh(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooter.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	m_UntimedCommand = true;
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ShooterFlywheelHigh::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ShooterFlywheelHigh::Execute() {
	Robot::shooter->FlyWheelHighSpeed();
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterFlywheelHigh::IsFinished() {
    return IsTimedOut() || m_UntimedCommand;
}

// Called once after isFinished returns true
void ShooterFlywheelHigh::End() {

}

ShooterFlywheelHigh::ShooterFlywheelHigh(double timeout): Command(timeout) {
	Requires(Robot::shooter.get());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterFlywheelHigh::Interrupted() {
}
