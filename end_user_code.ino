const int sec=5000;
const int Rin=300;
float data=0;
float Vin= 3.3;
float Vout= 0;
float Rsen= 0,R2=0;
float Rref1=3200;
float Rref2=320000;    //330 Kohms
float Rref3=2000000;  //2.18 Mohms
float Rref4=8.40000; //10.10 Mohms
float buffer=0;
long int sumR=0;
float avgR=0,temp=0;
double sum=0;
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
  pinMode(6,OUTPUT);
  pinMode(11,OUTPUT);
  analogReference(EXTERNAL);
  Serial.begin(9600);
  
  
}


void loop()
{
  Serial.println("Select reference range for sensors [without any space]" );
      Serial.println("'1':0 to 1K ohm ");
      Serial.println("'2':1K to 100 K ohm ");
      Serial.println("'3':100K to 1 Megaohm ");
      Serial.println("'4':1Megaohm to 10Megaohm ");
      delay(sec);
      delay(sec);
      if(Serial.available())
      {
  for(int a=0;a<3;a++)
  {
    if(a==0)
    {
      
      //delay(sec);
      //delay(sec);
      digitalWrite(11,LOW);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);      //LSB for MC
      /*digitalWrite(9,LOW);
      digitalWrite(10,LOW);      //LSB for arduino */
      Serial.println("1st sensor reading----> ");  
      delay(sec);
      R1_select=Serial.read();
      switch(R1_select)
      {
        case '1':
        {
          //0th channel resistance w.r.t first reference
          Serial.println("Reference: 0 to 1K ohm");
          Serial.println("Calculating resistance value...please wait for 20seconds!!! ");
          digitalWrite(7,HIGH);        //LSB
          digitalWrite(8,HIGH); 
          delay(sec);
          //delay(sec);
          //delay(sec);
          for(int i=0;i<5;i++)         
           { 
            data= analogRead(A0);   
            delay(sec);
            float vol=(data*Vin)/1024.0;  
            Serial.println(vol);   
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref1;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
            }
            
            avgR=sumR/5.0;
            Serial.print("Average Resistance : ");
            Serial.println(avgR);
            
            avgR=0;
            sumR=0;
        }
        break;
        case '2':
        {
          //0th channel resistance w.r.t second reference
          Serial.println("Reference: 1K to 100K");
          Serial.println("Calculating resistance value...please wait for 20seconds!!! ");
          digitalWrite(7,LOW);        //LSB
          digitalWrite(8,LOW); 
          delay(sec);
          //delay(sec);
          //delay(sec);
          for(int i=0;i<5;i++)         
           { 
            data= analogRead(A0);   
            delay(sec);
            float vol=(data*Vin)/1024.0;  
            Serial.println(vol);   
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref2;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
            }
            
            avgR=sumR/5.0;
            Serial.print("Average Resistance : ");
            Serial.println(avgR);
            
            avgR=0;
            sumR=0;
        }
        break;
        case '3':
        {
          //0th channel resistance w.r.t third reference
          Serial.println("Reference: 100K to 1M");
          Serial.println("Calculating resistance value...please wait for 20seconds!!! ");
          digitalWrite(7,HIGH); 
          digitalWrite(8,LOW); 
          delay(sec);
          //delay(sec);
          //delay(sec);
          for(int i=0;i<5;i++)         
           {
            data= analogRead(A0);   
            delay(sec);
            float vol=(data*Vin)/1024.0;  
            Serial.println(vol);   
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref3;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
            }
            avgR=sumR/5.0;
            Serial.print("Average Resistance : ");
            Serial.println(avgR);
            
            avgR=0;
            sumR=0;
              }
        break;
        case '4':
        {
          //0th channel resistance w.r.t fourth reference
          Serial.println("Reference: 1M to 10M");
          Serial.println("Calculating resistance value...please wait for 20seconds!!! ");
          digitalWrite(7,LOW); 
          digitalWrite(8,HIGH); 
          digitalWrite(6,HIGH);    //for arduino -->digitalWrite(13,HIGH);
          delay(sec);
          //delay(sec);
          //delay(sec);
          for(int i=0;i<5;i++)         
           {
            data= analogRead(A0);   
            delay(sec);
            float vol=(data*Vin)/1024.0;     
            Serial.println(vol);
            
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref4;     //current
            R2=vol/buffer;
            
            temp=4.9-R2;
            Rsen=((R2*4.9)/temp);
            sum+=Rsen;
      
           
            }
            avgR=sum/5.0;
            Serial.print("Average Resistance : ");
            Serial.print(avgR,3);
            Serial.println(" Mega");
            
            avgR=0;
            sum=0;
              }
        break;
      }
       
      
    }
    
    else if(a==1)
    {
      digitalWrite(11,LOW);
      digitalWrite(9,HIGH);       //LSB for MC
      digitalWrite(10,LOW);    
    /* digitalWrite(9,LOW);
      digitalWrite(10,HIGH);      //LSB for arduino */
      Serial.println("2nd sensor reading----> ");
      
      delay(sec);
      R2_select=Serial.read();
      switch(R2_select)
      {
          case '1':
        {
          //1st channel resistance w.r.t first reference
          Serial.println("Reference: 0 to 1K ohm");
          Serial.println("Calculating resistance value...please wait for 20seconds!!! ");
          digitalWrite(7,HIGH);        //LSB
          digitalWrite(8,HIGH); 
          delay(sec);
          //delay(sec);
          //delay(sec);
          for(int i=0;i<5;i++)         
           { 
            data= analogRead(A0);   
            delay(sec);
            float vol=(data*Vin)/1024.0;  
            Serial.println(vol);   
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref1;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
            }
            
            avgR=sumR/5.0;
            Serial.print("Average Resistance : ");
            Serial.println(avgR);
            
            avgR=0;
            sumR=0;
        }
        break;
        case '2':
        {
          //1st channel resistance w.r.t second reference
          Serial.println("Reference: 1K to 100K");
          Serial.println("Calculating resistance value...please wait for 20seconds!!! ");
          digitalWrite(7,LOW);        //LSB
          digitalWrite(8,LOW); 
          delay(sec);
          //delay(sec);
          //delay(sec);
          for(int i=0;i<5;i++)         
           { 
            data= analogRead(A0);   
            delay(sec);
           
            float vol=(data*Vin)/1024.0; 
            Serial.println(vol);    
           
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref2;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
            }
 
            avgR=sumR/5.0;
            Serial.print("Average Resistance : ");
            Serial.println(avgR);
            
            avgR=0;
            sumR=0;
        }
        break;
        case '3':
        {
          //1st channel resistance w.r.t third reference
          Serial.println("Reference: 100K to 1M");
          Serial.println("Calculating resistance value...please wait for 20seconds!!! ");
          digitalWrite(7,HIGH); 
          digitalWrite(8,LOW); 
          delay(sec);
          for(int i=0;i<5;i++)         
           {
            data= analogRead(A0);   
            delay(sec);
            //delay(sec);
            //delay(sec);
            
            float vol=(data*Vin)/1024.0;  
            Serial.println(vol);   
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref3;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
           
            }
            avgR=sumR/5.0;
            Serial.print("Average Resistance : ");
            Serial.println(avgR);
            
            avgR=0;
            sumR=0;
              }
        break;
        case '4':
        {
          //1st channel resistance w.r.t fourth reference
          Serial.println("Reference: 1M to 10M");
          Serial.println("Calculating resistance value...please wait for 20seconds!!! ");
          digitalWrite(7,LOW); 
          digitalWrite(8,HIGH); 
          digitalWrite(6,HIGH);    //for arduino -->digitalWrite(13,HIGH);
          delay(sec);
          ///delay(sec);
          //delay(sec);
          for(int i=0;i<5;i++)         
           {
            data= analogRead(A0);   
            delay(sec);
            
            float vol=(data*Vin)/1024.0;  
            Serial.println(vol);   
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref4;     //current
            R2=vol/buffer;
            
            temp=4.9-R2;
            Rsen=((R2*4.9)/temp);
            sum+=Rsen;
      
           
            }
 
            avgR=sum/5.0;
            Serial.print("Average Resistance : ");
            Serial.print(avgR,3);
            Serial.println(" Mega");
           
            avgR=0;
            sum=0;
              }
        break;
      }
    }
    
    else if(a==2)
    {
      digitalWrite(11,LOW);
      digitalWrite(10,HIGH);
      digitalWrite(9,LOW);    //LSB for MC
     /* digitalWrite(9,HIGH);
      digitalWrite(10,LOW);      //LSB for arduino*/
      Serial.println("3rd sensor reading----> ");
      
      R3_select=Serial.read();
      switch(R3_select)
      {
          case '1':
        { 
          //2nd channel resistance w.r.t first reference
          Serial.println("Reference: 0 to 1K ohm");
          Serial.println("Calculating resistance value...please wait for 20seconds!!! ");
          digitalWrite(7,HIGH);        //LSB
          digitalWrite(8,HIGH); 
          delay(sec);
          //delay(sec);
          //delay(sec);
          for(int i=0;i<5;i++)         
           { 
            data= analogRead(A0);   
            delay(sec);
            float vol=(data*Vin)/1024.0;  
            Serial.println(vol);   
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref1;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
            }
            
            avgR=sumR/5.0;
            Serial.print("Average Resistance : ");
            Serial.println(avgR);
            
            avgR=0;
            sumR=0;
        }
        break;
        case '2':
        {
          //2nd channel resistance w.r.t second reference
          Serial.println("Reference: 1K to 100K");
          Serial.println("Calculating resistance value...please wait for 20seconds!!! ");
          digitalWrite(7,LOW);        //LSB
          digitalWrite(8,LOW); 
          delay(sec);
          //delay(sec);
          //delay(sec);
          for(int i=0;i<5;i++)         
           { 
            data= analogRead(A0);   
            delay(sec);
            
            float vol=(data*Vin)/1024.0; 
            Serial.println(vol);    
          
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref2;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
         
            }
       
            avgR=sumR/5.0;
            Serial.print("Average Resistance : ");
            Serial.println(avgR);
            
            avgR=0;
            sumR=0;
        }
        break;
        case '3':
        {
          //2nd channel resistance w.r.t third reference
          Serial.println("Reference: 100K to 1M");
          Serial.println("Calculating resistance value...please wait for 20seconds!!! ");
          digitalWrite(7,HIGH); 
          digitalWrite(8,LOW); 
          delay(sec);
          //delay(sec);
          //delay(sec);
          for(int i=0;i<5;i++)         
           {
            data= analogRead(A0);   
            delay(sec);
            
            float vol=(data*Vin)/1024.0;
            Serial.println(vol);     
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref3;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
           
            }
   
            avgR=sumR/5.0;
            Serial.print("Average Resistance : ");
            Serial.println(avgR);
           
            avgR=0;
            sumR=0;
              }
        break;
        case '4':
        {
          //2nd channel resistance w.r.t fourth reference
          Serial.println("Reference: 1M to 10M");
          Serial.println("Calculating resistance value...please wait for 20seconds!!! ");
          digitalWrite(7,LOW); 
          digitalWrite(8,HIGH); 
          digitalWrite(6,HIGH);    //for arduino -->digitalWrite(13,HIGH);
          delay(sec);
          //delay(sec);
          //delay(sec);
          for(int i=0;i<5;i++)         
           {
            data= analogRead(A0);   
            delay(sec);
            
            float vol=(data*Vin)/1024.0; 
            Serial.println(vol);    
         
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref4;     //current
            R2=vol/buffer;
            
            temp=4.9-R2;
            Rsen=((R2*4.9)/temp);
            sum+=Rsen;
      
            }
   
            avgR=sum/5.0;
            Serial.print("Average Resistance : ");
            Serial.print(avgR,3);
            Serial.println(" Mega");
           
            avgR=0;
            sum=0;
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
        Serial.println("Please select range!!!!");
        }
}
       
  
