#pragma once

/* USER INTERFACE */
#define BLE_PAIR_BUTTON_PIN 22
#define BLE_STATUS_LED_PIN 10

/* MOTORS */
#define LEFT_MOTOR_PORT 3
#define RIGHT_MOTOR_PORT 4
#define MINIMUM_SPEED_ABS 40
#define MINIMUM_DIRECTION_ABS 40

/* SERVOS */
#define SERVO_TURN_HEAD_PIN 2
#define SERVO_TILT_HEAD_PIN 5
#define SERVO_ARM_LEFT_PIN 4
#define SERVO_HAND_LEFT_PIN 7
#define SERVO_ARM_RIGHT_PIN 6
#define SERVO_HAND_RIGHT_PIN 3
#define SERVO_TURN_HEAD_INITIAL 90
#define SERVO_TILT_HEAD_INITIAL 90
#define SERVO_ARM_LEFT_INITIAL 90
#define SERVO_HAND_LEFT_INITIAL 90
#define SERVO_ARM_RIGHT_INITIAL 90
#define SERVO_HAND_RIGHT_INITIAL 90

/* EYES */
#define EYE_GREEN_PIN 8
#define EYE_RED_PIN 9

/* STATES */
enum class BLEState : uint8_t { 
    Advertising, Connecting, Connected 
};
enum class RobotState : uint8_t { 
    Disconnected, Authentication, Running, Paused, Error 
};
enum class RobotValue : uint8_t { 
    BLEState, RobotState, // Robot State Variables
    DriveSpeed, DriveDirection, // Driving Variables
    ServoTurnHead, ServoTiltHead, ServoArmLeft, ServoHandLeft, ServoArmRight, ServoHandRight, // Servo Variables
    EyeColor, EyeStyle // Eye Variables
};
