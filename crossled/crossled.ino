const int ledPin = 12;
const int YledPin = 9;
const int buttonPin = 2;
int buttonState = 0;


void setup() {
  // put your setup code here, to run once:
    // pinMode(LED_BUILTIN, OUTPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(YledPin, OUTPUT);
    pinMode(buttonPin, INPUT);
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    buttonState = digitalRead(buttonPin);
    //Serial.println(buttonState);
    //digitalWrite(LED_BUILTIN, HIGH);
if (buttonState == HIGH){
  // 불켜기
    Serial.println("LED ON");
    digitalWrite(ledPin, HIGH);
    digitalWrite(YledPin, LOW);
    //delay(500);
}else {
    // 불끄기
    digitalWrite(ledPin, LOW);
    digitalWrite(YledPin, HIGH);
    //delay(500);
}

    //digitalWrite(LED_BUILTIN, LOW);
}
