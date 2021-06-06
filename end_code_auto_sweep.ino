const int sec=2000;
long int wait=500000;
const int Rin=300;
float data=0,vol=0;
float Vin= 3.3;
float Vout= 0;
float Rsen= 0,R2=0;
float Rref1=330000;     //330 Kohms
float Rref2=1000000;    //1 Mohms
float Rref3=2000000;  //2.18 Mohms
float Rref4=10000000; //10.10 Mohms
float buffer=0;
long int sumR=0;
float avgR=0,temp=0;
double sum=0;
float temp_vol=0,final_r=0,final_vol=0;
bool flag=true;
float vol_array[] ={};
float Rsen_array[] ={};
char r;

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
  Serial.println("Start reading(Y/N)?");
  delay("sec");
  
  
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
            int i=0,j=0,count=0;
            digitalWrite(11,LOW);
            digitalWrite(10,LOW);
            digitalWrite(9,LOW);      //LSB for MC
            Serial.println("R1----> ");  

            //0th channel resistance w.r.t first reference = 330K
            digitalWrite(7,HIGH);        //LSB
            digitalWrite(8,HIGH); 
            for(int i=0;i<5;i++)         
             {
              data= analogRead(A0);   
              vol=(data*Vin)/1024.0;  
              //unknown resistance calculated
              buffer=(Vin-vol)/Rref1;     //current
              R2=vol/buffer;
              Rsen=R2-Rin;
              sumR+=Rsen;
              }
            avgR=sumR/5.0;
            if((vol>0.1)&&(vol<1))
            {
              vol_array[i] = vol;
              Rsen_array[i] = avgR;
              Serial.print("Voltage=");
              Serial.print(vol_array[i]);
              Serial.print(" Resistance : ");
              Serial.println(Rsen_array[i]);
              count++;
              i++;//
              j=i;
           }
           vol=0;
           avgR=0;
           sumR=0;
             
           //0th channel resistance w.r.t second reference = 1M
          digitalWrite(7,LOW);        //LSB
          digitalWrite(8,LOW); 
          for(int i=0;i<5;i++)
          {          
            data= analogRead(A0);   
            vol=(data*Vin)/1024.0;  
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref2;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
          }
           avgR=sumR/5.0;
            if((vol>0.1)&&(vol<1))
            {
              vol_array[i] = vol;
              Rsen_array[i] = avgR;
              Serial.print("Voltage=");
              Serial.print(vol_array[i]);
              Serial.print(" Resistance : ");
              Serial.println(Rsen_array[i]);
              count++;
              i++;//
              j=i;
           }
           vol=0;
           avgR=0;
           sumR=0;
           
           //0th channel resistance w.r.t third reference =2M
          digitalWrite(7,HIGH); 
          digitalWrite(8,LOW);
          for(int i=0;i<5;i++)
          {
            data= analogRead(A0);   
            vol=(data*Vin)/1024.0;  
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref3;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
          }
          avgR=sumR/5.0;
            if((vol>0.1)&&(vol<1))
            {
              vol_array[i] = vol;
              Rsen_array[i] = avgR;
              Serial.print("Voltage=");
              Serial.print(vol_array[i]);
              Serial.print(" Resistance : ");
              Serial.println(Rsen_array[i]);
              count++;
              i++;//
              j=i;
           }
           vol=0;
           avgR=0;
           sumR=0;

                    
          //0th channel resistance w.r.t fourth reference = 10M
          digitalWrite(7,LOW); 
          digitalWrite(8,HIGH); 
          digitalWrite(6,HIGH);    //for arduino -->digitalWrite(13,HIGH);
          
          for(int i=0;i<5;i++)  
          {       
           data= analogRead(A0);   
           vol=(data*Vin)/1024.0;     
           //unknown resistance calculated
          buffer=(Vin-vol)/Rref4;     //current
          R2=vol/buffer;
          
          temp=4.9-R2;
          Rsen=((R2*4.9)/temp);
          sum+=Rsen;
          }
           avgR=sumR/5.0;
            if((vol>0.1)&&(vol<1))
            {
              vol_array[i] = vol;
              Rsen_array[i] = avgR;
              Serial.print("Voltage=");
              Serial.print(vol_array[i]);
              Serial.print(" Resistance : ");
              Serial.println(Rsen_array[i]);
              count++;
              i++;//
              j=i;
           }
           vol=0;
           avgR=0;
           sumR=0;

           switch(count)
           {
            case 0:
            {
              Serial.println("Voltage out of range OR Nothing connected");
            }
            break;
            case 1:
            {
              final_r = Rsen_array[j];
              final_vol = vol_array[j];
            }
            break;
            default:
            {
              temp_vol= abs(vol_array[0]-0.5);
               final_r = Rsen_array[0];
               final_vol = vol_array[0];
               for(int j=1;j<count;j++)
               {
                if (abs(vol_array[j]-0.5)< temp_vol )
                {
                  temp_vol = abs(vol_array[j]-0.5);
                  final_vol = vol_array[j];
                  final_r = Rsen_array[j];
                }
               }
            }
            break;
           }
           
            Serial.print("Final Voltage=");
            Serial.println(final_vol);
            Serial.print("Final Resistance : ");
            Serial.println(final_r);
          }  
            
    
              else if(a==1)
              {
                digitalWrite(11,LOW);
                digitalWrite(9,HIGH);       //LSB for MC
                digitalWrite(10,LOW);    
              
                Serial.println("R2----> ");
          
              }
              
              else if(a==2)
              {
                digitalWrite(11,LOW);
                digitalWrite(10,HIGH);
                digitalWrite(9,LOW);    //LSB for MC
              
                Serial.println("R3----> ");
              }
                 
          else
          {
            Serial.println("No sensor connected");
          }
          delay(sec);
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
    if(millis()>wait)
    {
      Serial.println("No command received!!");
      exit(0);
    }
    
  }
}
       
  
