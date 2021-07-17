
#include "arduino_secrets.h"
#include <ESP8266HTTPClient.h>
#include "Arduino_JSON.h"


const String SERVER_NAME = "http://api.openweathermap.org";

String getMeteo() {

  String payload = "";

  if (WiFi.status() == WL_CONNECTED) {
    
    WiFiClient wifiClient; 
    
    HTTPClient http;

    String serverPath = SERVER_NAME + "/data/2.5/weather?q=" + CITY + "&appid=" + SECRET_APPID;
    http.begin(wifiClient, serverPath);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      payload = http.getString();
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
    return payload;
  } else {
    Serial.println("WiFi Disconnected");
  }
}

bool isRaining(String meteoResponse) {
  
  JSONVar meteo = JSON.parse(meteoResponse);
  if (JSON.typeof(meteo) == "undefined") {
      Serial.println("Parsing input failed!");
      return false;
    } else {
      JSONVar curStat = meteo["weather"][0]["main"];
      Serial.println(curStat);
      if (JSON.stringify(curStat) != "Rain") {
        return false;
      } else {
        return true;
      }
  }
}
