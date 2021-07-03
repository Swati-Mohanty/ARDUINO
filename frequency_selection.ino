
#include <SPI.h>
const int cs1 = 4;// Digital pot pin
const int sec=2000;
double data=0;
int Vin= 5;
double Vout= 0;
float R2= 0;
float Rref=9960;
float R=0;
float buffer= 0;
int arrayRs[]={51,102,153,204,255};

void setup()
{
  pinMode(cs1, OUTPUT);
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
  for(int i=0;i<256;i++)
  {
    
    digitalWrite(cs1, LOW);
    digitalPot(0x00, i);//arrayRs[i]);
    digitalWrite(cs1, HIGH);
    R2 = 39.0625* arrayRs[i];
    //Serial.print("Rpot=");
    //Serial.println(R2);
    data= analogRead(A0);   //actually stored in digital
    delay(sec);
    Serial.print("i=");
    Serial.print(i);
    Serial.print("   :Data Read=");
    Serial.print(data);
              
    Vout= (data * Vin)/1024.0;                  
    buffer= Vout/(Vin-Vout);
    Serial.print("   :Voltage=");
    Serial.println(Vout);
    R=buffer*Rref;   
    Serial.print("    :R: ");
                  //Serial.println(Vout);
                  Serial.println(R);
                 // Serial.println(" ohms");
  }
}
 
          
         
