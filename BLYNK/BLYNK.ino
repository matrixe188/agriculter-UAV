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

void myTimerEvent()
{
     int sensorReading   = analogRead(27);
      int range = map(sensorReading,   sensorMin, sensorMax, 0, 3);
      Serial.println(range);
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

void setup()
{
  Serial.begin(115200);
  
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();

}
