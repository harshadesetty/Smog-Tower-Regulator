#define BLYNK_TEMPLATE_ID "TMPL3GhT-kNkn"
#define BLYNK_TEMPLATE_NAME "airmonitoring"
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#define BLYNK_AUTH "LwL_eHgimQ-__6Po8W9EHKJHMTGe2-5f"
#define WIFI_SSID "Harsha"
#define WIFI_PASS "12345678"

#define MQ135_PIN A0 

BlynkTimer timer;

void sendSensorData()
{
  int sensorValue = analogRead(MQ135_PIN);
  float voltage = sensorValue/12;
  int airQualityOutput;
  
  if(sensorValue <=350 ){
    airQualityOutput = 1;
  }
  else if(sensorValue > 350 && sensorValue <= 750){
    airQualityOutput = 2;
  }
  else {
    airQualityOutput = 3;  
  }
  
  Blynk.virtualWrite(V0, voltage); 
  Blynk.virtualWrite(V1, airQualityOutput);
  Blynk.virtualWrite(V2, sensorValue);
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH, WIFI_SSID, WIFI_PASS);

  timer.setInterval(1000L, sendSensorData); 
}

void loop()
{
  Blynk.run();
  timer.run();
}
