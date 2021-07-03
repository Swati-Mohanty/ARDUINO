
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Analog pin for the Impedance sensor
const int volPin = 0;

float v1=0;
float Vout= 0;
float R1= 0;
float R2= 0;
float R3= 0;
float Resistance = 0;

// Time in milliseconds
const int secs = 9000;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop()
{
 v1= analogRead(A0);
 Vout =v1*2.5*0.001;
R1 = (Vout)/2.6 + 0.25;
R2 = (Vout)/13 + 1.5;
R3 = (Vout)/4.3 + 1.743;
if(R1 < 1.5) 
{
  Resistance = R1/(2.5*0.001);
}
else if(1.5 < R2 < 1.743)
{
  Resistance = R2/(2.5*0.001);
}
else if(R3 > 1.743)
{
  Resistance = R3/(2.5*0.001);
}

  
 Serial.println(Resistance);
lcd.setCursor(0, 1);
lcd.print("Resistance: ");
lcd.print(Resistance);

  
  delay(secs);
}

