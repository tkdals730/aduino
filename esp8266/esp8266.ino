#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 32

const char* ssid = "5층";
const char* password = "48864886";

//Create an instance of the server
//specify the port to listen on as an argument
WebServer server(8080);

//threshold for cycle counts
DHT dht(DHTPIN, DHTTYPE);

float temp, humi;
String webString = "";
unsigned long previousMillis = 0;
const long interval = 2000;

void gettemphumi();
void handleevents(){
  gettemphumi();
   webString = "{\"temperature\":\"" + String(temp) + "\",\"humidity\":\"" + String(humi) + "\"}";
  Serial.println(webString);
  server.send(200, "text/plain", webString);
  yield();
}

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();
  Serial.println("=== SETUP START ===");


  // connect to wifi network
  Serial.print("connecting to ");
  Serial.println(ssid);
  
  Serial.println("=== WIFI BEGIN ===");
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // print the IP adress
  Serial.println(WiFi.localIP());

  //Start the server
  //server.on("/led",handleled);
  server.on("/events", handleevents);
  Serial.println("=== SERVER BEGIN ===");
  server.begin();
}

void loop() {
  server.handleClient();
}
void gettemphumi() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    humi = dht.readHumidity();
    temp = dht.readTemperature(false);

    if (isnan(humi) || isnan(temp)) {
      Serial.println("Falied to read dht sensor.");
      return;
    }
  }
}
