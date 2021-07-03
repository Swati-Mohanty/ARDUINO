
#include <SPI.h>
const int cs1 = 4;// Digital pot pin
const int sec=2000;
const int Rin=400;
int passflag=0;
bool flag=true;
float data=0;
int Vin= 5;
float Vout= 0;
float Rsen= 0;
float R2= 0;
float Rref= 9980;
float buffer= 0;
float temp=0;
int arrayRs[]={51,102,153,204,255};
long int sumR=0;
float avgR=0;

void setup()
{
  pinMode(cs1, OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
 // analogReference(EXTERNAL);
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
          
          for(int i=0;i<5;i++)
          {
                digitalWrite(8,HIGH);
                digitalWrite(9,LOW);
                digitalWrite(10,LOW);
                delay(sec);
                Serial.print("1st sensor in use with ");
                Serial.print(i+1);
                Serial.println("th potentiometer value");
                digitalWrite(cs1, LOW);
                digitalPot(0x00,arrayRs[i]);
                digitalWrite(cs1, HIGH);

                R2 = 39.0625* arrayRs[i];
                Serial.print("Rpot=");
                Serial.println(R2);
              
                delay(1000);
              
                  while(flag==true)
                  {
                  for(int j=0;j<5;j++)
                  {
                  data= analogRead(A0);   //actually stored in digital
                  delay(sec);
                  Serial.print("Data Read=");
                  Serial.println(data);
                 
                  buffer= data * Vin;
                  Vout= (buffer)/1024.0;        //converted to Analog
                  
                  temp= ((Vin/Vout) - 1)*R2;   
                  
                 // temp = R2 * buffer; 
                  Serial.println(temp);
                  Rsen=temp-Rref-Rin;
               
                  Serial.print("Rsen: ");
                  Serial.print(Rsen);
                  Serial.println(" ohms");
                  sumR+=Rsen;
                  delay(2000);
                  
                  }
                  
                  
                  flag=false;
                  }
           avgR=sumR/5.0;
          Serial.print("Avg value= ");
          Serial.print(avgR);
          Serial.println(" ohms");
          sumR=0;
          avgR=0;
          flag=true;
          }


                for(int i=0;i<5;i++)
          {
                digitalWrite(9,LOW);
                digitalWrite(10,HIGH);
                digitalWrite(7,HIGH);
                delay(sec);
                Serial.print("1st sensor in use with ");
                Serial.print(i+1);
                Serial.println("th potentiometer value");
                digitalWrite(cs1, LOW);
                digitalPot(0x00,arrayRs[i]);
                digitalWrite(cs1, HIGH);

                R2 = 39.0625* arrayRs[i];
                Serial.print("Rpot=");
                Serial.println(R2);
              
                delay(1000);
              
                  while(flag==true)
                  {
                  for(int j=0;j<5;j++)
                  {
                  data= analogRead(A0);   //actually stored in digital
                  delay(sec);
                  Serial.print("Data Read=");
                  Serial.println(data);
                 
                  buffer= data * Vin;
                  Vout= (buffer)/1024.0;        //converted to Analog
                  
                  temp= ((Vin/Vout) - 1)*R2;   
                  
                 // temp = R2 * buffer; 
                  Serial.println(temp);
                  Rsen=temp-Rref-Rin;
               
                  Serial.print("Rsen: ");
                  Serial.print(Rsen);
                  Serial.println(" ohms");
                  sumR+=Rsen;
                  delay(2000);
                  
                  }
                  
                  
                  flag=false;
                  }
           avgR=sumR/5.0;
          Serial.print("Avg value= ");
          Serial.print(avgR);
          Serial.println(" ohms");
          sumR=0;
          avgR=0;
          flag=true;
          }



  break;
  /* case '2':
          Serial.println("2nd sensor in use");
                digitalWrite(cs1, LOW);
                digitalPot(0x00, 50);
                digitalWrite(cs1, HIGH);

                R2 = (10000 * 50)/ 256;
              
                delay(1000);
              
                

                  while(flag==true)
                  {
                  for(int i=0;i<10;i++)
                  {
                  data= analogRead(A0);   //actually stored in digital
                  if(data)
                  {
                  buffer= data * Vin;
                  Vout= (buffer)/1024.0;        //converted to Analog
                  buffer= (Vin/Vout) -1;   
                  Rsen = R2 * buffer;
                  


                  Serial.print("Rsen2: ");
                  Serial.print(Rsen);
                  Serial.println(" ohms");
                  
                  delay(2000);
                  }
                  }
                  flag=false;
                  }

  break;
  
   case '3':
          Serial.println("3rd sensor in use");
                digitalWrite(cs1, LOW);
                digitalPot(0x00, 105);
                digitalWrite(cs1, HIGH);
                
                R2 = (10000 * 105)/ 256;
                
                delay(1000);
              
                

                  while(flag==true)
                  {
                  for(int i=0;i<10;i++)
                  {
                  data= analogRead(A0);   //actually stored in digital
                  if(data)
                  {
                  buffer= data * Vin;
                  Vout= (buffer)/1024.0;        //converted to Analog
                  buffer= (Vin/Vout) -1;   
                  Rsen = R2 * buffer;
          

                  Serial.print("Rsen3: ");
                  Serial.print(Rsen);
                  Serial.println(" ohms");
                  
                  delay(2000);
                  }
                  }
                  flag=false;
                  }

  break;*/
}
 passflag++;
      }
  }
}
