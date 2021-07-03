
#include <SPI.h>
const int cs1 = 4;// Digital pot pin
const int sec=2000;
const int Rin=200;
bool flag=true;
float data=0;
int Vin= 3.3;
float Vout= 0;
float Rsen= 0,R2=0,Rpot=0;
float Rref=9960 ;  //1000000  
float buffer=0;
int arrayP[]={48,101,154,206,255};
int arrayC[]={51,102,153,204,255};
long int sumR=0;
float avgR=0;

void setup()
{
  pinMode(cs1, OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  Serial.begin(9600);
  SPI.begin();
}

void digitalPot(int address, int value)
{
  SPI.transfer(address);
  SPI.transfer(value);
  delay(1000);
}

void loop()
{
  while(flag==true)
  {
    //First channel resistance
     for(int i=0;i<5;i++)         
     {
      //for 13th pin--000   
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      
      Serial.print("1st sensor in use with ");
      Serial.print(i+1);
      Serial.println("th potentiometer value");
      digitalWrite(cs1, LOW);       
      digitalPot(0x00,arrayP[i]);
      delay(sec);
      digitalWrite(cs1, HIGH);
      Rpot = 39.0625* arrayC[i];
      Serial.print("Rpot=");
      Serial.println(Rpot);
            
      for(int j=0;j<2;j++)
      {
          data= analogRead(A0);   //actually stored in digital
          delay(sec);
          Serial.print("Data Read=");
          Serial.println(data);
          float vol=(data*Vin)/1024.0;     //voltage across sensor+mux+digipot
          Serial.print("Voltage=");
          Serial.println(vol);
          delay(sec);
          //unknown resistance calculated
          buffer=(Vin-vol)/Rref;     //current
          R2=vol/buffer;
          
          Rsen=R2-Rpot-Rin;
          sumR+=Rsen;
    
    
          Serial.print("Resistance =");
          Serial.println(Rsen);
      } 
      }
      Serial.println(sumR);
      avgR=sumR/10.0;
      Serial.print("Average Resistance : ");
      Serial.println(avgR);
      avgR=0;
      sumR=0;

   //Second channel resistance
   for(int i=0;i<5;i++)
    {
      //for 14th pin--001   
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      
      Serial.print("2nd sensor in use with ");
      Serial.print(i+1);
      Serial.println("th potentiometer value");
      digitalWrite(cs1, LOW); 
      digitalPot(0x00,arrayP[i]);
      delay(sec);
      digitalWrite(cs1, HIGH);
         
      Rpot = 39.0625* arrayC[i];
      Serial.print("Rpot=");
      Serial.println(Rpot);
   
      for(int j=0;j<2;j++)
      {
          data= analogRead(A0);   //actually stored in digital
          delay(sec);
          Serial.print("Data Read=");
          Serial.println(data);
          float vol=(data*Vin)/1024.0;     //voltage across sensor+mux+digipot
          Serial.print("Voltage=");
          Serial.println(vol);
          delay(sec);
          //unknown resistance calculated
          buffer=(Vin-vol)/Rref;     //current
          R2=vol/buffer;
          Rsen=R2-Rpot-Rin;
          sumR+=Rsen;
    
          Serial.print("Resistance =");
          Serial.println(Rsen);
      } 
      }
      Serial.println(sumR);
      avgR=sumR/10.0;
      Serial.print("Average Resistance : ");
      Serial.println(avgR);

      avgR=0;
      sumR=0;

  //Third channel resistance
  for(int i=0;i<5;i++)
    {
      //for 15th pin--010   
      digitalWrite(8,LOW);
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);
            
      Serial.print("3rd sensor in use with ");
      Serial.print(i+1);
      Serial.println("th potentiometer value");
      digitalWrite(cs1, LOW);
      digitalPot(0x00,arrayP[i]);
      delay(sec);
      digitalWrite(cs1, HIGH);
         
      Rpot = 39.0625* arrayC[i];
      Serial.print("Rpot=");
      Serial.println(Rpot);
   
        for(int j=0;j<2;j++)
        {
          data= analogRead(A0);   //actually stored in digital
          delay(sec);
          Serial.print("Data Read=");
          Serial.println(data);
          float vol=(data*Vin)/1024.0;     //voltage across sensor+mux+digipot
          Serial.print("Voltage=");
          Serial.println(vol);
          delay(sec);
          //unknown resistance calculated
          buffer=(Vin-vol)/Rref;     //current
          R2=vol/buffer;
          
          Rsen=R2-Rpot-Rin;
          sumR+=Rsen;
  
  
          Serial.print("Resistance =");
          Serial.println(Rsen);
          } 
    }
    Serial.println(sumR);
    avgR=sumR/10.0;
    Serial.print("Average Resistance : ");
    Serial.println(avgR);
    avgR=0;
    sumR=0;

    flag=false;
  }
             
}
