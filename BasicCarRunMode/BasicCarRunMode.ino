/**********************************************************************
  Product     : Freenove 4WD Car for UNO
  Auther      : www.freenove.com
  Modification: 2019/08/03
**********************************************************************/
#define MOTOR_DIRECTION     1 //If the direction is reversed, change 0 to 1

//Motor Pins
#define PIN_DIRECTION_RIGHT 3
#define PIN_DIRECTION_LEFT  4
#define PIN_MOTOR_PWM_RIGHT 5
#define PIN_MOTOR_PWM_LEFT  6

//Buzzer for sounds
#define PIN_SOUNDMAKER A0

void setup() {
  pinMode(PIN_DIRECTION_LEFT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_LEFT, OUTPUT);
  pinMode(PIN_DIRECTION_RIGHT, OUTPUT);
  pinMode(PIN_MOTOR_PWM_RIGHT, OUTPUT);

  pinMode(PIN_SOUNDMAKER, OUTPUT);
}

void loop() {
  buzzer();
  delay(10);
  buzzer();
  delay(1000);


  //Move forward
  targetMove(1600);

  //Make Noise
  buzzer();
  delay(1000);
  targetMove(1000);
  //Stop
  motorRun(0, 0);
  delay(20000);
}

void motorRun(int speedl, int speedr) { //This one takes the speeds of the left and right thing, and based on the sign of the integer, (+ or -) it makes the motor turn one way, or the other.
  int dirL = 0, dirR = 0;
  if (speedl > 0) { //Based on direction, modifies the speed of the left side wheels!
    dirL = 0 ^ MOTOR_DIRECTION;
  } else {
    dirL = 1 ^ MOTOR_DIRECTION;
    speedl = -speedl;
  }

  if (speedr > 0) { // Based on direction, modifies the speed of the right side wheels
    dirR = 1 ^ MOTOR_DIRECTION;
  } else {
    dirR = 0 ^ MOTOR_DIRECTION;
    speedr = -speedr;
  }
  digitalWrite(PIN_DIRECTION_LEFT, dirL);
  digitalWrite(PIN_DIRECTION_RIGHT, dirR);
  analogWrite(PIN_MOTOR_PWM_LEFT, speedl);
  analogWrite(PIN_MOTOR_PWM_RIGHT, speedr);
}

void buzzer() {
  digitalWrite(PIN_SOUNDMAKER, HIGH);
  delay(100);
  digitalWrite(PIN_SOUNDMAKER, LOW);
}

void targetMove(int distanceInTime) { //Distance in centimeters, speed in cm/s
  int calcSpeed = 30; //The calculated average speed of the robot car at motor speed 100. In cm/s
  // int motSpeed = calcSpeed/speed * 100; //100 comes from the initial variable for calcSpeed
  // int distanceInTime = (distance/calcSpeed) * 1000; //1000 comes from seconds to milliseconds
  motorRun(100, 100);
  delay(distanceInTime);
  motorRun(0, 0);
}