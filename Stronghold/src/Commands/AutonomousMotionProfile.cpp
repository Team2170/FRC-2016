// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutonomousMotionProfile.h"
#include <iostream>
#include <fstream>
#include <string>


AutonomousMotionProfile::AutonomousMotionProfile(): Command(),
	talonService(AutonomousMotionProfile::PeriodicTask) {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveTrain.get());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}


// Called just before this Command runs the first time
void AutonomousMotionProfile::Initialize() {
	Robot::driveTrain->SetChassisMode(CANTalon::ControlMode::kMotionProfile);

	if (bResetGyro) {
		Robot::driveTrain->ResetChassisYaw();
	}

	if (mRightWheel) {
		Robot::driveTrain->FillProfileBuffer(mLeftWheel, mRightWheel);
	}
	else {
		Robot::driveTrain->FillProfileBuffer(mLeftWheel);
	}

	talonService.StartPeriodic(0.005);
}

// Called repeatedly when this Command is scheduled to run
void AutonomousMotionProfile::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool AutonomousMotionProfile::IsFinished() {
    return Robot::driveTrain->MotionProfileComplete();
}

// Called once after isFinished returns true
void AutonomousMotionProfile::End() {
	talonService.Stop();
	Robot::driveTrain->SetMotionProfileState(CANTalon::SetValueMotionProfileHold);
	Robot::driveTrain->SetChassisMode(CANTalon::ControlMode::kPercentVbus);
}


// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonomousMotionProfile::Interrupted() {
	End();
}

AutonomousMotionProfile::AutonomousMotionProfile(const ProfileData* LeftWheel, bool ResetGyro) : Command(),
		talonService(AutonomousMotionProfile::PeriodicTask){
	Requires(Robot::driveTrain.get());
	bResetGyro = ResetGyro;
	mLeftWheel.reset(LeftWheel);
	mRightWheel.reset();
}

AutonomousMotionProfile::AutonomousMotionProfile(const ProfileData* LeftWheel,
		const ProfileData* RightWheel, bool ResetGyro) : Command(),
				talonService(AutonomousMotionProfile::PeriodicTask) {
	Requires(Robot::driveTrain.get());
	bResetGyro = ResetGyro;
	mLeftWheel.reset(LeftWheel);
	mRightWheel.reset(RightWheel);
}

AutonomousMotionProfile::AutonomousMotionProfile(
		const std::string& LProfileName, const std::string& RProfileName, bool ResetGyro) :
		Command(), talonService(AutonomousMotionProfile::PeriodicTask) {

	Requires(Robot::driveTrain.get());

	bResetGyro = ResetGyro;
	std::ifstream input(LProfileName.c_str());
	std::string token;
	std::array<double, 3> rowData;

	mLeftProfile.clear();
	mRightProfile.clear();

	mLeftWheel.reset(&mLeftProfile);
	mRightWheel.reset(&mRightProfile);

	while (input.good()) {
		std::getline(input, token, ',');
		rowData[0] = std::stod(token);
		std::getline(input, token, ',');
		rowData[1] = std::stod(token);
		std::getline(input, token, ',');
		rowData[2] = std::stod(token);

		std::getline(input,token);
		mLeftProfile.push_back(rowData);
	}

	printf("%s loaded %u points\n",
			LProfileName.c_str(), mLeftProfile.size());

	input.close();
	input.open(RProfileName.c_str());

	while (input.good()) {
		std::getline(input, token, ',');
		rowData[0] = std::stod(token);
		std::getline(input, token, ',');
		rowData[1] = std::stod(token);
		std::getline(input, token, ',');
		rowData[2] = std::stod(token);

		std::getline(input,token);
		mRightProfile.push_back(rowData);
	}

	printf("%s loaded %u points\n",
			RProfileName.c_str(), mRightProfile.size());
}


void AutonomousMotionProfile::PeriodicTask() {
	Robot::driveTrain->ServiceMotionProfile();
}

AutonomousMotionProfile::AutonomousMotionProfile(
		const std::string& ProfileName, bool ResetGyro) : Command(),
				talonService(AutonomousMotionProfile::PeriodicTask) {

	Requires(Robot::driveTrain.get());

	bResetGyro = ResetGyro;
	std::ifstream input(ProfileName.c_str());
	std::string token;
	std::array<double, 3> rowData;

	mLeftProfile.clear();
	mRightProfile.clear();

	mLeftWheel.reset(&mLeftProfile);
	mRightWheel.reset();

	while (input.good()) {
		std::getline(input, token, ',');
		rowData[0] = std::stod(token);
		std::getline(input, token, ',');
		rowData[1] = std::stod(token);
		std::getline(input, token, ',');
		rowData[2] = std::stod(token);

		//this line is to make sure to get rid of the \r
		std::getline(input,token);
		mLeftProfile.push_back(rowData);
	}

	printf("%s loaded %u points\n",
			ProfileName.c_str(), mLeftProfile.size());
}
