/*
   -- New project --

   This source code of graphical user interface
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.8 or later version
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/
     - for ANDROID 4.11.1 or later version;
     - for iOS 1.9.1 or later version;

   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE    DHT11     // DHT 11
#define DHTPIN 2     // Digital pin connected to the DHT sensor 

DHT_Unified dht(DHTPIN, DHTTYPE);

// RemoteXY connection settings
#define REMOTEXY_SERIAL_RX 3
#define REMOTEXY_SERIAL_TX 4
#define REMOTEXY_SERIAL_SPEED 9600



// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 101 bytes
  { 255,0,0,30,0,94,0,16,31,1,68,50,0,52,63,26,8,36,135,84,
  101,109,112,101,114,97,116,117,114,101,0,72,117,109,105,100,105,116,121,0,
  67,4,20,12,26,10,2,26,11,67,4,20,28,26,10,2,26,11,129,0,
  20,8,22,3,17,84,101,109,112,101,114,97,116,117,114,101,32,40,67,41,
  0,129,0,20,24,18,3,17,72,117,109,105,100,105,116,121,32,40,37,41,
  0 };

// this structure defines all the variables and events of your control interface
struct {

  // output variables
  float onlineGraph_1_var1;
  float onlineGraph_1_var2;
  char Temp[11];  // string UTF8 end zero
  char Hum[11];  // string UTF8 end zero

  // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup()
{
  RemoteXY_Init ();

  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));


}

void loop()
{
  RemoteXY_Handler ();

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    RemoteXY.onlineGraph_1_var1=event.temperature;
    dtostrf(event.temperature, 0, 1, RemoteXY.Temp); 
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    RemoteXY.onlineGraph_1_var2=event.relative_humidity;
    dtostrf(event.relative_humidity, 0, 1, RemoteXY.Hum);
  }
}
