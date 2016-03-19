#include <SoftwareSerial.h>
SoftwareSerial HC06(2, 3); // RX | TX

void setup() 
{
    Serial.begin(9600);
    Serial.println("Wpisz komendę AT:");
    HC06.begin(9600); //domyślna prędkośc modułu
}
 
void loop()
{
 

    if (HC06.available()) //ciągłe połączenie z HC-06
    {  
        Serial.write(HC06.read()); //odczytujemy dane z HC-06, wyświetlamy monitorze
    }
 
    if (Serial.available()) //ciągłe połączenie z monitorem
    {
        HC06.write(Serial.read()); //odczytujemy dane z monitora i wysyłamy do HC-06
    }
 
}
