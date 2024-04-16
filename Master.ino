#include <Wire.h>

#define MASTER_ADDR 9

 

#include <DHT.h>

#define DHTPIN 13

#define DHTTYPE DHT11       // DHT11 sensor is used

DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT library

 

#include <OneWire.h>

#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

 

#include <EEPROM.h>

#include "GravityTDS.h"

#define TdsSensorPin A1

GravityTDS gravityTds;

float temperature = 25,tdsValue = 0;

 

 

void setup() {

  Wire.begin();

  dht.begin();

  sensors.begin();

  gravityTds.setPin(TdsSensorPin);

  gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO

  gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC

  gravityTds.begin();

}

 

void loop() {

  delay(100);

  byte RH = dht.readHumidity();

  byte Temp = dht.readTemperature();

  sensors.setResolution(10);

  sensors.requestTemperatures();

  byte Watertemp = sensors.getTempCByIndex(0);

 

  gravityTds.setTemperature(sensors.getTempCByIndex(0));  // set the temperature and execute temperature compensation

  gravityTds.update();  //sample and calculate

  tdsValue = gravityTds.getTdsValue();  // then get the value

  byte TDS = tdsValue;

 

  Wire.beginTransmission(MASTER_ADDR);

  Wire.write(RH);

  Wire.write(Temp);

  Wire.write(Watertemp);

  Wire.write(TDS);

  Wire.endTransmission();

}
