#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define ONE_WIRE_BUS 8      
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup()
{
  lcd.begin(16, 2);
  lcd.print("Temperature: ");
  Serial.begin(9600);
  sensors.begin();
  pinMode(9, INPUT);
}
int zero = 0;
void loop()
{
  lcd.setCursor(0, 1);
  sensors.requestTemperatures();
  lcd.print(sensors.getTempCByIndex(0));
  delay(1000);
    /*if(digitalRead(10) == HIGH)
 {
  digitalWrite(13, HIGH);
  digitalWrite(6, HIGH);
  sensors.requestTemperatures();
  Serial.println("");
  Serial.print("Sensor 1: ");
  Serial.println(sensors.getTempCByIndex(0)); 
 }
 else
 {
   digitalWrite(13, LOW);
   digitalWrite(6, LOW);
 }
  */
}
