/*
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-http-request
 */

#include <WiFi.h>
#include <HTTPClient.h>

const char WIFI_SSID[] = "5층";         // 와이파이 이름
const char WIFI_PASSWORD[] = "48864886"; // 와이파이 비번

String HOST_NAME   = "http://192.168.0.199:5000"; // 라즈베리파이(서버)로 보내려는주소
String PATH_NAME   = "/products/arduino";      // 라우터를 저렇게 만들자 그냥
//String PATH_NAME   = "/products/arduino.php";      // CHANGE IT
String queryString = "temperature=26&humidity=70"; // 

void setup() {
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } // 응답 대기용 . 표시인가?
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  HTTPClient http;

  http.begin(HOST_NAME + PATH_NAME + "?" + queryString);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0) {
    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void loop() {
  
}