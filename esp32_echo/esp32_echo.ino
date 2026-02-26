/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-ultrasonic-sensor
 */

#define TRIG_PIN 26 // 트리거핀 번호
#define ECHO_PIN 27 // 에코핀 번호

float duration_us, distance_cm;

void setup() {
  // begin serial port
  Serial.begin (9600);

  // 트리거핀을 출력으로
  pinMode(TRIG_PIN, OUTPUT);
  // 에코핀을 입력으로
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // 거리 계산
  distance_cm = 0.017 * duration_us;

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(3000);
}