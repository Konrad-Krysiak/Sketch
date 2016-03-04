#include <LiquidCrystal.h>
#define trig 8
#define echo 9
int buzz=10;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Distance:");
  pinMode (trig, OUTPUT);
  pinMode (echo, INPUT);
  pinMode (buzz, OUTPUT);
  digitalWrite(buzz, LOW);
}
void loop(){
  int czas, dist;
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);
  czas = pulseIn(echo, HIGH);
  dist = (czas/2) /29.1;
  lcd.setCursor(0, 1);
  
  if (dist<=10) {
    tone(buzz, 3000, 100);
    delay(200);
    lcd.print(dist/1.25);
    lcd.print("cm");}
  else if (dist <=20 && dist >10) {
    tone(buzz, 2000, 100);
    delay(400);
    lcd.print(dist/1.25);
    lcd.print("cm");}
  else if (dist>20){
    tone(buzz, 1000, 100);
    delay(800);
    lcd.print(dist/1.25);
    lcd.print("cm");}
}
