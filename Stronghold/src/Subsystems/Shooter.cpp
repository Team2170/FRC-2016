// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Shooter.h"
#include "../RobotMap.h"
#include "../Commands/ShooterJoystickControl.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Shooter::Shooter() : Subsystem("Shooter") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    elevationMotor = RobotMap::shooterElevationMotor;
    flyWheelMotor = RobotMap::shooterFlyWheelMotor;
    elevationEncoder = RobotMap::shooterElevationEncoder;
    elevationHome = RobotMap::shooterElevationHome;
    elevationMax = RobotMap::shooterElevationMax;
    ballKicker = RobotMap::shooterBallKicker;
    ballKickSensor = RobotMap::shooterBallKickSensor;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    kShooterLength = prefs->GetFloat("ShooterLength", 12.0);
    kArmLength = prefs->GetFloat("ArmLength", 10.0);
    kCountsPerInch = prefs->GetFloat("BallScrewCPI", 500.0);
}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new ShooterJoystickControl());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Shooter::FlyWheelReverse() {
	float speed = prefs->GetFloat("FlyWheelReverseSpeed", kFlyWheelReverseSpeed);
	flyWheelMotor->Set(-speed);
}

void Shooter::FlyWheelStop() {
	flyWheelMotor->Set(kFlyWheelStop);
}

void Shooter::FlyWheelHighSpeed() {
	float speed = prefs->GetFloat("FlyWheelHighSpeed", kFlyWheelHighSpeed);
	flyWheelMotor->Set(-speed);
}

void Shooter::FlyWheelLowSpeed() {
	float speed = prefs->GetFloat("FlyWheelLowSpeed", kFlyWheelLowSpeed);
	flyWheelMotor->Set(-speed);
}

void Shooter::KickerExtend() {
	ballKicker->Set(kKickerExtendSpeed);
}

void Shooter::KickerRetract() {
	ballKicker->Set(kKickerRetractSpeed);
}

bool Shooter::KickerDetect() {
	return !ballKickSensor->Get();		// Normally open switch need to invert
}

void Shooter::ShooterElevate() {
	if (!ShooterAtMax()) {
		elevationMotor->Set(-kShooterElevateSpeed);
	}
	else {
		elevationMotor->Set(kShooterStop);
	}
}

void Shooter::ShooterLower() {
	if (!ShooterIsHome()) {
		elevationMotor->Set(-kShooterLowerSpeed);
	}
	else {
		elevationMotor->Set(kShooterStop);
	}
}

bool Shooter::ShooterIsHome() {
	bool Home = elevationHome->Get();

	if (Home) {
		elevationEncoder->Reset();
		mShooterHomed = true;
	}
	return Home;
}

bool Shooter::ShooterAtMax() {
	return elevationMax->Get();
}

float Shooter::GetShooterElevation() {
	// cos(A) = b^2 + c^2 - a^2 / 2ab
	float raw = elevationEncoder->GetRaw();		// c
	SmartDashboard::PutNumber("ShooterEncoder", raw);
	return raw;
//	float angle = (kShooterLength * kShooterLength) + (raw * raw);		// b^2 + c^2
//
//	angle = angle - (kArmLength * kArmLength);   // b^2 + c^2 - a^2
//	angle /= 2 * kShooterLength * raw;			 // perform division component
//	return (acos(angle) * 360.0 / (M_PI * 2.0));
}

void Shooter::KickerStop() {
	ballKicker->Set(kKickerStop);
}

void Shooter::ShooterAim(float ElevationCmd) {
	ElevationCmd = DEADBAND_SHOOTER(ElevationCmd, 0.15);
//	ElevationCmd *= kShooterElevateSpeed;		// use auto elevate speed as limit

	if ((ElevationCmd > 0.0) && ShooterAtMax()) {
		ElevationCmd = 0.0;
	}

	if ((ElevationCmd < 0.0) && ShooterIsHome()) {
		ElevationCmd = 0.0;
	}

	SmartDashboard::PutNumber("Elevation", GetShooterElevation());
	elevationMotor->Set(-ElevationCmd);
}

void Shooter::EncoderReset() {
	elevationEncoder->Reset();
}

void Shooter::ShooterStop() {
	elevationMotor->Set(kShooterStop);
}

void Shooter::KickerMove(float speed) {
	ballKicker->Set(speed);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

