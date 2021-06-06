long int wait=500000;
const int sec=2000;
const int Rin=300;
float data=0;
float Vin= 3.3;
float Vout= 0,vol=0;
float Rsen= 0,R2=0;
float Rref1=328000;
float Rref2=2180000;
float Rref3=10100000;
float buffer=0;
int count=0;

bool flag=true;
char r;

void(* resetFunc) (void) = 0; 

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
  Serial.println("Start reading(Y/N)?");
  delay (sec);

}


void loop()
{
  
  if(Serial.available())
  {
    r=Serial.read();
    switch(r)
    {
      case 'Y':
    {
      Serial.println("Reading...");
      
  for(int a=0;a<3;a++)
  {
    if(a==0)
    {
      float  vol_array[3] ={0,0,0};
      float   Rsen_array[3] ={0,0,0};
      int i=0,j=0,count=0;
      float temp=0,temp_vol=0,temp_r=0;
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);      //LSB
      Serial.println("R1---> ");
  
          //0th channel resistance w.r.t first reference
          
          digitalWrite(7,LOW);        //LSB
          digitalWrite(8,LOW); 
          data= analogRead(A0);   //voltage across the sensor
          vol_array[i]=(data*Vin)/1024.0;     //ADC conversion of volatge

           if((vol_array[i]>0.1)&&(vol_array[i]<1))
           {
            //unknown resistance calculation
            buffer=(Vin-vol_array[i])/Rref1;     //current
            R2=vol_array[i]/buffer;        //Senosr Resistance

            Rsen_array[i] =R2-Rin;
      
            Serial.print("Voltage=");
            Serial.print(vol_array[i]);
            Serial.print(" Resistance : ");
            Serial.println(Rsen_array[i]);
            count++;
            i++;
            j=i;
           }
           
     
          //0th channel resistance w.r.t second reference
          
          digitalWrite(7,HIGH); 
          digitalWrite(8,LOW); 

          data= analogRead(A0);   //voltage across the sensor
          vol_array[i]=(data*Vin)/1024.0;     //ADC conversion of volatge

           if((vol_array[i]>0.1)&&(vol_array[i]<1))
           {
            //unknown resistance calculation
            buffer=(Vin-vol_array[i])/Rref2;     //current
            R2=vol_array[i]/buffer;        //Senosr Resistance

            Rsen_array[i]=R2-Rin;
      
            Serial.print("Voltage :");
            Serial.print(vol_array[i]);
            Serial.print(" Resistance : ");
            Serial.println(Rsen_array[i]);
            count++;
            j=i;
            i++;
           }

          //0th channel resistance w.r.t third reference
         
          digitalWrite(7,LOW); 
          digitalWrite(8,HIGH); 
          
          data= analogRead(A0);   //voltage across the sensor
          vol_array[i]=(data*Vin)/1024.0;     //ADC conversion of volatge

           if((vol_array[i]>0.1)&&(vol_array[i]<1))
           {
            //unknown resistance calculation
            buffer=(Vin-vol_array[i])/Rref3;     //current
            R2=vol_array[i]/buffer;        //Senosr Resistance
            
            Rsen_array[i]=R2-Rin;
            Serial.print("Voltage :");
            Serial.print(vol_array[i]);
            Serial.print(" Resistance : ");
            Serial.println(Rsen_array[i]);
            count++;
            j=i;
            i++;
           }

           
       float opt=abs(0.5-vol_array[0]);
       vol = vol_array[0];
       temp_r = Rsen_array[0];
       for(int j=1;j<count;j++)
        {
         if (abs(0.5-vol_array[j])<opt )
         {
           vol = vol_array[j];
           temp_r = Rsen_array[j];
           
         }
        
        }

           

        Serial.print("Final Voltage=");
        Serial.println(vol);
        Serial.print("Final Resistance : ");
        Serial.println(temp_r);
           
    }

  

    else if(a==1)
    {
      float  vol_array[3] ={0,0,0};
      float   Rsen_array[3] ={0,0,0};
      int i=0,j=0,count=0;
      float temp=0,temp_vol=0,temp_r=0;

      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);      //LSB
      Serial.println("2nd sensor ----> ");

      //0th channel resistance w.r.t first reference
          
        digitalWrite(7,LOW);        //LSB
        digitalWrite(8,LOW); 

       
       
          data= analogRead(A0);   //voltage across the sensor
          vol_array[i]=(data*Vin)/1024.0;     //ADC conversion of volatge

         if((vol_array[i]>0.1)&&(vol_array[i]<1))
         {
          //unknown resistance calculation
          buffer=(Vin-vol_array[i])/Rref1;     //current
          R2=vol_array[i]/buffer;        //Senosr Resistance

          Rsen_array[i] =R2-Rin;
    
          Serial.print("Voltage=");
          Serial.print(vol_array[i]);
          Serial.print(" Resistance : ");
          Serial.println(Rsen_array[i]);
          count++;
          i++;
          j=i;
         }
           
     
        //0th channel resistance w.r.t second reference
     
        digitalWrite(7,HIGH); 
        digitalWrite(8,LOW); 

        digitalWrite(13,LOW);
        
        data= analogRead(A0);   //voltage across the sensor
        vol_array[i]=(data*Vin)/1024.0;     //ADC conversion of volatge

         if((vol_array[i]>0.1)&&(vol_array[i]<1))
         {
          //unknown resistance calculation
          buffer=(Vin-vol_array[i])/Rref2;     //current
          R2=vol_array[i]/buffer;        //Senosr Resistance

          Rsen_array[i]=R2-Rin;
    
          Serial.print("Voltage :");
          Serial.print(vol_array[i]);
          Serial.print(" Resistance : ");
          Serial.println(Rsen_array[i]);
          count++;
          j=i;
          i++;
         }

          //0th channel resistance w.r.t third reference
          
          digitalWrite(7,LOW); 
          digitalWrite(8,HIGH); 
          
          data= analogRead(A0);   //voltage across the sensor
          vol_array[i]=(data*Vin)/1024.0;     //ADC conversion of volatge

           if((vol_array[i]>0.1)&&(vol_array[i]<1))
           {
            //unknown resistance calculation
            buffer=(Vin-vol_array[i])/Rref3;     //current
            R2=vol_array[i]/buffer;        //Senosr Resistance

            Rsen_array[i]=R2-Rin;
      
            Serial.print("Voltage :");
            Serial.print(vol_array[i]);
            Serial.print(" Resistance : ");
            Serial.println(Rsen_array[i]);
            count++;
            j=i;
            i++;
           }
           
//finding the optimum reading
         float opt=abs(0.5-vol_array[0]);
         vol = vol_array[0];
         temp_r = Rsen_array[0];
         for(int j=1;j<count;j++)
          {
           if (abs(0.5-vol_array[j])<opt )
           {
             vol = vol_array[j];
             temp_r = Rsen_array[j];
             
           }
          
          }
           
            Serial.print("Final Voltage=");
            Serial.println(vol);
            Serial.print("Final Resistance : ");
            Serial.println(temp_r);
      
    }
    else if(a==2)
    {
      float  vol_array[3] ={0,0,0};
      float   Rsen_array[3] ={0,0,0};
      int i=0,j=0,count=0;
      float temp=0,temp_vol=0,temp_r=0;
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);      //LSB
      Serial.println("3rd sensor ----> ");

      //0th channel resistance w.r.t first reference
          
      digitalWrite(7,LOW);        //LSB
      digitalWrite(8,LOW); 
     
      data= analogRead(A0);   //voltage across the sensor
      vol_array[i]=(data*Vin)/1024.0;     //ADC conversion of volatge

       if((vol_array[i]>0.1)&&(vol_array[i]<1))
       {
        //unknown resistance calculation
        buffer=(Vin-vol_array[i])/Rref1;     //current
        R2=vol_array[i]/buffer;        //Senosr Resistance

        Rsen_array[i] =R2-Rin;
  
        Serial.print("Voltage=");
        Serial.print(vol_array[i]);
        Serial.print(" Resistance : ");
        Serial.println(Rsen_array[i]);
        count++;
        i++;
        j=i;
       }
           
     
      //0th channel resistance w.r.t second reference
      
      digitalWrite(7,HIGH); 
      digitalWrite(8,LOW); 
      
      data= analogRead(A0);   //voltage across the sensor
      vol_array[i]=(data*Vin)/1024.0;     //ADC conversion of volatge

       if((vol_array[i]>0.1)&&(vol_array[i]<1))
       {
        //unknown resistance calculation
        buffer=(Vin-vol_array[i])/Rref2;     //current
        R2=vol_array[i]/buffer;        //Senosr Resistance

        Rsen_array[i]=R2-Rin;
  
        Serial.print("Voltage :");
        Serial.print(vol_array[i]);
        Serial.print(" Resistance : ");
        Serial.println(Rsen_array[i]);
        count++;
        j=i;
        i++;
       }

      //0th channel resistance w.r.t third reference
      
      digitalWrite(7,LOW); 
      digitalWrite(8,HIGH); 
     
      data= analogRead(A0);   //voltage across the sensor
      vol_array[i]=(data*Vin)/1024.0;     //ADC conversion of volatge

       if((vol_array[i]>0.1)&&(vol_array[i]<1))
       {
        //unknown resistance calculation
        buffer=(Vin-vol_array[i])/Rref3;     //current
        R2=vol_array[i]/buffer;        //Senosr Resistance

        Rsen_array[i]=R2-Rin;
  
        Serial.print("Voltage :");
        Serial.print(vol_array[i]);
        Serial.print(" Resistance : ");
        Serial.println(Rsen_array[i]);
        count++;
        j=i;
        i++;
       }

       float opt=abs(0.5-vol_array[0]);
       vol = vol_array[0];
       temp_r = Rsen_array[0];
       for(int j=1;j<count;j++)
        {
         if (abs(0.5-vol_array[j])<opt )
         {
           vol = vol_array[j];
           temp_r = Rsen_array[j];
           
         }
        
        }


      Serial.print("Final Voltage=");
      Serial.println(vol);
      Serial.print("Final Resistance : ");
      Serial.println(temp_r);


      //do reset
        Serial.println("RESET DONE");
        delay(1000);
        resetFunc();
        Serial.println("Never should be printed");
        delay(1000);
    }
    
  }
    }
  break;
    case 'N':
    {
      Serial.println("Waiting...");
    }
    }
  }
  else
  {
    
  }
}

       
  
