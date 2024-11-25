#include <Servo.h>    // library to control servo motor
#include <AFMotor.h>  // used to control the dc motors using the motor shield

// ultrasonic distance sensor pins
const int Echo = A0;  // listens for signals
const int Trig = A1;  // sends signals

const int servoMotor = 10;  // servo motor to arduino pin 10

const int Speed = 170;  // speed of the DC motors
const int spoint = 120; // servo motor starting point (spoint)

char value;   // stores commands received via Bluetooth
int distance; // stores distance from the ultrasonic sensor

int distanceLeft = 0;    // tracks left distance when checking obstacles
int distanceRight = 0;    // tracks right distance when checking obstacles

Servo servo;  // create servo object to control servo motor

// Connect DC motors to ports on the motor shield
AF_DCMotor M1(1);   // DC motor on port 1
AF_DCMotor M2(2);   // DC motor on port 2
AF_DCMotor M3(3);   // DC motor on port 3
AF_DCMotor M4(4);   // DC motor on port 4

void setup() {  

  Serial.begin(9600);  // initialize serial communication
  
  pinMode(Trig, OUTPUT); // set Trig pin as output (to send ultrasonic pulses)
  pinMode(Echo, INPUT); // set Echo pin as input (to receive pulses) 
  
  servo.attach(servoMotor); // attach servo to the servo motor pin (arduino pin 10)

  M1.setSpeed(Speed); // set speed for motor 1
  M2.setSpeed(Speed); // set speed for motor 2
  M3.setSpeed(Speed); // set speed for motor 3
  M4.setSpeed(Speed); // set speed for motor 4
}

void loop() {
  voicecontrol();
}

void voicecontrol() {

  if (Serial.available() > 0) {
    String value = Serial.readString();
    Serial.println(value);

    if (value == "forward") {
      moveForward();
    } else if (value == "back") {
      moveBack();
    } else if (value == "left") {
      distanceLeft = lookLeft();  // measure distance on the left
      servo.write(spoint);
      if (distanceLeft >= 10 ) {  // if distanc on left is > 10, turn left
        turnLeft();
        delay(500);
        Stop();
      } else if (distanceLeft < 10) { //distance on left is < 10, dont move
        Stop();
      }
    } else if (value == "right") {
      distanceRight = lookRight();
      servo.write(spoint);
      if (distanceRight >= 10 ) {
        turnRight();
        delay(500);
        Stop();
      } else if (distanceRight < 10) {
        Stop();
      }
    } else if (value == "stop") {
      Stop();
    }
  }
}

// Ultrasonic sensor distance reading function
int measureDistance() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  
  digitalWrite(Trig, HIGH);  // send a pulse
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  long t = pulseIn(Echo, HIGH); // measure how long the pulse takes
  long cm = t / 29 / 2; // convert to centimeters
  
  return cm;
}

// move forward
void moveForward() { 
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
// move back
void moveBack() { 
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}
// turn right
void turnRight() { 
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}
// turn left
void turnLeft() { 
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}
// stop all motors
void Stop() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}

int lookRight() {
  servo.write(60);
  delay(800);
  return measureDistance();
}
int lookLeft() {
  servo.write(180); // turn 180 degrees
  delay(800);
  return measureDistance(); // measure distance
}
