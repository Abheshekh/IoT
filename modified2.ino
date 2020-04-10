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
int god = 6;
int MasterBedRoomL = 7;
int MasterBedRoomF = 8;
int ChildBedRoomL = 9;
int ChildBedRoomF = 10;
int woofer = 11;
int tv = 12;
int cctv =13;
int box1 = 14;
int box2 = 15;
int box3 = 16;

int Prestairs = 1;
int PreHallL1 = 1;
int PreHallL2 = 1;
int PreHallF1 = 1;
int PreHallF2 = 1;
int PreHallBL = 1;
int PreMasterBedRoomL = 1;
int PreMasterBedRoomF = 1;
int PreChildBedRoomL = 1;
int PreChildBedRoomF = 1;


void setup() {
  
  // Initialize the MCP23017
  mcp0.begin(0);
  mcp1.begin(1);
  Serial.begin(9600);
  pinMode(A0, INPUT);
  // Define GPA0 (physical pin 21) as output pin
  mcp0.pinMode(stairs, OUTPUT);
  mcp0.pinMode(HallL1, OUTPUT);
  mcp0.pinMode(HallL2, OUTPUT);
  mcp0.pinMode(HallF1, OUTPUT);
  mcp0.pinMode(HallF2, OUTPUT);
  mcp0.pinMode(MasterBedRoomL, OUTPUT);
  mcp0.pinMode(MasterBedRoomF, OUTPUT);
  mcp0.pinMode(ChildBedRoomL, OUTPUT);
  mcp0.pinMode(ChildBedRoomF, OUTPUT);
  mcp0.pinMode(god, OUTPUT);

  Blynk.begin(auth, ssid, pass);
}

void mcp() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
  // wait 5 seconds for next scan
  delay(100);
}

void loop()
{
  
  mcp();
  int l = analogRead(A0);
  Serial.print("Light=");
  Serial.println(l);
  if(l>73)
    mcp0.digitalWrite(stairs, HIGH);
  
  else if(l<65){
    mcp0.digitalWrite(stairs, LOW);
  }
  b();
}

void b(){
  Blynk.run();
}

BLYNK_WRITE(V1)//Stairs
{
  int value = param.asInt();
  if (value == Prestairs)
    mcp0.digitalWrite(stairs, !value);
  else
    mcp0.digitalWrite(stairs, value);
  Prestairs = value;
}

BLYNK_WRITE(V2)//Hall L1
{
  int value = param.asInt();
  if (value == PreHallL1)
    mcp0.digitalWrite(HallL1, !value);
  else
    mcp0.digitalWrite(HallL1, value);
  PreHallL1 = value;
}

BLYNK_WRITE(V3)//HallL2
{
  int value = param.asInt();
  if (value == PreHallL2)
    mcp0.digitalWrite(HallL2, !value);
  else
    mcp0.digitalWrite(HallL2, value);
  PreHallL2 = value;
}

BLYNK_WRITE(V4)//HallF1
{
  int value = param.asInt();
  if (value == PreHallF1)
    mcp0.digitalWrite(HallF1, !value);
  else
    mcp0.digitalWrite(HallF1, value);
  PreHallF1 = value;
}

BLYNK_WRITE(V5)//HallF2
{
  int value = param.asInt();
  if (value == PreHallF2)
    mcp0.digitalWrite(HallF2, !value);
  else
    mcp0.digitalWrite(HallF2, value);
  PreHallF2 = value;
}

BLYNK_WRITE(V6)//god
{
  int value = param.asInt();
  mcp0.digitalWrite(god, value);
}

BLYNK_WRITE(V7)//MasterBedRoomL
{
  int value = param.asInt();
  if (value == PreMasterBedRoomL)
    mcp0.digitalWrite(MasterBedRoomL, !value);
  else
    mcp0.digitalWrite(MasterBedRoomL, value);
  MasterBedRoomL = value;
}

BLYNK_WRITE(V8)//MasterBedRoomF
{
  int value = param.asInt();
  if (value == PreMasterBedRoomF)
    mcp0.digitalWrite(MasterBedRoomF, !value);
  else
    mcp0.digitalWrite(MasterBedRoomF, value);
  PreMasterBedRoomF = value;
}

BLYNK_WRITE(V9)//ChildBedRoomL
{
  int value = param.asInt();
  if (value == PreChildBedRoomL)
    mcp0.digitalWrite(ChildBedRoomL, !value);
  else
    mcp0.digitalWrite(ChildBedRoomL, value);
  PreChildBedRoomL = value;
}
BLYNK_WRITE(V10)//ChildBedRoomF
{
  int value = param.asInt();
  if (value == PreChildBedRoomF)
    mcp0.digitalWrite(ChildBedRoomF, !value);
  else
    mcp0.digitalWrite(ChildBedRoomF, value);
  PreChildBedRoomF = value;
}

BLYNK_WRITE(V11)//MasterBedRoom All off
{
  int value = param.asInt();
  if (value == PreMasterBedRoomF)
    mcp0.digitalWrite(MasterBedRoomF, !value);
  else
    mcp0.digitalWrite(MasterBedRoomF, value);
  PreMasterBedRoomF = value;

  if (value == PreMasterBedRoomL)
    mcp0.digitalWrite(MasterBedRoomL, !value);
  else
    mcp0.digitalWrite(MasterBedRoomL, value);
  PreMasterBedRoomL = value;
}

BLYNK_WRITE(V12)//ChildBedRoom All off
{
  int value = param.asInt();
  if (value == PreChildBedRoomF)
    mcp0.digitalWrite(ChildBedRoomF, !value);
  else
    mcp0.digitalWrite(ChildBedRoomF, value);
  PreChildBedRoomF = value;

  if (value == PreChildBedRoomL)
    mcp0.digitalWrite(ChildBedRoomL, !value);
  else
    mcp0.digitalWrite(ChildBedRoomL, value);
  PreChildBedRoomL = value;
}

BLYNK_WRITE(V13)//All off
{
  int value = param.asInt();

  if (value == PreHallF1)
    mcp0.digitalWrite(HallF1, !value);
  else
    mcp0.digitalWrite(HallF1, value);
  PreHallF1 = value;

  if (value == PreHallF2)
    mcp0.digitalWrite(HallF2, !value);
  else
    mcp0.digitalWrite(HallF2, value);
  PreHallF2 = value;

  if (value == PreHallL1)
    mcp0.digitalWrite(HallL1, !value);
  else
    mcp0.digitalWrite(HallL1, value);
  PreHallL1 = value;

  if (value == PreHallL2)
    mcp0.digitalWrite(HallL2, !value);
  else
    mcp0.digitalWrite(HallL2, value);
  PreHallL2 = value;


  if (value == PreMasterBedRoomF)
    mcp0.digitalWrite(MasterBedRoomF, !value);
  else
    mcp0.digitalWrite(MasterBedRoomF, value);
  PreMasterBedRoomF = value;

  if (value == PreMasterBedRoomL)
    mcp0.digitalWrite(MasterBedRoomL, !value);
  else
    mcp0.digitalWrite(MasterBedRoomL, value);
  PreMasterBedRoomL = value;

  if (value == PreChildBedRoomF)
    mcp0.digitalWrite(ChildBedRoomF, !value);
  else
    mcp0.digitalWrite(ChildBedRoomF, value);
  PreChildBedRoomF = value;

  if (value == PreChildBedRoomL)
    mcp0.digitalWrite(ChildBedRoomL, !value);
  else
    mcp0.digitalWrite(ChildBedRoomL, value);
  PreChildBedRoomL = value;

}

BLYNK_WRITE(V14)//woofer
{
  int value = param.asInt();
  mcp0.digitalWrite(woofer, value);
}

BLYNK_WRITE(V15)//tv
{
  int value = param.asInt();
  mcp0.digitalWrite(tv, value);
}

BLYNK_WRITE(V16)//cctv
{
  int value = param.asInt();
  mcp0.digitalWrite(cctv, value);
}

BLYNK_WRITE(V17)//box1
{
  int value = param.asInt();
  mcp0.digitalWrite(box1, value);
}

BLYNK_WRITE(V18)//box2
{
  int value = param.asInt();
  mcp0.digitalWrite(box2, value);
}

BLYNK_WRITE(V19)//box3
{
  int value = param.asInt();
  mcp0.digitalWrite(box3, value);
}
