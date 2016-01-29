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
#include "Robot.h"
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

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
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
void DriveTrain::DriveWithJoysticks() {
	robotDrive->ArcadeDrive(Robot::oi->getDriveJoystick()->GetX(),
			Robot::oi->getDriveJoystick()->GetY(), true);
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
	Robot::driveTrain->robotDrive->SetSensitivity(0.1);
		float ChassisAngle = ReadChassisYaw();

		if (magnitude > 0.0) {
			robotDrive->Drive(magnitude, mYawGain * ChassisAngle);
		}
		else {
			robotDrive->Drive(magnitude, -mYawGain * ChassisAngle);

		}
}

void DriveTrain::StopMotors(void) {

	driveMotors->StopMotor();
	//Robot::chassis->movementData->Stop();


	 mCurrentAutoMagnitude = mDefaultAutoMagnitude;
	 mCurrentAutoRotationVelocity = mDefaultAutoRotatationVelocity;
	 mAutoVelocity = mDefaultAutoVelocity;

}
