int AA = 6;               //모터A의 A를 6번 핀에 배치
int AB = 7;               //모터A의 B를 7번 핀에 배치


void setup() {
  // put your setup code here, to run once:
  pinMode(AA, OUTPUT);
  pinMode(AB, OUTPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(AA, HIGH);          //모터A를 정회전
  digitalWrite(AB, LOW);
  delay(1000); //여기서 둘다 HIGH를 쓰면 쇼트의 위험성이있다.
 
  digitalWrite(AA, LOW);           //모터A를 정지
  digitalWrite(AB, LOW);
  delay(250);
  
  digitalWrite(AA, LOW);           //모터A를 역회전     
  digitalWrite(AB, HIGH);
  delay(1000);
}
