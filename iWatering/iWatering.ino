
#include <ESP8266WiFi.h> //ESP8266
#include "arduino_secrets.h"
#include "Meteo.h"

const int OUT_PIN_1 = 14;
const int SENSOR_PIN = 0;
const int OUT_PIN_2 = 12;
int sensorInit;  // initial value
int sensorVal;   // light reading

void setup() {

  Serial.begin(115200);
  Serial.println("Restarting in 10 seconds");

  WiFi.mode(WIFI_STA);
  WiFi.begin(SECRET_SSID, SECRET_PWD);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(OUT_PIN_1, OUTPUT);
  pinMode(OUT_PIN_2, OUTPUT);
  digitalWrite(OUT_PIN_1, LOW);
  digitalWrite(OUT_PIN_2, LOW);
  sensorInit = analogRead(SENSOR_PIN);
  

}

void loop() {

  sensorVal = analogRead(SENSOR_PIN);
  
  String meteo = getMeteo();
  if(!isRaining(meteo) && sensorVal < sensorInit) {
      Serial.println("Start watering");
      digitalWrite(OUT_PIN_1, HIGH);
      digitalWrite(OUT_PIN_2, HIGH);
      delay(180000);
      digitalWrite(OUT_PIN_1, LOW);
      digitalWrite(OUT_PIN_2, LOW);
  } else {
    Serial.println("Moisture level ok");
    delay(600000);
  }
  


}
