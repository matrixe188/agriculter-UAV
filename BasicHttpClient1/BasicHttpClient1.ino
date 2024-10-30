/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */
 #define BLYNK_TEMPLATE_ID "TMPL39zOcNCj5"
#define BLYNK_TEMPLATE_NAME "DHT"
#define BLYNK_AUTH_TOKEN "UguQV7PP0smmLxH5J4ffuaGVepQQxd2t"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <ESP32PWM.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

#define DHTPIN 26   
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
int temp;
int hum;
int mq;
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Data Bekkaaa";
char pass[] = "1234567890";
BlynkTimer timer;

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;
String url="";

void myTimerEvent()
{
     int sensorReading   = analogRead(27);
     PinMode();
    
      
        float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println(h);
  mq=random(20,40);
  temp=random(25,27);
  hum=random(68,79);
  delay(4000);
    Blynk.virtualWrite(V0,temp);
     Blynk.virtualWrite(V1,hum);
      Blynk.virtualWrite(V2,mq);
     
}


void setup() {

    USE_SERIAL.begin(115200);
    
  Serial.begin(115200);
    Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP("Data Bekkaaa", "1234567890");

}

void loop() {
    // wait for WiFi connection
    url="https://api.thingspeak.com/update?api_key=M6NG8SKGTC4J77UT&field1=";
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;
        mq=random(20,40);
  temp=random(25,27);
  hum=random(68,79);

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
       
         url=url+String(temp);
  url=url+"&field2=";
  url=url+String(hum);
  url=url+"&field3=";
  url=url+String(mq); http.begin(client,url); 

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(5000);
     Blynk.run();
  timer.run();
}
