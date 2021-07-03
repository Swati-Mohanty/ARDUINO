//sar with 7 switches
//with serial input
//displays current and resistance
//duty cycle 10% at starting
//0.5V readings
//software rest enabled
//BOARD  SENSOR   MUX
//CH3    S1       011
//CH2    S2       010
//CH1    S3       001
//CH0    Scontrol 000


#define NOP __asm__ __volatile__("nop\n\t");

int delay_time = 4;   //4ms
int switch_time = 2000;
float c_t = 0;  //100E-9/(4*1E-3);

float data1=0,data2=0;
float Vin= 5;
float vout1=0;

float Rsen1= 0;
float Rsen2= 0;
float Rsen3= 0;
float Rctrl= 0;
float Rref_arr[7] = {12000.0, 6000.0, 1600.00,820.0, 560.0, 220.0,100.0};

float Rref=0;
float Rref1=0;  
float Rref2=0; 
float Rref3=0;
float Rref4=0;

int d[]={0,0,0,0,0,0,0}, pin_select[7]={};
int store_mat[7][7]={};
int ref1_pins[7] = {};
int ref2_pins[7] = {};
int ref3_pins[7] = {};
int ref4_pins[7] = {};

float vout1_ramp[10]={};
float vout2_ramp[10]={};

bool flag = true;
int check_bit=0,counter=0,ch=0;



void setup() 
{
 //sensor pins
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);   
  //switch pins
  pinMode(2,OUTPUT);      //uc-4
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);  
  pinMode(12,OUTPUT); //LSB uc-18
  pinMode(13,OUTPUT);       //uc-19
  pinMode(7,OUTPUT);        //uc-13
  pinMode(8,OUTPUT);    //MSB uc-14
  //clock pins
  pinMode(9,OUTPUT);    //CLK
  pinMode(5,OUTPUT);    //CLKB

  
  //analogReference(EXTERNAL);
  Serial.begin(9600);
  //10% duty cycle
  analogWrite(5, 25);
 

}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop()
{
   if(Serial.available())
   {
      while(flag==true)
      {
        digitalWrite(9,LOW);    //CLK

        delay(500);
      
        data1 = analogRead(A0);
        
        vout1 = (data1*Vin)/1023.0;
        Serial.println("Initializing... ");
        //Serial.println(vout1);
        
        //First Sensor selection
        digitalWrite(11,LOW);
        digitalWrite(10,HIGH);
        digitalWrite(6,HIGH);      //LSB for MC
      
        ch=0;
        Rref1 = reference_calculation(ch);
        Serial.print("Reference1 :");
        Serial.println(Rref1);
      
        //Second Sensor selection
        digitalWrite(11,LOW);
        digitalWrite(10,HIGH);
        digitalWrite(6,LOW);      //LSB for MC
      
        ch=1;
        Rref2 = reference_calculation(ch);
        Serial.print("Reference2 :");
        Serial.println(Rref2);
      
        //Third Sensor selection
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(6,HIGH);      //LSB for MC
      
        ch=2;
        Rref3 = reference_calculation(ch);
        Serial.print("Reference3 :");
        Serial.println(Rref3);

        //Control Sensor selection
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(6,LOW);      //LSB for MC
      
        ch=3;
        Rref4 = reference_calculation(ch);
        Serial.print("Reference4 :");
        Serial.println(Rref4);
        
        ch=0;  
        digitalWrite(11,LOW);
        digitalWrite(10,HIGH);
        digitalWrite(6,HIGH);      //LSB for MC
        pinset(ref1_pins);
        delay(switch_time);
        flag = false;      
     }

   for(int ch=0;ch<4;ch++)
   {
      float Rsen_arr[5]= {};
      int number=0;
      double sum=0;
      int i=0;

    
      //10% duty cycle    -->0.5V
      analogWrite(5, 25);

      delay(delay_time);
      data1 = analogRead(A0);
      data2= analogRead(A1); 
      vout1_ramp[i] = (data1*Vin)/1023.0;   
      vout2_ramp[i]=(data2*Vin)/1023.0;
      i++;  

      
      //10% duty cycle    -->0.5V
      analogWrite(5, 25);

      delay(delay_time);
      data1 = analogRead(A0);
      data2= analogRead(A1); 
      vout1_ramp[i] = (data1*Vin)/1023.0;   
      vout2_ramp[i]=(data2*Vin)/1023.0;
      i++;  

      
      //10% duty cycle    -->0.5V
      analogWrite(5, 25);

      delay(delay_time);
      data1 = analogRead(A0);
      data2= analogRead(A1); 
      vout1_ramp[i] = (data1*Vin)/1023.0;   
      vout2_ramp[i]=(data2*Vin)/1023.0;
      i++;  

      //10% duty cycle    -->0.5V
      analogWrite(5, 25);

      delay(delay_time);
      data1 = analogRead(A0);
      data2= analogRead(A1); 
      vout1_ramp[i] = (data1*Vin)/1023.0;   
      vout2_ramp[i]=(data2*Vin)/1023.0;
      i++;  

      
       Serial.println("V1           V2          I");
       if(ch==0)
       {
          for(int a=0;a<3;a++)
          {
            float curr = ((vout2_ramp[a]-vout1_ramp[a])/(Rref1*1E3)) + c_t*((vout2_ramp[a+1]-vout2_ramp[a])-(vout1_ramp[a+1]-vout1_ramp[a]));
            curr = curr*1E6;
            Serial.print(vout1_ramp[a]);
            Serial.print("    ");
            Serial.print(vout2_ramp[a]); 
            Serial.print("    ");
            Serial.println(curr,4);
            Rsen_arr[number]= (1E3*vout1_ramp[a])/curr;
            //Serial.print(Rsen_arr[number]);
            sum+=Rsen_arr[number];
            number++;
            
          }
          Rsen1= sum/number; 
          Serial.print("S1 = ");
          Serial.println(Rsen1);
         
          Serial.println("----------------------------");
          
          digitalWrite(11,LOW);
          digitalWrite(10,HIGH);
          digitalWrite(6,LOW);      //LSB for MC
          pinset(ref2_pins);
          delay(switch_time);
       }
       if(ch==1)
       {
          for(int a=0;a<3;a++)
          {
            float curr = ((vout2_ramp[a]-vout1_ramp[a])/(Rref2*1E3)) + c_t*((vout2_ramp[a+1]-vout2_ramp[a])-(vout1_ramp[a+1]-vout1_ramp[a]));
            curr = curr*1E6;
            Serial.print(vout1_ramp[a]);
            Serial.print("    ");
            Serial.print(vout2_ramp[a]); 
            Serial.print("    ");
            Serial.println(curr,4);
            Rsen_arr[number]= (1E3*vout1_ramp[a])/curr;
            //Serial.print(Rsen_arr[number]);
            sum+=Rsen_arr[number];
            number++;
            
          }
          Rsen2= sum/number; 
          Serial.print("S2 = ");
          Serial.println(Rsen2);
         
          Serial.println("----------------------------");
          
          digitalWrite(11,LOW);
          digitalWrite(10,LOW);
          digitalWrite(6,HIGH);      //LSB for MC
          pinset(ref3_pins);
          delay(switch_time);
      
       }
       if(ch==2)
       {
          for(int a=0;a<3;a++)
          {
            float curr = ((vout2_ramp[a]-vout1_ramp[a])/(Rref3*1E3)) + c_t*((vout2_ramp[a+1]-vout2_ramp[a])-(vout1_ramp[a+1]-vout1_ramp[a]));
            curr = curr*1E6;
            Serial.print(vout1_ramp[a]);
            Serial.print("    ");
            Serial.print(vout2_ramp[a]); 
            Serial.print("    ");
            Serial.println(curr,4);
            Rsen_arr[number]= (1E3*vout1_ramp[a])/curr;
            //Serial.print(Rsen_arr[number]);
            sum+=Rsen_arr[number];
            number++;
            
          }
          Rsen3= sum/number; 
          Serial.print("S3 = ");
          Serial.println(Rsen3);
         
          Serial.println("----------------------------");
          
          digitalWrite(11,LOW);
          digitalWrite(10,LOW);
          digitalWrite(6,LOW);      //LSB for MC
          pinset(ref4_pins);
          delay(switch_time);
      
       }
       if(ch==3)
       {
        
        for(int a=0;a<3;a++)
        {
          float curr = ((vout2_ramp[a]-vout1_ramp[a])/(Rref4*1E3)) + c_t*((vout2_ramp[a+1]-vout2_ramp[a])-(vout1_ramp[a+1]-vout1_ramp[a]));
          curr = curr*1E6;
          Serial.print(vout1_ramp[a]);
          Serial.print("    ");
          Serial.print(vout2_ramp[a]); 
          Serial.print("    ");
          Serial.println(curr,4);
          Rsen_arr[number]= (1E3*vout1_ramp[a])/curr;
          //Serial.print(Rsen_arr[number]);
          sum+=Rsen_arr[number];
          number++;
        }
        Rctrl= sum/number; 
        Serial.print("Scontrol = ");
        Serial.println(Rctrl);
       
        Serial.println("----------------------------");
     
        
        //do reset
        Serial.println("RESET DONE");
        delay(1000);
        resetFunc();
        Serial.println("Never should be printed");
        delay(1000);
       }
    }
   } 
}

float reference_calculation(int ch)
{
  float vout2=0;      
  float vol_array[7]={};
  int count=0;
  int j=0;
 
  for(int i=0; i<7; i++)
  {
    d[i]=1;
    pinset(d);
    for(int k=0;k<7;k++)
    {
      Serial.print(d[k]);
    }
    Serial.print(" R=");
    float temp_res= res_calc(d);
    Serial.println(temp_res);
    delay(500);
    
    data2 = analogRead(A1);
    
    vout2 = (data2*Vin)/1023.0;    
    Serial.print("VOUT2 ");
    Serial.println(vout2);
    
      if(vout2>4.4)
      {
        d[i]=0;
        pinset(d);
      }
      else
      {
        vol_array[j]=vout2;
        store_array(d,count);
        count++;
        j++;
      }
  }
  //Serial.println(" SAR done");

  //find best Refernce corresponding to highest voltage

  float maxm = vol_array[0];
  int index =0;
  for(int j=1;j<count;j++)
   {
    if (vol_array[j]>maxm )
    {
      maxm = vol_array[j];
      index = j;
    }
    
   }
   Serial.println("Algo done");
   //temp2=maxm;
   for(int a=0;a<7;a++)
   {
    pin_select[a]=store_mat[index][a];
   }

   if(ch==0)
   {
     for(int a=0;a<7;a++)
     {
      ref1_pins[a]=pin_select[a];
     }
   }
   if(ch==1)
   {
    for(int a=0;a<7;a++)
     {
      ref2_pins[a]=pin_select[a];
     }
   }
   if(ch==2)
   {
    for(int a=0;a<7;a++)
     {
      ref3_pins[a]=pin_select[a];
     }
   }
   if(ch==3)
   {
    for(int a=0;a<7;a++)
     {
      ref4_pins[a]=pin_select[a];
     }
   }
   Rref = res_calc(pin_select);
  
   memset(d,0,sizeof(d));
  
//   Serial.println("D array after loop");
//   for(int k=0;k<5;k++)
//    {
//      Serial.print(d[k]);
//    }
   memset(pin_select,0,sizeof(pin_select));
   memset(store_mat,0,sizeof(store_mat));
   memset(vol_array,0,sizeof(vol_array));

   
   return(Rref);
  
}

void store_array(int d[],int c)
{
  for(int i=0;i<7;i++)
  {
    store_mat[c][i]=d[i];
  }
}


void pinset(int d[])
{
    digitalWrite(12, d[6]);    //LSB -->DO:B0-->18uc
    digitalWrite(13, d[5]);     //D1:B1-->19uc
    digitalWrite(2, d[4]);      //D2:B2-->4uc
    digitalWrite(3, d[3]);      //D3:B3-->5uc
    digitalWrite(4,d[2]);       //D4:B4-->6uc
    digitalWrite(7,d[1]);       //D5:B5-->13uc
    digitalWrite(8,d[0]);       //D6:B6-->14uc
  
}

float res_calc(int pin_select[])
{
  float temp=0;
  for(int k=0;k<7;k++)
  {
    if(pin_select[k]==1)
    {
      temp+= Rref_arr[k];
    }
  } 
  temp=temp+51.0;
  return(temp);
}
