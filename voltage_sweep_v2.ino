#include <TimerOne.h>
#define NOP __asm__ __volatile__("nop\n\t");

float data1=0,data2=0;
float Vin= 5;
float vout1=0;
float Rsen1_arr[3]= {};
float Rsen2_arr[3]= {};
float Rsen3_arr[3]= {};
//float Rref_arr[5] = {18000.0,1500.0,820.00,100.0,51.00};
float Rref_arr[5] = {51.0,100.0,820.00,1600.0,18000.00};

float Rref=0;
float Rref1=0;  
float Rref2=0; 
float Rref3=0;

int i=0,d[]={1,0,0,0,0}, pin_select[5]={};
int store_mat[5][5]={};
int ref1_pins[5] = {};
int ref2_pins[5] = {};
int ref3_pins[5] = {};

bool flag = true;
int check_bit=0,counter=0,ch=0;
float tem1;

void setup() 
{
 //sensor pins
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);   
  //switch pins
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);  //LSB
  pinMode(12,OUTPUT); //MSB
  pinMode(13,OUTPUT);
  //SnH pins
  pinMode(7,OUTPUT);    //L0--->ADC1-->A0
  pinMode(8,OUTPUT);    //L1--->ADC2-->A1
  //clock pins
  pinMode(9,OUTPUT);    //CLK
  pinMode(5,OUTPUT);    //CLKB
  
  
  //analogReference(EXTERNAL);
  Serial.begin(9600);
 // Timer1.initialize(300);

}

void loop()
{
 if(Serial.available())
 {
    if(flag==true)
    {
      digitalWrite(9,LOW);    //CLK
      digitalWrite(5,LOW);    //CLKB
    
      digitalWrite(7,LOW);   //sample the value for adc1
      digitalWrite(8,LOW);
        delay(200);
        pinset(d);
        for(int a=0;a<5;a++)
        {
          Serial.print(d[a]);
        }
      data1 = analogRead(A0);
      delay(100);
      vout1 = (data1*Vin)/1023.0;
      Serial.print("VOUT1 ");
      Serial.println(vout1);
     
      
      //First Sensor selection
      digitalWrite(11,LOW);
      digitalWrite(10,LOW);
      digitalWrite(6,LOW);      //LSB for MC

      ch=0;
      Rref1 = reference_calculation(ch);
      Serial.print("Reference1 :");
      Serial.println(Rref1);
      pinset(ref1_pins);
      for(int b=0;b<5;b++)
      {
        Serial.print(ref1_pins[b]);
      }
      float vout = tem1;
      Serial.print("VOUT2 ");
      Serial.println(vout);
     
      float tem=vout-vout1;
      float Rsen =Rref1*(vout1/tem);
      Serial.println(Rsen);

      //Second Sensor selection  //done?
      digitalWrite(11,LOW);
      digitalWrite(10,LOW);
      digitalWrite(6,HIGH);      //LSB for MC

      ch=1;
      //Rref2 = reference_calculation(ch);
      Serial.print("Reference2 :");
      Serial.println(Rref2);

      //Third Sensor selection
      digitalWrite(11,LOW);
      digitalWrite(10,HIGH);
      digitalWrite(6,LOW);      //LSB for MC

      ch=2;
      //Rref3 = reference_calculation(ch);
      Serial.print("Reference3 :");
      Serial.println(Rref3);
      
      flag=false;
 }
    
 }
  
   
 /* if(flag==true)
  {
     Timer1.initialize(500);    //5mili secs
     Timer1.attachInterrupt(timer_isr);
     flag = false; 
  }
  if(check_bit==1)
  {
    Timer1.stop();
    Serial.println("A0");
    for(int i=0;i<10;i++)
    Serial.println(vout1[i]);
    Serial.println("A1");
    for(int i=0;i<10;i++)
    Serial.println(vout2[i]);
    check_bit=0;
    Timer1.restart();
  }
 */

}

float reference_calculation(int ch)
{
  float vout2=0;      
  float vol_array[5]={};
  int count=0;
  int j=0;
  pinset(d);     //MSB high,  Rref1 used
  
  for(int i=0; i<5; i++)
  {
    //digitalWrite(7,LOW);
    digitalWrite(8,LOW);   //sample the value for adc2
    delay(2000);
    for(int k=0;k<5;k++)
    {
      Serial.print(d[k]);
    }
    //Serial.print(" R=");
    //float temp_res= res_calc(d);
    //Serial.println(temp_res);
    delay(10);
    data2 = analogRead(A1);
    vout2 = (data2*Vin)/1023.0;   
    Serial.print("VOUT2 ");
    Serial.println(vout2);
    if((i==4)&&(vout2<4.7))   //when i=4 this executes 
    {
      vol_array[j]=vout2;
      store_array(d,count); 
      count++;
      j++;
    
    }
    else        //for i=3,2,1,0 this executes
    {
      if(vout2>4.7)
      {
        d[i]=0;
        d[i+1]=1;
        pinset(d);
      }
      else
      {
        vol_array[j]=vout2;
        store_array(d,count);
        count++;
        j++;
        d[i+1]=1;
        pinset(d);
      }
    }
  }

  Serial.println("SAR loop done"); 

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
   tem1=maxm;

  Serial.println("max voltage calculated"); 

   memset(d,0,sizeof(d));
   d[0]=1;
   pinset(d);
   Serial.println("D array after loop");  
   for(int k=0;k<5;k++)
    {
      Serial.print(d[k]);
    }
   for(int a=0;a<5;a++)
   {
    pin_select[a]=store_mat[index][a];
   }

   if(ch==0)
   {
    //memcpy(ref1_pins, pin_select, 5);
      for(int a=0;a<5;a++)
     {
      ref1_pins[a]=store_mat[index][a];
     }
   }
   if(ch==1)
   {
    memcpy(ref2_pins, pin_select, 5);   
   }
   if(ch==2)
   {
    memcpy(ref3_pins, pin_select, 5);
   }

    Serial.println("pins stored"); 
   
   Rref = res_calc(ref1_pins);
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
    digitalWrite(12, d[0]);    //LSB -->DO
    digitalWrite(13, d[1]);     //D1
    digitalWrite(2, d[2]);      //D2
    digitalWrite(3, d[3]);      //D3
    digitalWrite(4,d[4]);       //D4
  
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
  return(temp);
}


void timer_isr()
{
  int i=0;
  if(counter<10)
  {
    digitalWrite(9,HIGH);
    digitalWrite(5,HIGH);
   
    digitalWrite(7,LOW);   //sample the value for adc1
    digitalWrite(8,LOW);   //sample the value for adc2
    NOP;
    digitalWrite(7,HIGH);    //hold
    digitalWrite(8,HIGH);    //hold
   // data1 = analogRead(A0);
   //data2= analogRead(A1); 
    //vout1[i] = (data1*Vin)/1023.0;   //constant voltage for refernce calculatio
     // vout2[i]=(data2*Vin)/1023.0;   
      counter++; 
      //i++; 

                                                            //read adc2
    }
    if(counter==10)
    {
      digitalWrite(9,LOW);
      digitalWrite(5,LOW);
      check_bit=1;
      counter =0;
      //suitable Rref calculation, Rsen calculation and storing in Rsen_arr
    }
  
  }
  
