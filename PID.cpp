//An Example PID Function which would Drive the Robot Forward or Backwards
void DriveDistance(float distance, float maxTime)
  {
    //Reset the Rotation of Both Encoders
    lDrive1.resetPosition();
    rDrive1.resetPosition();

    //Calculate number of degrees needed to turn to reach target
    float rotationGoal = (360 * distance) / wheelCircumfrence;

    //Acceleration times at beginning, to prevent tipping if neccesary
    const float maxSpeed = 100;
    const float accelTime = 500;

    //Constant Values, These are to be tuned as per the robot
    
    //Proportional Constant | Higher Value will cause more jerk and rebound, lower will cause longer decel
    const float Kp = 0.25;

    //Integral Constant | Used to Add small amount of Movement at end if robot undershoots
    const float Ki = 0;

    //Derivative Constant | Used to Add small amount of Movement at end if robot undershoots
    const float Kd = 0;

    //DO NOT ADJUST VALUES BELOW THIS POINT
    
    //Rotation Error of Each side of the robot
    float lError = 0;
    float rError = 0;

    float lIntegral = 0;
    float rIntegral = 0;

    float lDerivative = 0;
    float rDerivative = 0;

    float lLastError = 0;
    float rLastError = 0;

    float lMotorSpeed = 0;
    float rMotorSpeed = 0;

    float doneTime = 0;
    
    float curMaxSpeed = 0;
    while(true){       
      //Calculates Error | The Degrees Remaining until the wheels reach the target Degrees
      lError = rotationGoal - lDrive1.rotation(deg);
      rError = rotationGoal - rDrive1.rotation(deg);

      lIntegral += lError;
      rIntegral += rError;

      //Only Engage Integral one Robot is closer to Target
      if(lError > 200 || lError < -200)
      {
        lIntegral = 0;
      }
      if(rError > 200 || rError < -200)
      {
        rIntegral = 0;
      }

      lDerivative = lError - lLastError;
      rDerivative = rError - rLastError;

      lLastError = lError;
      rLastError = rError;

      //Calculate Motor speed to be assigned to Wheels
      lMotorSpeed = Kp * lError + Ki * lIntegral + Kd * lDerivative;
      rMotorSpeed = Kp * rError + Ki * rIntegral + Kd * rDerivative;

      //Calculate Max speed at current time based on acceleration Time and MaxMaxSpeed
      if(doneTime < accelTime)
      {
        if(distance < 0)
          curMaxSpeed = -(doneTime / (accelTime / maxSpeed));
        else
          curMaxSpeed = doneTime / (accelTime / maxSpeed;
      }   
      
      //Decide When to break out of PID Loop
      if(doneTime > maxTime)
      {
        rDrive.spin(fwd, 0, pct);
        lDrive.spin(fwd, 0, pct);
        break;
      }    
      
      //Cap Motor Speeds to Current Max Speed
      if(distance > 0)
      {
        lMotorSpeed = curMaxSpeed < lMotorSpeed ? curMaxSpeed : lMotorSpeed;
        rMotorSpeed = curMaxSpeed < rMotorSpeed ? curMaxSpeed : rMotorSpeed;
      }
      else
      {
        lMotorSpeed = curMaxSpeed > lMotorSpeed ? curMaxSpeed : lMotorSpeed;
        rMotorSpeed = curMaxSpeed > rMotorSpeed ? curMaxSpeed : rMotorSpeed;
      }

      //Apply Speed values to motors
      lDrive.spin(fwd, lMotorSpeed, pct);
      rDrive.spin(fwd, rMotorSpeed, pct);

      wait(15, msec);
      doneTime += 15;
    }
  }