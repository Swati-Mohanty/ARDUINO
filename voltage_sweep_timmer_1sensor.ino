//30 samples
//3 sensors
//with serial input
//with scalling factor


#include <TimerOne.h>
#include <PinChangeInterrupt.h>
#define NOP __asm__ __volatile__("nop\n\t");

float data1=0,data2=0;
float Vin= 5;
float vout1=0;
const byte rise_Pin = 9;

float Rsen1= 0;
float Rsen2= 0;
float Rsen3= 0;
float Rref_arr[5] = {12000.0, 5621.0, 1493.00, 550.0, 199.7};

float Rref=0,temp1=0,temp2=0;
float Rref1=0;  
float Rref2=0; 
float Rref3=0;

int d[]={0,0,0,0,0}, pin_select[5]={};
int store_mat[5][5]={};
int ref1_pins[5] = {};
int ref2_pins[5] = {};
int ref3_pins[5] = {};

float vout1_ramp[3][30]={};
float vout2_ramp[3][30]={};

bool flag = true;
int check_bit=0,counter=0,ch=0;
int i=0;
const int a=2.25;
float T=1E-6;

void setup() 
{
 //sensor pins
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);   
  //switch pins
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);  //MSB
  pinMode(12,OUTPUT); //LSB
  pinMode(13,OUTPUT);
  //SnH pins
  pinMode(7,OUTPUT);    //L0--->ADC1-->A0
  pinMode(8,OUTPUT);    //L1--->ADC2-->A1
  //clock pins
  pinMode(9,OUTPUT);    //CLK
  pinMode(5,OUTPUT);    //CLKB
  
  pinMode(rise_Pin,LOW);
 
  //analogReference(EXTERNAL);
  Serial.begin(9600);
 

}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop()
{
  if(Serial.available())
  {
    while(flag==true)
    {
      digitalWrite(9,LOW);    //CLK
      digitalWrite(5,LOW);    //CLKB
    
      digitalWrite(7,LOW);   //sample the value for adc1
      digitalWrite(8,LOW);   //sample the value for adc2
      delay(500);
    
      data1 = analogRead(A0);
      
      vout1 = (data1*Vin)/(1023.0*3.667);
      Serial.println("Initializing... ");
      Serial.print("vout1 ");
      Serial.println(vout1);
      
      //First Sensor selection
      digitalWrite(11,LOW);
      digitalWrite(10,LOW);
      digitalWrite(6,LOW);      //LSB for MC

      ch=0;
      Rref1 = reference_calculation(ch);
      Serial.print("Reference1 :");
      Serial.println(Rref1);

      //Second Sensor selection
      digitalWrite(11,LOW);
      digitalWrite(10,LOW);
      digitalWrite(6,HIGH);      //LSB for MC

      ch=1;
      Rref2 = reference_calculation(ch);
      Serial.print("Reference2 :");
      Serial.println(Rref2);

      //Third Sensor selection
      digitalWrite(11,LOW);
      digitalWrite(10,HIGH);
      digitalWrite(6,LOW);      //LSB for MC

      ch=2;
      Rref3 = reference_calculation(ch);
      Serial.print("Reference3 :");
      Serial.println(Rref3);
      
      ch=0;  
      pinset(ref1_pins);
      delay(1000);
      //Serial.println(" Timer started");
      
      Timer1.initialize(33000);    //10Hz 54ms per sample
      Timer1.attachInterrupt(timer_isr);
      flag = false;      
    }
    
    if(check_bit==1)
    {
      float cor[3] = {a*T*Rref1, a*T*Rref2, a*T*Rref3};
      
      //Timer1.detachInterrupt();
      delay(1000);
      //Serial.println("Timer stopped");
      Serial.println("A0");
      for(int i=0;i<30;i++)
      {
        Serial.println(vout1_ramp[0][i]);
      }
      for(int b=0;b<3;b++)
      {
        float Rsen_arr[30]= {};
        int number=0;
        double sum=0;
        for(int a=0;a<30;a++)
        {
          if((vout1_ramp[b][a]>0.4)&&(vout1_ramp[b][a]<0.6))
          {
            Rsen_arr[number]= Rref1*((vout1_ramp[b][a]-cor[b])/(vout2_ramp[b][a]-vout1_ramp[b][a]));
            sum+=Rsen_arr[number];
            number++;
          }
        }
        if(b==0)
        {
           Rsen1= sum/number; 
           Serial.print("S1= ");
           Serial.println(Rsen1);
        }
        else if(b==1)
        {
         Rsen2= sum/number; 
         Serial.print("S2= ");
         Serial.println(Rsen2);
        }
        else if(b==2)
        {
          Rsen3= sum/number; 
         Serial.print("S3= ");
         Serial.println(Rsen3);
        }
        else
        {
          Serial.println("Oops..something went wrong!!");
        }
      }
      
      check_bit=0;
      Serial.println(" RESET DONE");
      delay(1000);
      resetFunc();
      Serial.println(" Never should be printed");
    }
    
    
  }
}

float reference_calculation(int ch)
{
  float vout2=0;      
  float vol_array[5]={};
  int count=0;
  int j=0;
 
  for(int i=0; i<5; i++)
  {
    d[i]=1;
    pinset(d);
//    for(int k=0;k<5;k++)
//    {
//      Serial.print(d[k]);
//    }
//    Serial.print(" R=");
//    float temp_res= res_calc(d);
//    Serial.println(temp_res);
    delay(1000);
    digitalWrite(8,LOW);   //sample the value for adc2
    data2 = analogRead(A1);
    
    vout2 = (data2*Vin)/1023.0;    
//    Serial.print("VOUT2 ");
//    Serial.println(vout2);
    
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
   temp2=maxm;
   for(int a=0;a<5;a++)
   {
    pin_select[a]=store_mat[index][a];
   }

   if(ch==0)
   {
     for(int a=0;a<5;a++)
     {
      ref1_pins[a]=pin_select[a];
     }
   }
   if(ch==1)
   {
    for(int a=0;a<5;a++)
     {
      ref2_pins[a]=pin_select[a];
     }
   }
   if(ch==2)
   {
    for(int a=0;a<5;a++)
     {
      ref3_pins[a]=pin_select[a];
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
  for(int i=0;i<5;i++)
  {
    store_mat[c][i]=d[i];
  }
}


void pinset(int d[])
{
    digitalWrite(12, d[4]);    //LSB -->DO
    digitalWrite(13, d[3]);     //D1
    digitalWrite(2, d[2]);      //D2
    digitalWrite(3, d[1]);      //D3
    digitalWrite(4,d[0]);       //D4
  
}

float res_calc(int pin_select[])
{
  float temp=0;
  for(int k=0;k<5;k++)
  {
    if(pin_select[k]==1)
    {
      temp+= Rref_arr[k];
    }
  }
  temp=temp+100.0;
  return(temp);
}


void timer_isr()
{
  
  if(counter<30)
  {
    digitalWrite(9,HIGH);
    digitalWrite(5,HIGH);
    //140us
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    //NOP;
    digitalWrite(7,HIGH);    //hold
    digitalWrite(8,HIGH);    //hold
    data1 = analogRead(A0);
    data2= analogRead(A1); 
    vout1_ramp[ch][i] = (data1*Vin)/(1023.0*3.667);   
    vout2_ramp[ch][i]=(data2*Vin)/1023.0;   
    counter++; 
    i++;   
    
   }
    if(counter==30)
    {        
      digitalWrite(9,LOW);
      digitalWrite(5,LOW);
      
      //check_bit=1;
      counter =0;
      i=0;
      if(ch==0)     //second sensor and pin selsction
      {
        Serial.println(" low1");
        pinset(ref2_pins);
        digitalWrite(10,LOW);
        digitalWrite(6,HIGH);
        
      }
      else if(ch==1)    //third sensor and pin selection
      {
        Serial.println(" low2");
        pinset(ref3_pins);
        digitalWrite(10,HIGH);
        digitalWrite(6,LOW);
        
      }
      else if(ch==2)      //go to main loop
      {
        Serial.println(" low3");
        check_bit=1;
      }
      ch++;
    }
  
  }
  
  
