#include <Servo.h>

const int potPin = A0;    // 가변저항 (크놉)
const int servoPin = 9;   // 서보 신호 핀
const int Gled = 11;
const int Rled = 10;

Servo myServo;

void setup() {
  myServo.attach(servoPin);   // 서보를 9번 핀에 연결
  pinMode(Rled, OUTPUT);
  pinMode(Gled, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int val = analogRead(potPin);          // 0 ~ 1023
  int angle = map(val, 0, 1023, 0, 180); // 0 ~ 180도 변환

  myServo.write(angle);                  // 서보 각도 제어

  Serial.print("val = ");
  Serial.print(val);
  Serial.print(" | angle = ");
  Serial.println(angle);

  delay(15);  // 서보 안정 시간

  if (angle >= 30 && angle <= 150){
    digitalWrite(Gled, HIGH);
    digitalWrite(Rled, LOW);
  }else {
    digitalWrite(Gled, LOW);
    digitalWrite(Rled, HIGH);
  }
}