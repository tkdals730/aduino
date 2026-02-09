const int ledPin = 12;
int sensorPin = A0;
int sensorValue = 0;
const int YledPin = 9;
const int buttonPin = 2;
int buttonState = 0;
const int ZledPin = 10;

void setup() {
  // put your setup code here, to run once:
    // pinMode(LED_BUILTIN, OUTPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(YledPin, OUTPUT);
    pinMode(ZledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    buttonState = digitalRead(buttonPin);
    sensorValue = analogRead(sensorPin);
    if(sensorValue <= 500){
      Serial.println("전압이 약합니다.");
    }
    // 전압이 0이면 점등하는 led
    if(sensorValue == 0){
      digitalWrite(ZledPin, HIGH);
    }else{
      digitalWrite(ZledPin, LOW);
    }
    //Serial.println(buttonState);
    //digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(sensorValue);
if (buttonState == HIGH){
  // 불켜기
    Serial.println("LED ON");
    digitalWrite(ledPin, HIGH);
    digitalWrite(YledPin, LOW);
    //delay(500);
    delay(sensorValue);
}else {
    // 불끄기
    digitalWrite(ledPin, LOW);
    digitalWrite(YledPin, HIGH);
    delay(sensorValue);
    //delay(500);
}

    //digitalWrite(LED_BUILTIN, LOW);
}
