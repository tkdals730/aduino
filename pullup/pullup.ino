const int ledPin = 13;
const int buttonPin = 2;
int buttonState = 0;


void setup() {
  // put your setup code here, to run once:
    // pinMode(LED_BUILTIN, OUTPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
    buttonState = digitalRead(buttonPin);

    //digitalWrite(LED_BUILTIN, HIGH);
if (buttonState == LOW){
  // 불켜기
    digitalWrite(ledPin, HIGH);
    // delay(500);
}else {
    // 불끄기
    digitalWrite(ledPin, LOW);
    // delay(500);
}

    //digitalWrite(LED_BUILTIN, LOW);
}
