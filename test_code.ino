const int sec1=10000;
const int sec=2000;
const int Rin=300;
float data=0;
float Vin= 3.3;
float Vout= 0;
float Rsen= 0,R2=0;
float Rref1=328000;
float Rref2=2180000;
float Rref3=10.00;
float Rrefp=5.00;
float buffer=0;
float temp=0;
bool flag=true;
char R1_select;
char R2_select;
char R3_select;

void setup()
{
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(2,OUTPUT);
  analogReference(EXTERNAL);
  Serial.begin(9600);
  Serial.println("Select reference range for sensors [without any space]" );
      Serial.println("'1':1K to 100 Kohm ");
      Serial.println("'2':100K to 1 Megaohm ");
      Serial.println("'3':1Megaohm to 10Megaohm ");
      delay(sec);
      
     
}


void loop()
{
  if(Serial.available())
  {
  for(int a=0;a<3;a++)
  {
    if(a==0)
    {
      
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);      //LSB
      Serial.println("1st sensor reading----> ");
     
      R1_select=Serial.read();
      switch(R1_select)
      {
        case '1':
        {
          //0th channel resistance w.r.t first reference
          Serial.println("Reference: 1K to 100K");
          digitalWrite(7,LOW);        //LSB
          digitalWrite(8,LOW); 
          
            data= analogRead(A0);   //voltage across the sensor
           
            float vol=(data*Vin)/1024.0;     //ADC conversion of volatge
           
            //unknown resistance calculation
            buffer=(Vin-vol)/Rref1;     //current
            R2=vol/buffer;        //Senosr Resistance
            Rsen=R2-Rin;  
      
            Serial.print("Voltage=");
            Serial.println(vol);
            Serial.print("Resistance : ");
            Serial.println(Rsen);
            
           
        }
        break;
        case '2':
        {
          //0th channel resistance w.r.t second reference
          Serial.println("Reference: 100K to 1M");
          digitalWrite(7,HIGH); 
          digitalWrite(8,LOW); 
         
            data= analogRead(A0);   
            
            float vol=(data*Vin)/1024.0;     
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref2;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
           
            Serial.print("Voltage=");
            Serial.println(vol);
           
            Serial.print("Resistance : ");
            Serial.println(Rsen);
            
            
              }
        break;
        case '3':
        {
          //0th channel resistance w.r.t third reference
          Serial.println("Reference: 1M to 10M");
          digitalWrite(7,LOW); 
          digitalWrite(8,HIGH); 
          digitalWrite(13,HIGH);
          delay(500);
          
            data= analogRead(A0);   
            float vol=(data*Vin)/1024.0;     
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref3;     //current
            R2=vol/buffer;
            Serial.print("Eqv res :");
            Serial.println(R2);
            
            temp=(Rrefp-R2);
            Rsen=((R2*Rrefp)/temp);
           
            Serial.print("Voltage=");
            Serial.println(vol);
            
            Serial.print("Resistance : ");
            Serial.println(Rsen*1000000);
            
           // digitalWrite(13,LOW);
            
              }
        break;
      }
       
      
    }
    
    else if(a==1)
    {
      
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);      //LSB
      Serial.println("2nd sensor reading----> ");
     
     R2_select=Serial.read();
      switch(R2_select)
      {
        case '1':
        {
          //1st channel resistance w.r.t first reference
          Serial.println("Reference: 1K to 100K");
          digitalWrite(7,LOW);        //LSB
          digitalWrite(8,LOW); 
         
            data= analogRead(A0);   
            
            float vol=(data*Vin)/1024.0;     
            
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref1;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            
            Serial.print("Voltage=");
            Serial.println(vol);
            
            Serial.print("Resistance : ");
            Serial.println(Rsen);
            

        }
        break;
        case '2':
        {
          //1st channel resistance w.r.t second reference
          Serial.println("Reference: 100K to 1M");
          digitalWrite(7,HIGH); 
          digitalWrite(8,LOW); 
          
            data= analogRead(A0);   
            
            float vol=(data*Vin)/1024.0;     
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref2;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            
            Serial.print("Voltage=");
            Serial.println(vol);
            
            Serial.print("Resistance : ");
            Serial.println(Rsen);
            
            
            
              }
        break;
        case '3':
        {
          //1st channel resistance w.r.t third reference
          Serial.println("Reference: 1M to 10M");
          digitalWrite(7,LOW); 
          digitalWrite(8,HIGH); 
          digitalWrite(13,HIGH);
          delay(500);
         
            data= analogRead(A0);   
            
            float vol=(data*Vin)/1024.0;     
           
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref3;     //current
            R2=vol/buffer;
            Serial.print("Eqv res :");
            Serial.println(R2);
            
            temp=(Rrefp-R2);
            Rsen=((R2*Rrefp)/temp);
            
            Serial.print("Voltage=");
            Serial.println(vol);
            
            Serial.print("Resistance : ");
            Serial.println(Rsen*1000000);
            
            //digitalWrite(13,LOW);
              }
        break;
      }
    }
    
    else if(a==2)
    {
      
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);      //LSB
      Serial.println("3rd sensor reading----> ");
      
      
      R3_select=Serial.read();
      switch(R3_select)
      {
        case '1':
        {
          //2nd channel resistance w.r.t first reference
          Serial.println("Reference: 1K to 100K");
          digitalWrite(7,LOW);        //LSB
          digitalWrite(8,LOW); 
         
            data= analogRead(A0);   
            
            float vol=(data*Vin)/1024.0;     
            
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref1;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            
            Serial.print("Voltage=");
            Serial.println(vol);
            
            Serial.print("Resistance : ");
            Serial.println(Rsen);
            
            
           
        }
        break;
        case '2':
        {
          //2nd channel resistance w.r.t second reference
          Serial.println("Reference: 100K to 1M");
          digitalWrite(7,HIGH); 
          digitalWrite(8,LOW); 
          
            data= analogRead(A0);   
           
            float vol=(data*Vin)/1024.0;     
           
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref2;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            
            Serial.print("Voltage=");
            Serial.println(vol);
            
            Serial.print("Resistance : ");
            Serial.println(Rsen);
            
            
              }
        break;
        case '3':
        {
          //2nd channel resistance w.r.t third reference
          Serial.println("Reference: 1M to 10M");
          digitalWrite(7,LOW); 
          digitalWrite(8,HIGH); 
          digitalWrite(13,HIGH);
          delay(500);
         
            data= analogRead(A0);   
           
            float vol=(data*Vin)/1024.0;     
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref3;     //current
            R2=vol/buffer;
            Serial.print("Eqv res :");
            Serial.println(R2);
            
            temp=(Rrefp-R2);
            Rsen=((R2*Rrefp)/temp);
            
            Serial.print("Voltage=");
            Serial.println(vol);
            
            Serial.print("Resistance : ");
            Serial.println(Rsen*1000000);
            //digitalWrite(13,LOW);
            
              }
        break;
      }
    }
    
    else
    {
      Serial.println("No sensor connected");
    }
    delay(sec);
  }
}
else
{
  
  Serial.println("Waiting for input!!!!");
  delay(sec1);
  }
}
       
  
