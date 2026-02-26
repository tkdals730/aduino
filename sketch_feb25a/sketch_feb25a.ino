#include <WiFi.h>
#include <WebSocketsClient.h>
#include <SocketIoClient.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 32          // DHT22 DATA 핀 (원하는 GPIO로 변경 가능)
#define LED_PIN 2          // ESP32 보드 내장 LED는 보통 2번(GPIO2)

const char* ssid = "5층";
const char* password = "48864886";

//  라즈베리파이(서버) IP
const char* serverIp = "192.168.0.21";   // 예: 라즈베리파이 IP
const int   port     = 5000;             // 예: 서버 포트 (Socket.IO 포트)

SocketIoClient webSocket;
DHT dht(DHTPIN, DHTTYPE);

float temp = 0.0;
float humi = 0.0;

unsigned long previousMillis = 0;
const unsigned long interval = 5000; // 5초마다 전송

bool ledState = false;

// ---- Socket.IO 이벤트 핸들러 ----
void handleConnect(const char * payload, size_t length) {
  Serial.println("[SocketIO] Connected!");

  // (선택) 방 참가 같은 거 하고 싶으면 서버 이벤트명에 맞춰 emit
  // webSocket.emit("join_dev", "{\"room\":\"DEV\"}");
}

void handleLedControl(const char * payload, size_t length) {
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);

  Serial.print("[SocketIO] led_control -> ");
  Serial.println(ledState);
}

// ---- 센서 읽기 ----
bool getTempHumi() {
  humi = dht.readHumidity();
  temp = dht.readTemperature(); // 섭씨

  if (isnan(humi) || isnan(temp)) {
    Serial.println("Failed to read DHT sensor.");
    return false;
  }
  return true;
}

// ---- events 전송 ----
void sendEvents() {
  if (!getTempHumi()) return;

  // JSON 문자열 만들기
  String webString = "{\"temperature\":\"" + String(temp) + "\",\"humidity\":\"" + String(humi) + "\"}";
  Serial.print("[Send] ");
  Serial.println(webString);

  // emit은 char* 필요해서 변환
  char ch[80];
  webString.toCharArray(ch, sizeof(ch));

  webSocket.emit("events", ch);
}

void setup() {
  Serial.begin(115200);
  delay(300);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  // Socket.IO 이벤트 바인딩
  webSocket.on("connect", handleConnect);
  webSocket.on("led_control", handleLedControl);

  // 서버 접속 시작
  webSocket.begin(serverIp, port);
}

void loop() {
  webSocket.loop(); // Socket.IO 유지

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    sendEvents();
  }

  delay(10);
}