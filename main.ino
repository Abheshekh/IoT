#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp0;
Adafruit_MCP23017 mcp1;

char auth[] = "AaD53SEVaELuneWTjjAS1XoolFoaolGw";
char ssid[] = "Gautham";
char pass[] = "1234567890";

int stairs = 1;
int HallL1 = 2;
int HallL2 = 3;
int HallF1 = 4;
int HallF2 = 5;
int HallBL = 6;
int MasterBedRoomL = 7;
int MasterBedRoomF = 8;
int ChildBedRoomL = 9;
int ChildBedRoomF = 10;


void setup() {  
  Blynk.begin(auth, ssid, pass);
  // Initialize the MCP23017
  mcp0.begin(0);
  mcp1.begin(1);
  Serial.begin(9600);
//  pinMode(A0,INPUT);
  // Define GPA0 (physical pin 21) as output pin
  mcp0.pinMode(stairs, OUTPUT);
  mcp0.pinMode(HallL1, OUTPUT);
  mcp0.pinMode(HallL2, OUTPUT);
  mcp0.pinMode(HallF1, OUTPUT);
  mcp0.pinMode(HallF2, OUTPUT);
  mcp0.pinMode(HallBL, OUTPUT);
  mcp0.pinMode(MasterBedRoomL, OUTPUT);
  mcp0.pinMode(MasterBedRoomF, OUTPUT);
  mcp0.pinMode(ChildBedRoomL, OUTPUT);
  mcp0.pinMode(ChildBedRoomF, OUTPUT);

}

void mcp(){
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
  // wait 5 seconds for next scan
  delay(100);
}

void loop() {
  mcp();
  Blynk.run();

  Serial.print("Light=");
  int l = analogRead(A0);
  Serial.println(l);
  if(l>90)
    mcp0.digitalWrite(stairs, HIGH);
  
  else{
    mcp0.digitalWrite(stairs, LOW);
  }
}


BLYNK_WRITE(V1)//Stairs
{
  int value = param.asInt();
  mcp0.digitalWrite(stairs, value);
}

BLYNK_WRITE(V2)//Hall L1
{
  int value = param.asInt();
  mcp0.digitalWrite(HallL1, value);
}

BLYNK_WRITE(V3)//HallL2
{
  int value = param.asInt();
  mcp0.digitalWrite(HallL2, value);
}

BLYNK_WRITE(V4)//HallF1
{
  int value = param.asInt();
  mcp0.digitalWrite(HallF1, value);
}

BLYNK_WRITE(V5)//HallF2
{
  int value = param.asInt();
  mcp0.digitalWrite(HallF2, value);
}

BLYNK_WRITE(V6)//HallBL
{
  int value = param.asInt();
  mcp0.digitalWrite(HallBL, value);
}

BLYNK_WRITE(V7)//MasterBedRoomL
{
  int value = param.asInt();
  mcp0.digitalWrite(MasterBedRoomL, value);
}

BLYNK_WRITE(V8)//MasterBedRoomF
{
  int value = param.asInt();
  mcp0.digitalWrite(MasterBedRoomF, value);
}

BLYNK_WRITE(V9)//ChildBedRoomL
{
  int value = param.asInt();
  mcp0.digitalWrite(ChildBedRoomL, value);
} 
BLYNK_WRITE(V10)//ChildBedRoomL
{
  int value = param.asInt();
  mcp0.digitalWrite(ChildBedRoomF, value);
} 

BLYNK_WRITE(V11)//MasterBedRoom All off
{
  mcp0.digitalWrite(MasterBedRoomF, HIGH);
  mcp0.digitalWrite(MasterBedRoomL, HIGH);
}

BLYNK_WRITE(V12)//ChildBedRoom All off
{
  mcp0.digitalWrite(ChildBedRoomF, HIGH);
  mcp0.digitalWrite(ChildBedRoomL, HIGH);
}

BLYNK_WRITE(V13)//All off
{
  mcp0.digitalWrite(HallL1, HIGH);
  mcp0.digitalWrite(HallL2, HIGH);
  mcp0.digitalWrite(HallBL, HIGH);
  mcp0.digitalWrite(MasterBedRoomF, HIGH);
  mcp0.digitalWrite(MasterBedRoomL, HIGH);
  mcp0.digitalWrite(ChildBedRoomF, HIGH);
  mcp0.digitalWrite(ChildBedRoomL, HIGH);
  mcp0.digitalWrite(HallF1, HIGH);
  mcp0.digitalWrite(HallF2, HIGH);
  
}
