void setup()
{
 Serial.begin(9600);
 pinMode(A0, INPUT); 
  
}
void loop()
{
  int odczyt = analogRead(A0);
  Serial.println(odczyt);
  delay(1000);
}
