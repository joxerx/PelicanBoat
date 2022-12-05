#include <Servo.h>
#define IN1 2
#define IN2 4
#define ENA 3
Servo servo;  // Создаем объект

int directionFlag = 0;
int directionServo = 0;

int _speed;

void setup() {
	Serial.begin(9600);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(ENA, OUTPUT);
	analogWrite(ENA, 200);
	servo.attach(9);   // Указываем объекту класса Servo, что серво присоединен к пину 9
	servo.write(90);   // Выставляем начальное положение 
}

void loop() {
    if (Serial.available() != 0) {
        char valueRead = Serial.read();
        if (valueRead >= '0' && valueRead <= '9') {
            _speed = map((valueRead - '0'), 0, 9, 0, 255);
        }
        else if (valueRead == 'F') forward(_speed);
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
        else stop();
    }
}

void forward(int s) {
    analogWrite(ENA, s);
    if (directionFlag == 0) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }
    else
    {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
    servo.write(90);
}
void backward(int s) {
    analogWrite(ENA, s);
    if (directionFlag == 0) {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
    else
    {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }
    servo.write(90);
}
void forwardLeft(int s) {
    analogWrite(ENA, s);
    if (directionFlag == 0) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }
    else
    {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
    if (directionServo == 1) servo.write(10);
    else servo.write(170);
}
void left() {
    if (directionServo == 1) servo.write(10);
    else servo.write(170);
}
void backLeft(int s) {
    analogWrite(ENA, s);
    if (directionFlag == 0) {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
    else
    {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }
    if (directionServo == 1) servo.write(10);
    else servo.write(170);
}
void forwardRight(int s) {
    analogWrite(ENA, s);
    if (directionFlag == 0) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }
    else
    {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
    if (directionServo == 1) servo.write(170);
    else servo.write(10);
}
void right() {
    if (directionServo == 1) servo.write(170);
    else servo.write(10);
}
void backRight(int s) {
    analogWrite(ENA, s);
    if (directionFlag == 0) {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
    else
    {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }
    if (directionServo == 1) servo.write(170);
    else servo.write(10);
}
void stop() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    servo.write(90);
}
