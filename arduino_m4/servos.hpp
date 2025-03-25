#ifndef ROBOT_SERVOS_HPP
#define ROBOT_SERVOS_HPP

#include <Arduino.h>
#include <Servo.h>

class RobotServos {

  public:

    /*  
      Initializes the servo motors
    */
    bool init();

    /*  
      Move head-turn servo to desired position
      position: 0 (home pos) to 255 (extended pos)
    */
    void turnHead(int position);

    /*  
      Move head-tilt servo to desired position
      position: 0 (home pos) to 255 (extended pos)
    */
    void tiltHead(int position);

    /*  
      Move left-arm servo to desired position
      position: 0 (home pos) to 255 (extended pos)
    */
    void moveLeftArm(int position);

    /*  
      Move left-hand servo to desired position
      position: 0 (home pos) to 255 (extended pos)
    */
    void moveLeftHand(int position);

    /*  
      Move right-arm servo to desired position
      position: 0 (home pos) to 255 (extended pos)
    */
    void moveRightArm(int position);

    /*  
      Move right-hand servo to desired position
      position: 0 (home pos) to 255 (extended pos)
    */
    void moveRightHand(int position);

  private:

    class RestrictedServo {

      public:

        RestrictedServo(int pin, int min_pos, int max_pos, bool inv);
        bool init();
        void move(int position);

      private:

        Servo servo;
        int servo_pin;
        int min_position;
        int max_position;
        bool inverted;

    };

    // CONSTANTS //
    // Servos: Pin, Minimum Position, Maximum Position, Inverting
    RestrictedServo turn_head{2, 0, 180, true};
    RestrictedServo tilt_head{1, 0, 180, false};
    RestrictedServo arm_left{0, 0, 180, false};
    RestrictedServo hand_left{3, 0, 180, false};
    RestrictedServo arm_right{5, 0, 180, true};
    RestrictedServo hand_right{4, 0, 180, true};

};

#endif