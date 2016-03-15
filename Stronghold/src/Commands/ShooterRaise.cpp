// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ShooterRaise.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ShooterRaise::ShooterRaise(int displacement): Command() {
    m_displacement = displacement;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooter.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ShooterRaise::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ShooterRaise::Execute() {
	Robot::shooter->ShooterElevate();
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterRaise::IsFinished() {
	bool bFinished = false;

	// Limit switch active forces stop
	bFinished = Robot::shooter->ShooterAtMax();

	if (m_AbsoluteCommand)
	{
		bFinished |= (Robot::shooter->GetShooterElevation() >= m_displacement);
	}
    return bFinished;
}

// Called once after isFinished returns true
void ShooterRaise::End() {
	Robot::shooter->ShooterStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterRaise::Interrupted() {
	Robot::shooter->ShooterStop();
}

ShooterRaise::ShooterRaise(): Command() {
	Requires(Robot::shooter.get());
	m_displacement = 0.0;
	m_AbsoluteCommand = false;
}
