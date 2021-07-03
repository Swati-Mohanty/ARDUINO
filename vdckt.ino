#include <Wire.h>

int Apina=A0;
int Apinb=A1;
int Apinc=A2;
int Va,Vb,Vc;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
 Va=analogRead(Apina);
 Vb=analogRead(Apinb);
 Vc=analogRead(Apinc);

  if (Serial.available())
  {
  Serial.println("V1=");
  Serial.print(Va);
  delay(1000);
  Serial.println("V2=");
  Serial.print(Vb);
  delay(1000);
  Serial.println("V3=");
  Serial.print(Vc);
  delay(1000);
  }
}
