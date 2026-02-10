
int AA = 6;               //모터A의 A를 6번 핀에 배치
int AB = 7;               //모터A의 B를 7번 핀에 배치

const int buzzer = 8;
const int trig_pin = 9;
const int echo_pin = 10;
float timing = 0.0;
float distance = 0.0;

void setup() {
  // put your setup code here, to run once:
  pinMode(AA, OUTPUT);
  pinMode(AB, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(trig_pin, LOW);
  digitalWrite(buzzer, LOW);
    
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(trig_pin, LOW);
  delay(2);
  
  digitalWrite(trig_pin, HIGH);
  delay(10);
  digitalWrite(trig_pin, LOW);  
  timing = pulseIn(echo_pin, HIGH);
  distance = (timing * 0.034) / 2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("cm | ");
  Serial.print(distance / 2.54);
  Serial.println("in");
  
    
  if (distance <= 50) {
  	tone(buzzer, 500);
  } else {
  	noTone(buzzer);
  }
  
  delay(100);
  if(distance > 50){
    digitalWrite(AA, HIGH);          //모터A를 정회전
    digitalWrite(AB, LOW);
  }else{
    digitalWrite(AA, LOW);           //모터A를 정지
    digitalWrite(AB, LOW);
  }
  
}

