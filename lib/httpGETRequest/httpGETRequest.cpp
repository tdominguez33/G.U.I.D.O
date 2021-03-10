#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>


String httpGETRequest(const char* http_serverName) {

  HTTPClient http;

  http.begin(http_serverName);
  
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();

  return payload;
}

String httpsGETRequest(const char* https_servername) {
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;

  String JSON;

  if (https.begin(*client, https_servername)) {  // HTTPS
    Serial.print("[HTTPS] GET... ");
    int httpCode = https.GET();

    // httpCode sera negativo si hay un error
    if (httpCode > 0) {
      Serial.printf("code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK) {
        JSON = https.getString();
      }
    } else {
      Serial.printf("failed, error: %s\n\r", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n\r");
  }
  return JSON;
}
