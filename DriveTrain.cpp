//Value to Tune the acceleration speed of the robot
const int MOTOR_ACCEL_LIMIT = 2; 

float s_lastL = 0;
float s_lastR = 0;

//Example Function for Controlling Motors, function should be called within the drive control loop, with lSpeed and rSpeed being set to the Joystick Axis
void SetMotors(int lSpeed, int rSpeed) {
    //Cap lSpeed and rSpeed to Accel limit
    if ((lSpeed - s_lastL) > MOTOR_ACCEL_LIMIT) {
      lSpeed = s_lastL + MOTOR_ACCEL_LIMIT;
    }
    if ((lSpeed - s_lastL) < -MOTOR_ACCEL_LIMIT) {
      lSpeed = s_lastL - MOTOR_ACCEL_LIMIT;
    }
    if ((rSpeed - s_lastR) > MOTOR_ACCEL_LIMIT) {
      rSpeed = s_lastR + MOTOR_ACCEL_LIMIT;
    }
    if ((rSpeed - s_lastR) < -MOTOR_ACCEL_LIMIT) {
      rSpeed = s_lastR - MOTOR_ACCEL_LIMIT;
    }
    
    s_lastL = lSpeed;
    s_lastR = rSpeed;

    //Set Speeds to Motors
    if (lSpeed == 0) {
      lDrive.stop(brakeType::brake);
    } else {
      lDrive.spin(directionType::fwd, lSpeed, velocityUnits::pct);
    }
    if (rSpeed == 0) {
      rDrive.stop(brakeType::brake);
    } else {
      rDrive.spin(directionType::fwd, rSpeed, velocityUnits::pct);
}
  