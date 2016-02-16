// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutonomousDriveStraightForTime.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutonomousDriveStraightForTime::AutonomousDriveStraightForTime(double DriveTime): Command() {
    m_DriveTime = DriveTime;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveTrain.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutonomousDriveStraightForTime::Initialize() {
	 	Robot::driveTrain->ResetChassisYaw();
	 	Command::SetTimeout(m_DriveTime);
}

// Called repeatedly when this Command is scheduled to run
void AutonomousDriveStraightForTime::Execute() {
	//sets forward or backward
	Robot::driveTrain->DriveStraight(false);

}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousDriveStraightForTime::IsFinished() {
	return Command::IsTimedOut();
}

// Called once after isFinished returns true
void AutonomousDriveStraightForTime::End() {
	Robot::driveTrain->DriveStraight(0.0f);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousDriveStraightForTime::Interrupted() {

}
