// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef SHOOTER_H
#define SHOOTER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

#define DEADBAND_SHOOTER(val, limit)	((fabs(val) < limit) ? 0.0 : val)


/**
 *
 *
 * @author ExampleAuthor
 */
class Shooter: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<SpeedController> elevationMotor;
	std::shared_ptr<SpeedController> flyWheelMotor;
	std::shared_ptr<Encoder> elevationEncoder;
	std::shared_ptr<DigitalInput> elevationHome;
	std::shared_ptr<DigitalInput> elevationMax;
	std::shared_ptr<SpeedController> ballKicker;
	std::shared_ptr<DigitalInput> ballKickSensor;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	const float kFlyWheelHighSpeed = 1.0;
	const float kFlyWheelLowSpeed = 0.5;
	const float kFlyWheelReverseSpeed = -1.0;
	const float kFlyWheelStop = 0.0;

	const float kShooterElevateSpeed = 0.75;
	const float kShooterLowerSpeed = -0.75;
	const float kShooterStop = 0.0;

	const float kKickerExtendSpeed = 1.0;
	const float kKickerRetractSpeed = -0.3;
	const float kKickerStop = 0.0;

	float kShooterLength;
	float kArmLength;
	float kCountsPerInch;

	bool mShooterHomed = false;
	Preferences* prefs = Preferences::GetInstance();

public:
	Shooter();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	//Fly Wheel Manipulation public functions
	void FlyWheelReverse();
	void FlyWheelStop();
	void FlyWheelHighSpeed();
	void FlyWheelLowSpeed();

	// Ball Kicker manipulation
	void KickerExtend();
	void KickerRetract();
	void KickerStop();
	bool KickerDetect();
	void KickerMove(float speed);

	// Elevation Manipulation public functions
	void ShooterElevate();
	void ShooterLower();
	void ShooterStop();
	bool ShooterIsHome();
	bool ShooterAtMax();
	float GetShooterElevation();

	void EncoderReset();

	// Teleop public methods
	void ShooterAim(float ElevationCmd);
};

#endif
