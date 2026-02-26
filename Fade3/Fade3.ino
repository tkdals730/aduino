int led = 9;          // PWM 핀
int analogPin = A0;   // 가변저항
const int fanPin = 10;
int val = 0;

void setup() {
  pinMode(led, OUTPUT);
   pinMode(fanPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(analogPin);   // 0~1023
  int pwm = val / 4;             // 0~255
  float voltage = val * (5.0 / 1023.0);

  analogWrite(fanPin, pwm);         // PWM 출력
  Serial.println(pwm);       // 전압 표시

  delay(50);
}