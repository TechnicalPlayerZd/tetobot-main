#include "robot.hpp"

pros::ADIDigitalOut pneumatic('A');
bool pneumaticExtended = false;

// ============================================================
// DRIVETRAIN MOTORS
// ============================================================
//
// Left:  ports 14 and 12 (reversed, matching your old code)
// Right: ports 13 and 11
//
// Assumption: these are the blue 600 RPM cartridges you
// mentioned earlier, mechanically geared to 360 RPM.

pros::MotorGroup leftMotors(
    {1, 2},
    pros::MotorGears::blue
);

pros::MotorGroup rightMotors(
    {-5, -3},
    pros::MotorGears::blue
);

// ============================================================
// CONTROLLER
// ============================================================

pros::Motor mechanismMotor(
    6,
    pros::MotorGears::green
);

pros::Controller master(pros::E_CONTROLLER_MASTER);

// ============================================================
// LEMLIB DRIVETRAIN
// ============================================================
//
// Track width is a placeholder because we aren't using
// odometry or autonomous movements yet.
//
// Wheel diameter: 3.25 inches
// Effective drivetrain speed: 360 RPM
// Horizontal drift: default starting value

lemlib::Drivetrain drivetrain(
    &leftMotors,
    &rightMotors,
    10.0,                       // placeholder track width
    lemlib::Omniwheel::NEW_325, // 3.25-inch wheels
    360,                        // effective drivetrain RPM
    2                           // horizontal drift
);

// ============================================================
// PID SETTINGS
// ============================================================
//
// Required to construct the LemLib chassis.
// Not used for basic tank driver control.

lemlib::ControllerSettings lateralController(
    10, 0, 3,
    3,
    1, 100,
    3, 500,
    20
);

lemlib::ControllerSettings angularController(
    2, 0, 10,
    3,
    1, 100,
    3, 500,
    0
);

// ============================================================
// ODOMETRY SENSORS
// ============================================================
//
// No IMU or tracking wheels required for expo driver control.

lemlib::OdomSensors sensors(
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr
);

// ============================================================
// EXPO DRIVE CURVES
// ============================================================

// Throttle: left and right joystick Y axes
lemlib::ExpoDriveCurve throttleCurve(
    3,      // joystick deadband
    10,     // minimum output
    1.019   // expo strength
);

// Steering curve is configured for future arcade/curvature use.
// Tank drive uses the throttle curve for each side.
lemlib::ExpoDriveCurve steerCurve(
    3,      // joystick deadband
    10,     // minimum output
    1.019   // expo strength
);

// ============================================================
// LEMLIB CHASSIS
// ============================================================

lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    sensors,
    &throttleCurve,
    &steerCurve
);

// ============================================================
// INITIALIZATION
// ============================================================

void robotInitialize() {
    robot::stop();
}

// ============================================================
// STOP
// ============================================================

namespace robot {

void stop() {
    leftMotors.move(0);
    rightMotors.move(0);
}

} // namespace robot

// ============================================================
// OP CONTROL — EXPO TANK DRIVE
// ============================================================

void robotOpcontrol() {
    while (true) {
        const int leftY = master.get_analog(
            pros::E_CONTROLLER_ANALOG_RIGHT_Y
        );

        const int rightY = master.get_analog(
            pros::E_CONTROLLER_ANALOG_LEFT_Y
        );

        // LemLib applies the configured expo curve.
        chassis.tank(leftY, rightY);

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            mechanismMotor.move(50);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            mechanismMotor.move(-50);
        } else {
            mechanismMotor.move(0);
        }

        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            pneumaticExtended = !pneumaticExtended;
            pneumatic.set_value(pneumaticExtended);
        }

        

        pros::delay(25);
    }
}