#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 6, 9); //init LCD

int bluetoothTx = 2; // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3; // RX-I pin of bluetooth mate, Arduino D3

int led = 10;
int buz = 8; 
int sek = 15;			
int mins = 0;

int dataFromBt; // Data recieved

boolean Bombol = false;
boolean Ledbol = false;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx); //init BT

void setup()
{
  Serial.begin(9600); // Begin the serial monitor at 9600bps
  bluetooth.begin(115200); // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$"); // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$"); // Enter command mode
  delay(100); // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N"); // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600); // Start bluetooth serial at 9600
  pinMode(led, OUTPUT);
  pinMode(buz, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("HELLO MY VICTIMS");
  lcd.setCursor(0, 1);
  lcd.print("       :)");
}
void loop()
{ 
  if(bluetooth.available()) // If the bluetooth sent any characters
 {
 // Send any characters the bluetooth prints to the serial monitor
 //Serial.println((char)bluetooth.read());
 
dataFromBt = bluetooth.read();

 
 if(dataFromBt == 'h'){
   bluetooth.println("--------HELP--------");
   bluetooth.println("1 - TURN THE BOMB ON");
   bluetooth.println("2 - TURN THE BOMB OFF"); 
 }
if(dataFromBt == '1'){
   Serial.println("Bomb was armed.");
   bluetooth.println("Bomb was armed.");
   Bombol = !Bombol;
}
if(dataFromBt == '2'){
   Serial.println("Bomb was disarmed.");
   bluetooth.println("Bomb was disarmed.");
   Bombol = false;
   lcd.clear();
   sek = 1;
   mins = 2;
   digitalWrite(buz, LOW);
   digitalWrite(led, LOW);
}
 
 }
 
 if(Serial.available())
 {
   bluetooth.print((char)Serial.read());
 }
   
if(Bombol)
{
   Ledbol = !Ledbol;
   lcd.setCursor(0, 0);
   lcd.print("Bomba jebnie za:");
   lcd.setCursor (0,1);					
   lcd.print (mins);		
   lcd.print (" min ");		
   lcd.setCursor (8,1);		
   lcd.print ("  "); //space
   lcd.print (sek);		
   lcd.print (" SEC ");		
   sek --;
   tone(buz, 3000, 250);
   delay(988);
   if(sek==0){
     sek = 60;
     mins --;
   }
   if(mins == -1){
     Bombol = !Bombol;
     lcd.clear();
     sek = 1;
     mins = 2;
     digitalWrite(buz, HIGH);
   }
if(Ledbol){
    digitalWrite(led, HIGH);
 }
 else{
   digitalWrite(led, LOW);
 }
}
 
}
