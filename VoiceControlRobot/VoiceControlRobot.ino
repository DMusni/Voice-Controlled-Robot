//define motor enable pins
int enable1 = 9;  //speed control for motor1 and motor2
int enable2 = 10; //speed control for motor3 and motor4

//define motor control pins
int m1 = 2; //motor1 to pin2
int m2 = 3; //motor2 to pin3
int m3 = 4; //motor3 to pin4
int m4 = 5; //motor4 to pin5


void setup() {
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);

  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);

  //set motor speeds
  analogWrite(enable1, 255); //m1 and m2 to max speed
  analogWrite(enable2, 255); //m3 and m4 to max speed

  Serial.begin(9600);

}

void loop() {
  //check if there is any data available to read from bluetooth module
  if(Serial.available() > 0) {
    String command = Serial.readStringUntil('\n'); //read command data
    command.trim();

    //execute correct funtion based on command
    if(command == "forward"){
      moveForward();
      delay(3000); //forward for 3 seconds
      stopMotors(); //stop moving after 
    }else if(command == "backward"){
      moveBackward();
      delay(3000); //forward for 3 seconds
      stopMotors(); 
    }else if(command == "left"){
      turnLeft(); 
      delay(1000); //turn left for 1 second
      stopMotors();
    }else if(command == "right"){
      turnRight();
      delay(1000); //turn right for 1 second
      stopMotors();
    }else if(command == "stop") {
      stopMotors();
    }else {
      Serial.println("command invalid");
    }
  }

}

void moveForward() {
  digitalWrite(m1, HIGH); //motor1 forward
  digitalWrite(m2, LOW); //motor2 forward
  digitalWrite(m3, HIGH); //motor3 forward
  digitalWrite(m4, LOW); //motor4 forward

}

void moveBackward() {
  digitalWrite(m1, LOW); //motor1 backward
  digitalWrite(m2, HIGH); //motor2 backward
  digitalWrite(m3, LOW); //motor3 backward
  digitalWrite(m4, HIGH); //motor4 backward
}

void stopMotors() {
  //all set to low ensures no current is supplied to the motor, stopping it
  digitalWrite(m1, LOW); 
  digitalWrite(m2, LOW); 
  digitalWrite(m3, LOW); 
  digitalWrite(m4, LOW); 
}

void turnLeft() {
  digitalWrite(m1, LOW); //motor1 backward
  digitalWrite(m2, HIGH); //motor2 backward
  digitalWrite(m3, HIGH); //motor3 forward
  digitalWrite(m4, LOW); //motor4 forward
}

void turnRight() {
  digitalWrite(m1, HIGH); //motor1 forward
  digitalWrite(m2, LOW);  //motor2 forward
  digitalWrite(m3, LOW);  //motor3 backward
  digitalWrite(m4, HIGH); //motor4 backward
}