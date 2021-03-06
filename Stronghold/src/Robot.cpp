// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
//harold is cool

#include "Robot.h"
#include "Commands/AutonomousDriveStraightForTime.h"
#include "Commands/AutonomousDriveToDefense.h"
#include "Commands/AutonomousDriveThroughLowBar.h"
#include "Commands/AutonomousDriveLowBarShootLow.h"
#include "Commands/AutonomousDriveLowShootHigh.h"
#include "Commands/AutonomousDoNothing.h"
#include "Commands/AutonomousCommand.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Climber> Robot::climber;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<VisionEngine> Robot::ve;


void Robot::RobotInit() {
	RobotMap::init();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    driveTrain.reset(new DriveTrain());
    shooter.reset(new Shooter());
    climber.reset(new Climber());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand.reset(new AutonomousDefault());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	//Adds a sendable chooser to choose between AutonomousDriveToScore and AutonomousPickupAndScore
	chooser.AddObject("Drive To Defense", new (AutonomousDriveToDefense));
	chooser.AddDefault("Do Nothing", new (AutonomousDoNothing));
	chooser.AddObject("Drive Through LowBar", new (AutonomousDriveThroughLowBar));
	chooser.AddObject("Drive Through LowBar Shoot Low", new (AutonomousDriveLowBarShootLow));
	chooser.AddObject("Spy Shoot High", new (AutonomousDriveLowShootHigh));
	chooser.AddObject("Auto Testing - Don't choose in match!!", new (AutonomousDefault));
	SmartDashboard::PutData("Autonomous Modes", &chooser);

	AccelService.reset(new Notifier(Robot::UpdateAccel));
	AccelService->StartPeriodic(0.05);

	ve.reset(new VisionEngine());
	if (Preferences::GetInstance()->GetBoolean("EnableVision", false)) {
		ve->StartGRIP();
		VisionService.reset(new Notifier(Robot::UpdateVision));
		VisionService->StartPeriodic(0.1);
	}
  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	Robot::driveTrain->SetChassisMode(CANTalon::ControlMode::kMotionProfile);

	autonomousCommand.release();
	autonomousCommand.reset((Command *)chooser.GetSelected());

	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	Robot::driveTrain->SetChassisMode(CANTalon::ControlMode::kPercentVbus);
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	lw->Run();
}

void Robot::UpdateAccel() {
	Robot::driveTrain->UpdateChassisPitch();
}

START_ROBOT_CLASS(Robot);

void Robot::UpdateVision() {
	Robot::ve->ProcessContours();
}
