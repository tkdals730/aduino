/******************************************************************************
 * step3_temperature_mqtt_esp32.ino
 * 3단계: 온도 센서 조건부 퍼블리시 (QoS 0)
 *
 * 목표: 온도가 특정 조건을 만족할 때만 MQTT 메시지를 전송
 * 토픽: device/14/temperature
 * QoS:  0 (PubSubClient publish 기본이 QoS 0)
 *
 * DHT11 배선(예시):
 *   VCC  → 3.3V
 *   GND  → GND
 *   DATA → GPIO 32 (※ 너가 실제로 꽂은 핀으로 바꿔)
 *   + 10kΩ 풀업(보통 모듈이면 내장된 경우도 많음)
 ******************************************************************************/

#include <WiFi.h>              //  ESP32는 WiFi.h
#include <PubSubClient.h>
#include <DHT.h>

// ===== Wi-Fi 설정 =====
const char *ssid     = "5층";
const char *password = "48864886";

// ===== MQTT 설정 =====
const char *MQTT_ID = "temperature_14";          //  중복되면 끊기니 고유하게
const char *TOPIC   = "device/14/temperature";   //  student_id=14

IPAddress broker(192, 168, 0, 86);               //  라즈베리파이 WiFi IP
const int MQTT_PORT = 1883;

WiFiClient wclient;
PubSubClient client(wclient);

// ===== DHT 센서 설정 =====
#define DHT_PIN   32          
#define DHT_TYPE  DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// ===== 타이밍 설정 =====
unsigned long previousMillis = 0;
const long interval = 2000;   // 2초마다 측정

// ===== 조건부 전송 설정 =====
// 방식 A: 임계값 기반
const float THRESHOLD_TEMP = 27.5;

// 방식 B: 변화폭 기반
const float CHANGE_THRESHOLD = 1.0;
float lastSentTemp = -999.0;

// ===== 조건 선택 =====
#define USE_THRESHOLD_MODE  0  // 1이면 방식A(30도 이상), 0이면 방식B(변화폭 1도)

// ===== Wi-Fi 연결 =====
void setup_wifi() {
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// ===== MQTT 재연결 =====
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect(MQTT_ID)) {
      Serial.println("connected");
      Serial.print("Publishing to: ");
      Serial.println(TOPIC);
      Serial.println();
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// ===== 전송 조건 판단 함수 =====
bool shouldPublish(float temperature) {
  // 센서 오류 방지
  if (isnan(temperature)) return false;

#if USE_THRESHOLD_MODE
  // === 방식 A: 임계값 기반 ===
  // 30도 이상일 때만 전송
  return (temperature >= THRESHOLD_TEMP);
#else
  // === 방식 B: 변화폭 기반 ===
  // 마지막 전송값과 1도 이상 차이 나면 전송
  if (fabs(temperature - lastSentTemp) >= CHANGE_THRESHOLD) {
    lastSentTemp = temperature;   //  전송하기로 했으면 기준값 갱신
    return true;
  }
  return false;
#endif
}

void setup() {
  Serial.begin(115200);

  dht.begin();

  delay(100);
  setup_wifi();

  client.setServer(broker, MQTT_PORT);

  Serial.println("3단계: 온도 조건부 MQTT 퍼블리시");
  Serial.println("=================================");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // 1) 온도 읽기
    float temperature = dht.readTemperature();

    // 2) 센서 읽기 실패 처리
    if (isnan(temperature)) {
      Serial.println("[에러] DHT 읽기 실패 (NaN)");
      return;
    }

    // 3) 조건 확인 후 전송
    if (shouldPublish(temperature)) {
      char tempStr[10];
      dtostrf(temperature, 4, 1, tempStr);

      client.publish(TOPIC, tempStr); //  QoS0

      Serial.print("[전송] ");
      Serial.print(TOPIC);
      Serial.print(" => ");
      Serial.println(tempStr);

      // 방식 A(임계값)에서는 lastSentTemp 갱신이 필요하면 여기서 해도 됨(선택)
      // lastSentTemp = temperature;
    } else {
      Serial.print("[스킵] 온도: ");
      Serial.print(temperature, 1);
      Serial.println(" ℃ - 조건 미충족");
    }
  }
}