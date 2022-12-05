/*
   Скетч для управления судомоделью с использованием
   регулятора скорости коллекторных моторов (ESC)
*/
#include <Servo.h>
Servo servo;
Servo motor;

int maxAngle[2] = {10, 170};
const int neutralAngle = 90;
int directionServo = 0;

int maxSpeed[2] = {1000, 2000};
const int neutralPosition = 1500;

int directionFlag = 0;
int _speed = maxSpeed[directionFlag];

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  servo.write(neutralAngle);
  motor.attach(3);
  motor.write(neutralPosition);
  delay(1000);
}

void loop() {
  if (Serial.available() != 0) {
    char valueRead = Serial.read();
    if (valueRead >= '0' && valueRead <= '9') {
      _speed = map((valueRead - '0'), 0, 9, neutralPosition, maxSpeed[directionFlag]);
    } else if (valueRead == 'F') forward(_speed);
    else if (valueRead == 'B') backward();
    else if (valueRead == 'L') left();
    else if (valueRead == 'R') right();
    else if (valueRead == 'G') forwardLeft(_speed);
    else if (valueRead == 'I') forwardRight(_speed);
    else if (valueRead == 'H') backLeft();
    else if (valueRead == 'J') backRight();

    else if (valueRead == 'W') directionFlag = 1;
    else if (valueRead == 'w') directionFlag = 0;
    else if (valueRead == 'U') directionServo = 1;
    else if (valueRead == 'u') directionServo = 0;
    else Stop();
  }
}



void forward(int _s) {
  motor.writeMicroseconds(_s);
}
void backward() {
  if (directionFlag == 1) motor.writeMicroseconds(neutralPosition - 200);
  else motor.writeMicroseconds(neutralPosition + 200);
}
void left() {
  if (directionServo == 0) servo.write(maxAngle[0]);
  else servo.write(maxAngle[1]);
}
void right() {
  if (directionServo == 0) servo.write(maxAngle[1]);
  else servo.write(maxAngle[0]);
}
void forwardLeft(int _s) {
  motor.writeMicroseconds(_s);
  if (directionServo == 0) servo.write(maxAngle[0]);
  else servo.write(maxAngle[1]);
}
void forwardRight(int _s) {
  motor.writeMicroseconds(_s);
  if (directionServo == 0) servo.write(maxAngle[1]);
  else servo.write(maxAngle[0]);
}
void backLeft() {
  if (directionFlag == 1) motor.writeMicroseconds(neutralPosition - 200);
  else motor.writeMicroseconds(neutralPosition + 200);
  if (directionServo == 0) servo.write(maxAngle[0]);
  else servo.write(maxAngle[1]);
}
void backRight() {
  if (directionFlag == 1) motor.writeMicroseconds(neutralPosition - 200);
  else motor.writeMicroseconds(neutralPosition + 200);
  if (directionServo == 0) servo.write(maxAngle[1]);
  else servo.write(maxAngle[0]);
}
void Stop() {
  servo.write(neutralAngle);
  motor.write(neutralPosition);
}
