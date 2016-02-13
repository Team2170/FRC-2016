// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "../Commands/TankDriveTeleop.h"
#include "DriveTrain.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include <RobotDrive.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    cANTalonRight = RobotMap::driveTrainCANTalonRight;
    cANTalonLeft = RobotMap::driveTrainCANTalonLeft;
    robotDrive = RobotMap::driveTrainRobotDrive;
    gyro = RobotMap::driveTrainGyro;
    maxSonarAI = RobotMap::driveTrainMaxSonarAI;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    FrontSonar.reset(new MaxSonarEZ1(maxSonarAI));
}

void DriveTrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new TankDriveTeleop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
void DriveTrain::ArcadeDriveWithJoysticks(float moveVal, float rotateVal) {
	robotDrive->ArcadeDrive(moveVal, rotateVal, true);
}

void DriveTrain::ResetChassisYaw() {
	gyro->Reset();
}

float DriveTrain::ReadChassisYaw() {
	return gyro->GetAngle();
}

void DriveTrain::DriveStraight(bool Backwards) {
	if (Backwards)
		{
			DriveStraight(-mAutoVelocity);
		}
		else
		{
			DriveStraight(mAutoVelocity);
		}
}


void DriveTrain::DriveStraight(float magnitude) {

		float ChassisAngle = ReadChassisYaw();

		if (magnitude > 0.0) {
			robotDrive->Drive(magnitude, mYawGain * ChassisAngle);
		}
		else {
			robotDrive->Drive(magnitude, -mYawGain * ChassisAngle);
		}
}

void DriveTrain::StopMotors(void) {

	robotDrive->StopMotor();

}

void DriveTrain::IntializeMotorDrives() {
	cANTalonLeft->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	cANTalonLeft->EnableControl();
	cANTalonLeft->Set(0.0);
	cANTalonRight->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	cANTalonRight->EnableControl();
	cANTalonRight->Set(0.0);

}

void DriveTrain::TankDriveWithTriggers(float Left, float Right, float Trigger) {
	float newLeft = 0.0;
 	float newRight = 0.0;
 	float ProcessedLeft = Left;
 	float ProcessedRight = Right;
 	double fExponent = 1.0;


 	// make sure talons are in voltage drive mode

	cANTalonLeft->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	cANTalonRight->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);


 	ProcessedLeft = DEADBAND(AxisPower(ProcessedLeft, fExponent), 0.15);


 	ProcessedRight = DEADBAND(AxisPower(ProcessedRight, fExponent), 0.15);


 	newLeft = fmax(fmin(ProcessedLeft + (Trigger * .8), 1.0), -1.0);
 	newRight = fmax(fmin(ProcessedRight + (Trigger * .8), 1.0), -1.0);


 	if ((ProcessedLeft == 0) && (ProcessedRight == 0)) {
 		if (!bDriveStraight || DEADBAND(Trigger, 0.15) == 0) {
 			ResetChassisYaw();
 		}
 		bDriveStraight = true;
 		DriveStraight(Trigger * 0.8f);
 	}
 	else {
 		bDriveStraight = false;
 		robotDrive->TankDrive(newLeft, newRight, true);
 	}
}

double DriveTrain::AxisPower(double axis, double exponent) {
	double retVal = 0.0;

	retVal = pow(fabs(axis), exponent);
	retVal = (axis < 0.0) ? -1.0 * retVal : retVal;

	return retVal;
}

void DriveTrain::SetClosedLoopMode() {

	cANTalonLeft->SetControlMode(CANSpeedController::ControlMode::kPosition);
	cANTalonLeft->SetFeedbackDevice(CANTalon::QuadEncoder);
	cANTalonLeft->ConfigEncoderCodesPerRev(1000);
	cANTalonLeft->SetPosition(0.0);
	cANTalonLeft->SetSensorDirection(false);
	cANTalonLeft->EnableControl();
	cANTalonLeft->Set(0.0);

	cANTalonRight->SetControlMode(CANSpeedController::ControlMode::kPosition);
	cANTalonRight->SetFeedbackDevice(CANTalon::QuadEncoder);
	cANTalonRight->ConfigEncoderCodesPerRev(1000);
	cANTalonRight->SetPosition(0.0);
	cANTalonRight->SetSensorDirection(false);
	cANTalonRight->EnableControl();
	cANTalonRight->Set(0.0);
}

void DriveTrain::SetMotionProfileMode() {
	cANTalonLeft->SetControlMode(CANSpeedController::ControlMode::kMotionProfile);
	cANTalonLeft->EnableControl();
	cANTalonLeft->Set(0.0);
	cANTalonRight->SetControlMode(CANSpeedController::ControlMode::kMotionProfile);
	cANTalonRight->EnableControl();
	cANTalonRight->Set(0.0);
}

float DriveTrain::ReadChassisDistance() {
	return(FrontSonar->GetRangeInches());
}

void DriveTrain::Rotate(float rotateSpeed) {
	//if positive clockwise else counterclockwise
	//don't want squared value, for some reason
	robotDrive->TankDrive(rotateSpeed,-rotateSpeed,false);
}

void DriveTrain::CommandChassisPosition(float position) {
	if (cANTalonLeft->GetControlMode()==
			CANSpeedController::ControlMode::kPosition){
		cANTalonLeft->Set(position);
	}

	if (cANTalonRight->GetControlMode()==
			CANSpeedController::ControlMode::kPosition){
	cANTalonRight->Set(position);
	}
}

double DriveTrain::ReadPositionError() {
	return (cANTalonLeft->GetClosedLoopError()/1000.0);
}

void DriveTrain::SetVelocityMode() {
cANTalonLeft->SetControlMode(CANSpeedController::ControlMode::kSpeed);
cANTalonLeft->EnableControl();
cANTalonLeft->Set(0.0);
cANTalonRight->SetControlMode(CANSpeedController::ControlMode::kSpeed);
cANTalonRight->EnableControl();
cANTalonRight->Set(0.0);
}

void DriveTrain::SetChassisVelocity(float velocity) {
	if (cANTalonLeft->GetControlMode()==
				CANSpeedController::ControlMode::kSpeed){
			cANTalonLeft->Set(velocity);
		}

		if (cANTalonRight->GetControlMode()==
				CANSpeedController::ControlMode::kSpeed){
		cANTalonRight->Set(velocity);
		}
}
