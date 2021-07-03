#include <LiquidCrystal.h>

const int sec=5000;
const int Rin=200;
float data=0;
float Vin= 3.3;
float Vout= 0;
float Rsen= 0,R2=0;
float Rref1=99400;    //99.4 Kohms
float Rref2=1003000;  //1.003 Mohms
float Rref3=10160000; //10.16 Mohms
float buffer=0;
long int sumR=0;
float avgR=0;

void setup()
{
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT);
  analogReference(EXTERNAL);
  Serial.begin(9600);
}


void loop()
{
 
    char R_select;
        R_select=Serial.read();
        switch (R_select)
        {
          case '1':
        Serial.println("No connection in parallel");
        delay(sec);
        //digitalWrite(4,HIGH);
        digitalWrite(2,LOW);
        digitalWrite(3,LOW);
      
    //First channel resistance w.r.t first reference
    Serial.println("1st sensor reading----> ");
    //for 13th pin--000 
     digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW); 
      digitalWrite(8,LOW); 
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);      //LSB
     for(int i=0;i<5;i++)         
     {
       delay(sec);
    delay(sec);
      data= analogRead(A0);   
      delay(sec);
      Serial.print("Data Read=");
      Serial.println(data);
      float vol=(data*Vin)/1024.0;     
      Serial.print("Voltage=");
      Serial.println(vol);
      
      //unknown resistance calculated
      buffer=(Vin-vol)/Rref1;     //current
      R2=vol/buffer;
      
      Rsen=R2-Rin;
      sumR+=Rsen;

      Serial.print("Resistance =");
      Serial.println(Rsen, 3);
     
      }
      Serial.println(sumR);
      avgR=sumR/5.0;
      Serial.print("Average Resistance : ");
      Serial.println(avgR);
      avgR=0;
      sumR=0;


//Seventh channel resistance w.r.t first reference
      Serial.println("2nd sensor reading----> ");
       digitalWrite(2,HIGH);
        digitalWrite(3,HIGH);
      delay(sec);
      delay(sec);
       digitalWrite(2,LOW);
        digitalWrite(3,LOW);
        delay(sec);
      //for 13th pin--000 
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW); 
      digitalWrite(8,HIGH); 
      digitalWrite(9,HIGH);
      digitalWrite(10,HIGH);      //LSB
       delay(sec);
     for(int i=0;i<5;i++)         
     {
      
    
      data= analogRead(A0);   
      //data=d-70;
      delay(sec);
      delay(sec);
      Serial.print("Data Read=");
      Serial.println(data);
      float vol=(data*Vin)/1024.0;     
      Serial.print("Voltage=");
      Serial.println(vol);
      
      //unknown resistance calculated
      buffer=(Vin-vol)/Rref1;     //current
      R2=vol/buffer;
      
      Rsen=R2-Rin;
      sumR+=Rsen;

      Serial.print("Resistance =");
      Serial.println(Rsen, 3);
     
      }
      Serial.println(sumR);
      avgR=sumR/5.0;
      Serial.print("Average Resistance : ");
      Serial.println(avgR);
      avgR=0;
      sumR=0;

   //Third channel resistance w.r.t second reference           
   Serial.println("3rd sensor reading----> ");
   digitalWrite(2,HIGH);
        digitalWrite(3,HIGH);
      delay(sec);
      delay(sec);
       digitalWrite(2,LOW);
        digitalWrite(3,LOW);
        delay(sec);
   //for 3rd pin--011
      digitalWrite(5,HIGH);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);    
      digitalWrite(9,HIGH);
      digitalWrite(10,HIGH);
      delay(sec);
   for(int i=0;i<5;i++)
    {
      delay(sec);
      delay(sec);
      data= analogRead(A0);  
      
      //data=d-70;
      Serial.print("Data Read=");
      Serial.println(data);
      float vol=(data*Vin)/1024.0; 
      //vol=vol-0.2;    
      Serial.print("Voltage=");
      Serial.println(vol);
      delay(sec);
      //unknown resistance calculated
      buffer=(Vin-vol)/Rref2;     //current
      R2=vol/buffer;
      Rsen=R2-Rin;
      sumR+=Rsen;

      Serial.print("Resistance =");
      Serial.println(Rsen);
      
      }
      Serial.println(sumR);
      avgR=sumR/5.0;
      Serial.print("Average Resistance : ");
      Serial.println(avgR);

      avgR=0;
      sumR=0;

//Sixth channel resistance w.r.t second reference
   Serial.println("4th sensor reading----> ");
   //for 15th pin--001
    digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);
    delay(sec);
    delay(sec);
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    delay(sec);
      digitalWrite(5,HIGH);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,HIGH);    
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);
      delay(sec);
   for(int i=0;i<5;i++)
    {
      delay(sec);
      delay(sec);
      data= analogRead(A0);  
      delay(sec);
      Serial.print("Data Read=");
      Serial.println(data);
      float vol=(data*Vin)/1024.0;   
      //vol=vol-0.2;  
      Serial.print("Voltage=");
      Serial.println(vol);
      delay(sec);
      //unknown resistance calculated
      buffer=(Vin-vol)/Rref2;     //current
      R2=vol/buffer;
      Rsen=R2-Rin;
      sumR+=Rsen;

      Serial.print("Resistance =");
      Serial.println(Rsen);
      
      }
      Serial.println(sumR);
      avgR=sumR/5.0;
      Serial.print("Average Resistance : ");
      Serial.println(avgR);

      avgR=0;
      sumR=0;

  
break;
case '2':
        
       Serial.println("Parallel Connection");
        delay(sec);
        //digitalWrite(4,LOW);
      
    //Third channel resistance w.r.t third reference with parallel resistance
     
      Serial.print("1st sensor reading ");
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);    
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      digitalWrite(12,HIGH);
      digitalWrite(13,HIGH);
      delay(sec);   
      delay(sec);
     for(int i=0;i<5;i++)         
     {   
      
      data= analogRead(A0);   
      delay(sec);
      Serial.println("Data Read=");
      Serial.println(data);
      float vol=(data*Vin)/1024.0;     
      Serial.print("Voltage=");
      Serial.println(vol);
      delay(sec);
      //unknown resistance calculated
      buffer=(Vin-vol)/Rref3;     //current
      R2=vol/buffer;
      
      //Rsen=R2-Rin;
      sumR+=R2;


      Serial.print("Resistance =");
      Serial.println(R2);
      }
      Serial.println(sumR);
      avgR=sumR/5.0;
      Serial.print("Average Resistance : ");
      Serial.println(avgR);
      avgR=0;
      sumR=0;

//Second channel resistance w.r.t third reference with parallel resistance
      Serial.print("2nd sensor reading ");
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(7,HIGH);
      digitalWrite(8,LOW);    
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
      digitalWrite(11,HIGH);
      digitalWrite(12,HIGH);
      digitalWrite(13,HIGH);
      delay(sec);   
      delay(sec);
     for(int i=0;i<5;i++)         
     {   
      
      data= analogRead(A0);   
      delay(sec);
      Serial.println("Data Read=");
      Serial.println(data);
      float vol=(data*Vin)/1024.0;     
      Serial.print("Voltage=");
      Serial.println(vol);
      delay(sec);
      //unknown resistance calculated
      buffer=(Vin-vol)/Rref3;     //current
      R2=vol/buffer;
      
      //Rsen=R2-Rin;
      sumR+=R2;


      Serial.print("Resistance =");
      Serial.println(R2);
      }
      Serial.println(sumR);
      avgR=sumR/5.0;
      Serial.print("Average Resistance : ");
      Serial.println(avgR);
      avgR=0;
      sumR=0;

break;

        }
             
}
