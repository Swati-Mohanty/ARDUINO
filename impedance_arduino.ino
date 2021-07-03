
float Vin= 3.3;
float Vout= 0;
float R1= 0;
float R2= 0;
float R3= 0;
float buffer= 0;
bool flag=true;
float Resistance=0;
int s1=0, s2=0, s3=0;

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


void setup()
{
  pinMode(cs1, OUTPUT);
  pinMode(cs2, OUTPUT);
  pinMode(cs3, OUTPUT);
  pinMode(cs4, OUTPUT);
  pinMode(cs5, OUTPUT);
  pinMode(cs6, OUTPUT);
  pinMode(cs7, OUTPUT);
  //analogReference(EXTERNAL);
  Serial.begin(9600);
  SPI.begin();
}

void digitalPot(int address, int value)
{
  SPI.transfer(address);
  SPI.transfer(value);
  delay(100);
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
          Serial.println("1st potentiometer in use");
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


                  while(flag==true)
                  {
                  for(int i=0;i<10;i++)
                  {
                  data= analogRead(A0);   //actually stored in digital
                  if(data)
                  {
                  buffer= data * Vin;
                  Vout= (buffer)/1024.0;        //converted to digital

                  s1=digitalRead(A1);
                  s3=digitalRead(A2);
                  s2= !(s1||s3);

                  //unknown resistance calculated
                  R1 = (Vout)/2.6 + 0.22;
                  R2 = (Vout)/13 + 1.43;
                  R3 = (Vout)/4.3 + 1.68;
                  if((R1 < 1.43)&&(s1==HIGH)) 
                  {
                        Resistance = R1/(2.5*0.001);
                  }
                  else if((1.43 < R2 < 1.68)&&(s2==HIGH))
                  {
                         Resistance = R2/(2.5*0.001);
                  }
                 else if((R3 > 1.743)&&(s3==HIGH))
                 {
                       Resistance = R3/(2.5*0.001);
                 }
                  
                  Serial.print("Vout: ");
                  Serial.println(Vout);
                  Serial.print("Impedance: ");
                  Serial.print(Resistance);
                  Serial.println(" ohms");
                  
                  delay(2000);
                  }
                  }
                  flag=false;
                  }

  break;

          case '2':
          Serial.println("2nd potentiometer in use");
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

                  while(flag==true)
                  {
                  for(int i=0;i<10;i++)
                  {
                  data= analogRead(A0);   //actually stored in digital
                  if(data)
                  {
                  buffer= data * Vin;
                  Vout= (buffer)/1024.0;        //converted to digital
                  
                  s1=digitalRead(A1);
                  s3=digitalRead(A2);
                  s2= !(s1||s3);

                  //unknown resistance calculated
                  R1 = (Vout)/2.6 + 0.22;
                  R2 = (Vout)/13 + 1.43;
                  R3 = (Vout)/4.3 + 1.68;
                  if((R1 < 1.43)&&(s1==HIGH)) 
                  {
                        Resistance = R1/(2.5*0.001);
                  }
                  else if((1.43 < R2 < 1.68)&&(s2==HIGH))
                  {
                         Resistance = R2/(2.5*0.001);
                  }
                 else if((R3 > 1.743)&&(s3==HIGH))
                 {
                       Resistance = R3/(2.5*0.001);
                 }
                  
                  Serial.print("Vout: ");
                  Serial.println(Vout);
                  Serial.print("Impedance: ");
                  Serial.print(Resistance);
                  Serial.println(" ohms");
                  
                  delay(2000);
                  }
                  }
                  flag=false;
                  }
                  
 break;
 
         case '3':
         Serial.println("3rd potentiometer in use");
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

                   
                  while(flag==true)
                  {
                  for(int i=0;i<10;i++)
                  {
                  data= analogRead(A0);   //actually stored in digital
                  if(data)
                  {
                  buffer= data * Vin;
                  Vout= (buffer)/1024.0;        //converted to digital
                  
                  s1=digitalRead(A1);
                  s3=digitalRead(A2);
                  s2= !(s1||s3);

                  //unknown resistance calculated
                  R1 = (Vout)/2.6 + 0.22;
                  R2 = (Vout)/13 + 1.43;
                  R3 = (Vout)/4.3 + 1.68;
                  if((R1 < 1.43)&&(s1==HIGH)) 
                  {
                        Resistance = R1/(2.5*0.001);
                  }
                  else if((1.43 < R2 < 1.68)&&(s2==HIGH))
                  {
                         Resistance = R2/(2.5*0.001);
                  }
                 else if((R3 > 1.743)&&(s3==HIGH))
                 {
                       Resistance = R3/(2.5*0.001);
                 }
                  
                  Serial.print("Vout: ");
                  Serial.println(Vout);
                  Serial.print("Impedance: ");
                  Serial.print(Resistance);
                  Serial.println(" ohms");
                  
                  
                  delay(2000);
                  }
                  }
                  flag=false;
                  }
                  

  break;

         case '4':
         Serial.println("4th potentiometer in use");
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


                  while(flag==true)
                  {
                  for(int i=0;i<10;i++)
                  {
                  data= analogRead(A0);   //actually stored in digital
                  if(data)
                  {
                  buffer= data * Vin;
                  Vout= (buffer)/1024.0;        //converted to digital
                  
                  s1=digitalRead(A1);
                  s3=digitalRead(A2);
                  s2= !(s1||s3);

                  //unknown resistance calculated
                  R1 = (Vout)/2.6 + 0.22;
                  R2 = (Vout)/13 + 1.43;
                  R3 = (Vout)/4.3 + 1.68;
                  if((R1 < 1.43)&&(s1==HIGH)) 
                  {
                        Resistance = R1/(2.5*0.001);
                  }
                  else if((1.43 < R2 < 1.68)&&(s2==HIGH))
                  {
                         Resistance = R2/(2.5*0.001);
                  }
                 else if((R3 > 1.743)&&(s3==HIGH))
                 {
                       Resistance = R3/(2.5*0.001);
                 }
                  
                  Serial.print("Vout: ");
                  Serial.println(Vout);
                  Serial.print("Impedance: ");
                  Serial.print(Resistance);
                  Serial.println(" ohms");
                  
                  delay(2000);
                  }
                  }
                  flag=false;
                  }
                  
 break;
}
 passflag++;
      }
  }
}



//The Arduino Uno ADC is of 10-bit resolution (so the integer values from 0 - 2^10 = 1024 values). 
//This means that it will map input voltages between 0 and 5 volts into integer values between 0 and 1023. 
//So if we multiply input anlogValue to (5/1024), then we get the digital value of input voltage.
