#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 7

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int bluetoothTx = 2; // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3; // RX-I pin of bluetooth mate, Arduino D3
 
int led = 12;
int buz = 8; 
 
int dataFromBt;
 
boolean lightBlink = false;
boolean BuzzerBol = false;
 
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
 
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
 sensors.begin();
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
 bluetooth.println("0 - LED OFF");
 bluetooth.println("1 - LED ON");
 bluetooth.println("b - Blink");
 bluetooth.println("v - Buzzer ON/OFF");
 bluetooth.println("t - Termometer");
 }
 if(dataFromBt == '1'){
   Serial.println("led on");
   digitalWrite(led, HIGH);
   bluetooth.println("LED ON");
 }
 if(dataFromBt == '0'){
   Serial.println("led off");
   digitalWrite(led, LOW);
   bluetooth.println("LED OFF");
 }
 if(dataFromBt == 't'){
   Serial.println("Dallas Termometer ON");
   sensors.requestTemperatures();
   bluetooth.println("Temperature: ");
   bluetooth.println(sensors.getTempCByIndex(0));
 }
 if(dataFromBt == 'v'){
   BuzzerBol = !BuzzerBol;
   if(BuzzerBol){
     digitalWrite(8, HIGH);
     Serial.println("Buzzer ON");
     bluetooth.println("Buzzer ON");
   }
   else{
     digitalWrite(8, LOW);
     Serial.println("Buzzer OFF");
     bluetooth.println("Buzzer OFF");
   }
 }
 
 if(dataFromBt == 'b'){
   Serial.println("a");
   lightBlink = true;
 }
 else{
   lightBlink = false;
 }
 
 }
 
 if(Serial.available()) // If stuff was typed in the serial monitor
 {
 // Send any characters the Serial monitor prints to the bluetooth
 bluetooth.print((char)Serial.read());
 }
 
 // and loop forever and ever!
 if(lightBlink){
 digitalWrite(led, HIGH);
 bluetooth.print("1");
 Serial.println("HIGH");
 delay(500);
 digitalWrite(led, LOW);
 bluetooth.print("0");
 Serial.println("LOW");
 delay(500);
 }}
