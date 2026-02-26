#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "5층";
const char* password = "48864886";
String serverURL = "http://192.168.0.86:5000/ping";
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("====ESP32 접속 테스트 시작===");
  WiFi.begin(ssid,password);
  Serial.print("WiFi 연결 중");
  
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi 연결 성공");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());
  }
void loop() {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(serverURL);
    int httpCode = http.GET();
      if (httpCode == 200) {
      String response = http.getString();
      Serial.println("서버 접속 성공! 응답: " + response);
      } else {
      Serial.println("서버 접속 실패! 코드: " + String(httpCode));
    }
    http.end();
  } else {
    Serial.println("WiFi끊김!");
  }
  delay(3000);

}
