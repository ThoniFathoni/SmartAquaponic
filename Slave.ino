#include <LiquidCrystal.h>

#include <Wire.h>

#define SLAVE_ADDR 9

#define OUTPUT1 10

#define OUTPUT2 11

#define LED1 6

#define LED2 7

#define LED3 8

#define LED4 9

 

LiquidCrystal lcd(5, 4, 3, 2, 1, 0);

 

char temperature[] = "Temp = 00.0 C  ";

char humidity[]    = "RH   = 00.0 %  ";

char wtemperature[]= "WTemp= 00.0 C  ";

char tds[]         = "TDS  = 000.0 ppm";

 

byte RH;

byte Temp;

byte Watertemp;

byte tdsValue;

 

void setup() {

  Wire.begin(SLAVE_ADDR);

  Wire.onReceive(receiveEvent);

 

  lcd.begin(16, 2);

  pinMode(OUTPUT1, OUTPUT);

  pinMode(OUTPUT2, OUTPUT);

  pinMode(LED1, OUTPUT);

  pinMode(LED2, OUTPUT);

  pinMode(LED3, OUTPUT);

  pinMode(LED4, OUTPUT);

 

  lcd.clear();

  lcd.setCursor(0, 0);

  lcd.print("SMART AQUAPONIC");

  lcd.setCursor(0, 1);

  lcd.print("    Kelompok 9   ");

  delay(5000);

}

 

void receiveEvent(){

  RH = Wire.read();

  Temp = Wire.read();

  Watertemp = Wire.read();

  tdsValue = Wire.read();

}

 

void showLCD(){

  lcd.clear();

  lcd.setCursor(0, 0);

  lcd.print(temperature);

  lcd.setCursor(0, 1);

  lcd.print(humidity);

  delay(3000);

  lcd.clear();

  lcd.setCursor(0, 0);

  lcd.print(wtemperature);

  lcd.setCursor(0, 1);

  lcd.print(tds);

  delay(3000);

}

 

void outputState(){

  if(RH < 60 || Temp > 33){

    digitalWrite(OUTPUT1, LOW);

    digitalWrite(LED1, HIGH);

    digitalWrite(LED2, LOW);

  }else{

    digitalWrite(OUTPUT1, HIGH);

    digitalWrite(LED1, LOW);

    digitalWrite(LED2, HIGH);

  }

 

  if(tdsValue > 200){

    digitalWrite(OUTPUT2, LOW);

    digitalWrite(LED3, HIGH);

    digitalWrite(LED4, LOW);

  }else{

    digitalWrite(OUTPUT2, HIGH);

    digitalWrite(LED3, LOW);

    digitalWrite(LED4, HIGH);

  }

}

 

void loop() {

  temperature[7]     = Temp / 10 + 48;

  temperature[8]     = Temp % 10 + 48;

  temperature[11]    = 223;

 

  humidity[7]        = RH / 10 + 48;

  humidity[8]        = RH % 10 + 48;

 

  wtemperature[7]    = Watertemp / 10 + 48;

  wtemperature[8]    = Watertemp % 10 + 48;

  wtemperature[11]   = 223;

 

  if(tdsValue < 100){

    tds[7]             = tdsValue / 10 + 48;

    tds[8]             = tdsValue % 10 + 48;

  }else{

    tds[7]             = tdsValue / 100 + 48;

    tds[8]             = tdsValue / 100 + 48;

    tds[9]             = tdsValue % 10 + 48;

  }

 

  outputState();

  showLCD();


}
