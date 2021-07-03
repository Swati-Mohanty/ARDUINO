
#include <SPI.h>
const int cs7 = 10;//Rsen
const int cs1 = 4;//RG
const int cs2 = 5;//Rosc
const int cs3=6;// RF1
const int cs4=7;//RF2
const int cs5=8;// R12
const int cs6=9;//R34
int passflag=0;
float data=0;


void digitalPot(int address, int value)
{
  SPI.transfer(address);
  SPI.transfer(value);
  delay(100);
}


void setup()
{
  pinMode(cs1, OUTPUT);
  pinMode(cs2, OUTPUT);
  pinMode(cs3, OUTPUT);
  pinMode(cs4, OUTPUT);
  pinMode(cs5, OUTPUT);
  pinMode(cs6, OUTPUT);
  pinMode(cs7, OUTPUT);
  
  SPI.begin();
  Serial.begin(9600);
}

void loop()
{
  if(passflag==0)
  {
      char frequency_select;
      if(Serial.available())
      {
        frequency_select=Serial.read();
        switch (frequency_select)
     {
case '1':
Serial.print("Case 1 selected");

  digitalWrite(cs1, LOW);
  digitalPot(0x00, 105);
  digitalPot(0x10, 1);
  digitalWrite(cs1, HIGH);

  delay(1000);

  digitalWrite(cs2, LOW);
  digitalPot(0x00, 167);
  digitalPot(0x10, 167);
  digitalWrite(cs2, HIGH);
   delay(1000);


   digitalWrite(cs3, LOW);
  digitalPot(0x00, 100);
  digitalPot(0x10,100);
  digitalWrite(cs3, HIGH);
   delay(1000);


  digitalWrite(cs4, LOW);
  digitalPot(0x00,200);
  digitalPot(0x10,200);
  digitalWrite(cs4, HIGH);
   delay(1000);

   digitalWrite(cs5, LOW);
  digitalPot(0x00, 92);
  digitalPot(0x10, 92);
  digitalWrite(cs5, HIGH);
   delay(1000);


  digitalWrite(cs6, LOW);
  digitalPot(0x00, 92);
  digitalPot(0x10, 92);
  digitalWrite(cs6, HIGH);
   delay(1000);

digitalWrite(cs7, LOW);
  digitalPot(0x00, 31);
  digitalPot(0x10,31);
  digitalWrite(cs7, HIGH);
   delay(1000);

  break;

case '2':
Serial.print("Case 2 selected");
 digitalWrite(cs1, LOW);
  digitalPot(0x00, 105);
  digitalPot(0x10, 1);
  digitalWrite(cs1, HIGH);

  delay(1000);

  digitalWrite(cs2, LOW);
  digitalPot(0x00, 15);
  digitalPot(0x10, 15);
  digitalWrite(cs2, HIGH);
   delay(1000);


   digitalWrite(cs3, LOW);
  digitalPot(0x00, 8);
  digitalPot(0x10, 8);
  digitalWrite(cs3, HIGH);
   delay(1000);


  digitalWrite(cs4, LOW);
  digitalPot(0x00,21);
  digitalPot(0x10,22);
  digitalWrite(cs4, HIGH);
   delay(1000);

   digitalWrite(cs5, LOW);
  digitalPot(0x00, 91);
  digitalPot(0x10, 91);
  digitalWrite(cs5, HIGH);
   delay(1000);


  digitalWrite(cs6, LOW);
  digitalPot(0x00, 91);
  digitalPot(0x10, 91);
  digitalWrite(cs6, HIGH);
   delay(1000);

digitalWrite(cs7, LOW);
  digitalPot(0x00, 45);
  digitalPot(0x10,45);
  digitalWrite(cs7, HIGH);
   delay(1000);

 break;
 
case '3':
Serial.print("Case 3 selected");

 digitalWrite(cs1, LOW);
  digitalPot(0x00, 103);
  digitalPot(0x10, 1);
  digitalWrite(cs1, HIGH);

  delay(1000);

  digitalWrite(cs2, LOW);
  digitalPot(0x00, 7);
  digitalPot(0x10, 7);
  digitalWrite(cs2, HIGH);
   delay(1000);


   digitalWrite(cs3, LOW);
  digitalPot(0x00, 3);
  digitalPot(0x10, 3);
  digitalWrite(cs3, HIGH);
   delay(1000);


  digitalWrite(cs4, LOW);
  digitalPot(0x00,11);
  digitalPot(0x10,12);
  digitalWrite(cs4, HIGH);
   delay(1000);

   digitalWrite(cs5, LOW);
  digitalPot(0x00, 89);
  digitalPot(0x10, 89);
  digitalWrite(cs5, HIGH);
   delay(1000);


  digitalWrite(cs6, LOW);
  digitalPot(0x00, 89);
  digitalPot(0x10, 89);
  digitalWrite(cs6, HIGH);
   delay(1000);

digitalWrite(cs7, LOW);
  digitalPot(0x00, 10);
  digitalPot(0x10,10);
  digitalWrite(cs7, HIGH);
   delay(1000);

  break;

case '4':
Serial.print("Case 4 selected");
  
  digitalWrite(cs1, LOW);
  digitalPot(0x00, 105);
  digitalPot(0x10, 1);
  digitalWrite(cs1, HIGH);

  delay(1000);

  digitalWrite(cs2, LOW);
  digitalPot(0x00, 2);
  digitalPot(0x10, 2);
  digitalWrite(cs2, HIGH);
   delay(1000);

   digitalWrite(cs3, LOW);
  digitalPot(0x00, 2);
  digitalPot(0x10,2);
  digitalWrite(cs3, HIGH);
   delay(1000);

  digitalWrite(cs4, LOW);
  digitalPot(0x00,5);
  digitalPot(0x10,5);
  digitalWrite(cs4, HIGH);
   delay(1000);

   digitalWrite(cs5, LOW);
  digitalPot(0x00, 86);
  digitalPot(0x10, 86);
  digitalWrite(cs5, HIGH);
   delay(1000);


  digitalWrite(cs6, LOW);
  digitalPot(0x00, 86);
  digitalPot(0x10, 86);
  digitalWrite(cs6, HIGH);
   delay(1000);


digitalWrite(cs7, LOW);
  digitalPot(0x00,5);
  digitalPot(0x10,5);
  digitalWrite(cs7, HIGH);
   delay(1000);

  break;
}
 passflag++;
 
      }


  }
}
