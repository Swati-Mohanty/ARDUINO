//ramp up circuit code
//with 7 reference resistors
//40 samples
//3 sensors
//with  serial input
//displays current
//average resistance display when 0.48 < vout1 < 0.52
//with scalling factor
//no correction factor
//checked with mobile


#include <TimerOne.h>
#define NOP __asm__ __volatile__("nop\n\t");

float data1=0,data2=0;
float Vin= 5;
float vout1=0;

float Rref_arr[6] = {12000.0, 5621.0, 1493.00, 550.0, 199.7,100};

float Rref=0;
float Rref1=0;  
float Rref2=0; 
float Rref3=0;

int d[]={0,0,0,0,0,0};// pin_select[6]={};
int store_mat[6][6]={};
int ref1_pins[6] = {};
int ref2_pins[6] = {};
int ref3_pins[6] = {};

float vout1_ramp[3][40]={};
float vout2_ramp[3][40]={};

bool flag = true;
int check_bit=0,counter=0,ch=0;
int i=0;
int no_of_samples = 40;
long int init_time = 27500;
float c_t = 100E-9/27E-3;

void setup() 
{
 //sensor pins
  pinMode(5,OUTPUT);   //LSB
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);   //MSB
  //switch pins
  pinMode(12,OUTPUT);        //LSB  D0    pin 18 on uc--->100K
  pinMode(13,OUTPUT);        //D1         pin 19 on uc--->200K
  pinMode(2,OUTPUT);         //D2         pin 4 on uc---->550K
  pinMode(3,OUTPUT);         //D3         pin 5 on uc---->1.6M
  pinMode(4,OUTPUT);         //D4         pin 6 on uc---->5M
  pinMode(A4,OUTPUT);  //MSB D5          pin 27 on uc--->12M
  //SnH pins
  pinMode(8,OUTPUT);    //L0
  pinMode(10,OUTPUT);    //M0--->ADC-->vout2
  pinMode(11,OUTPUT);    //M1--->ADC-->vout3
  //clock pins
  pinMode(9,OUTPUT);    //CLK
  //cap switch
  pinMode(A3,OUTPUT);

  digitalWrite(A3,HIGH);   //switch is open by default

  Serial.begin(9600);
 

}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop()
{
  float Rsen1= 0;
  float Rsen2= 0;
  float Rsen3= 0;
  if(Serial.available())
  {
    while(flag==true)
    {
      digitalWrite(9,LOW);    //CLK
    
      digitalWrite(8,LOW);   //sample
      digitalWrite(10,LOW);   //M0 close
      digitalWrite(11,HIGH);   //M1 open
      delay(500);
    
      data1 = analogRead(A0);
      
      vout1 = (data1*Vin)/1023.0;
      Serial.println("Initializing... ");
      Serial.println("vout2=");   //nomenclature as per new ckt
      Serial.println(vout1);
      
      //First Sensor selection
      digitalWrite(7,LOW);
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);      //LSB for MC

      ch=0;
      Rref1 = reference_calculation(ch);
      Serial.print("Reference1 :");
      Serial.println(Rref1);

      //Second Sensor selection
      digitalWrite(7,LOW);
      digitalWrite(6,LOW);
      digitalWrite(5,HIGH);      //LSB for MC

      ch=1;
      Rref2 = reference_calculation(ch);
      Serial.print("Reference2 :");
      Serial.println(Rref2);

      //Third Sensor selection
      digitalWrite(7,LOW);
      digitalWrite(6,HIGH);
      digitalWrite(5,LOW);      //LSB for MC

      ch=2;
      Rref3 = reference_calculation(ch);
      Serial.print("Reference3 :");
      Serial.println(Rref3);
      
      ch=0;  
      digitalWrite(7,LOW);
      digitalWrite(6,LOW);
      digitalWrite(5,LOW);      //LSB for MC
      pinset(ref1_pins);
      delay(500);
      
      Timer1.initialize(init_time);
      Timer1.attachInterrupt(timer_isr);
      flag = false;      
    }
    
    if(check_bit==1)
    {
      Timer1.stop();
      
      for(int b=0;b<3;b++)
      {
        float Rsen_arr[20]= {};
        int number=0;
        double sum=0;
        Serial.println("V1           V2          I");
        if(b==0)
        {
          for(int a=0;a<39;a++)
          {
            if((vout1_ramp[b][a]>0.3)&&(vout1_ramp[b][a]<0.6))
            {
              float curr = ((vout2_ramp[b][a]-vout1_ramp[b][a])/(Rref1*1E3)) + c_t*((vout2_ramp[b][a+1]-vout2_ramp[b][a])-(vout1_ramp[b][a+1]-vout1_ramp[b][a]));
              curr = curr*1E6;
              Serial.print(vout1_ramp[b][a]);
              Serial.print("    ");
              Serial.print(vout2_ramp[b][a]); 
              Serial.print("    ");
              Serial.println(curr,4);
              Rsen_arr[number]= (1E3*vout1_ramp[b][a])/curr;
              //Serial.print(Rsen_arr[number]);
              sum+=Rsen_arr[number];
              number++;
            }
            
          }
          Rsen1= sum/number; 
          Serial.print("S1 = ");
          Serial.println(Rsen1);
         
          Serial.println("----------------------------");
        }
        else if(b==1)
        {
          for(int a=0;a<39;a++)
          {
            if((vout1_ramp[b][a]>0.3)&&(vout1_ramp[b][a]<0.6))
            {
              float curr = ((vout2_ramp[b][a]-vout1_ramp[b][a])/(Rref2*1E3)) + c_t*((vout2_ramp[b][a+1]-vout2_ramp[b][a])-(vout1_ramp[b][a+1]-vout1_ramp[b][a]));
              curr = curr*1E6;
              Serial.print(vout1_ramp[b][a]);
              Serial.print(" ");
              Serial.print(vout2_ramp[b][a]); 
              Serial.print(" ");
              Serial.println(curr,4);
              Rsen_arr[number]= (1E3*vout1_ramp[b][a])/curr;
              //Serial.print(Rsen_arr[number]);
              sum+=Rsen_arr[number];
              number++;
            }
            
          }
          Rsen2= sum/number; 
          Serial.print("S2 = ");
          Serial.println(Rsen2);
         
          Serial.println("-----------------------------");
         
           
        }
        else if(b==2)
        {
          for(int a=0;a<39;a++)
          {
           if((vout1_ramp[b][a]>0.3)&&(vout1_ramp[b][a]<0.6))
            {
              float curr = ((vout2_ramp[b][a]-vout1_ramp[b][a])/(Rref3*1E3)) + c_t*((vout2_ramp[b][a+1]-vout2_ramp[b][a])-(vout1_ramp[b][a+1]-vout1_ramp[b][a]));
              curr = curr*1E6;
              Serial.print(vout1_ramp[b][a]);
              Serial.print(" ");
              Serial.print(vout2_ramp[b][a]); 
              Serial.print(" ");
              Serial.println(curr,4);
              Rsen_arr[number]= (1E3*vout1_ramp[b][a])/curr;
              //Serial.print(Rsen_arr[number]);
              sum+=Rsen_arr[number];
              number++;
            }
            
          }
          Rsen3= sum/number; 
          Serial.print("S3 = ");
          Serial.println(Rsen3);
         
          Serial.println("----------------------------");
           
        }
        else
        {
          Serial.println("Oops..something went wrong!!");
        }

      }

      Timer1.detachInterrupt();
      check_bit=0;
      Serial.println("RESET DONE");
      delay(1000);
      resetFunc();
      Serial.println("Never should be printed");
    }
    
    
  }
}

float reference_calculation(int ch)
{
  float vout2=0;      
  float vol_array[6]={};
  int count=0;
  int j=0;
  digitalWrite(8,LOW);   //sample
  digitalWrite(10,HIGH);   //M0 open
  digitalWrite(11,LOW);   //M1 close
  for(int i=0; i<6; i++)
  {
    d[i]=1;
    pinset(d);
    delay(500);
    data2 = analogRead(A0);
    
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
 
//   for(int a=0;a<6;a++)
//   {
//    pin_select[a]=store_mat[index][a];
//   }

   if(ch==0)
   {
     for(int a=0;a<6;a++)
     {
      ref1_pins[a]=store_mat[index][a];
      Rref = res_calc(ref1_pins);
     }
   }
   if(ch==1)
   {
    for(int a=0;a<6;a++)
     {
      ref2_pins[a]=store_mat[index][a];
      Rref = res_calc(ref2_pins);
     }
   }
   if(ch==2)
   {
    for(int a=0;a<6;a++)
     {
      ref3_pins[a]=store_mat[index][a];
      Rref = res_calc(ref3_pins);
     }
   }
//   Rref = res_calc(pin_select);
  
   memset(d,0,sizeof(d));
   //memset(pin_select,0,sizeof(pin_select));
   memset(store_mat,0,sizeof(store_mat));
   memset(vol_array,0,sizeof(vol_array));

   
   return(Rref);
  
}

void store_array(int d[],int c)
{
  for(int i=0;i<6;i++)
  {
    store_mat[c][i]=d[i];
  }
}


void pinset(int d[])
{
    digitalWrite(12, d[5]);    //LSB -->DO
    digitalWrite(13, d[4]);     //D1
    digitalWrite(2, d[3]);      //D2
    digitalWrite(3, d[2]);      //D3
    digitalWrite(4,d[1]);       //D4
    digitalWrite(A4,d[0]);      //D5
  
}

float res_calc(int pin_select[])
{
  float temp=0;
  for(int k=0;k<6;k++)
  {
    if(pin_select[k]==1)
    {
      temp+= Rref_arr[k];
    }
  }
  temp=temp+51.0;
  return(temp);
}


void timer_isr()
{
  
  if(counter < no_of_samples)    //40 samples
  {
    digitalWrite(9,HIGH);
    //140us
    digitalWrite(8,LOW);   //sample
    digitalWrite(10,HIGH);   //M0 open
    digitalWrite(11,HIGH);   //M1 open
    digitalWrite(8,LOW);   //sample
    digitalWrite(10,HIGH);   //M0 open
    digitalWrite(11,HIGH);   //M1 open
   digitalWrite(8,LOW);   //sample
    digitalWrite(10,HIGH);   //M0 open
    digitalWrite(11,HIGH);   //M1 open
    digitalWrite(8,LOW);   //sample
    digitalWrite(10,HIGH);   //M0 open
    digitalWrite(11,HIGH);   //M1 open
    digitalWrite(8,LOW);   //sample
    digitalWrite(10,HIGH);   //M0 open
    digitalWrite(11,HIGH);   //M1 open
    digitalWrite(8,LOW);   //sample
    digitalWrite(10,HIGH);   //M0 open
    digitalWrite(11,HIGH);   //M1 open
    digitalWrite(8,LOW);   //sample
    digitalWrite(10,HIGH);   //M0 open
    digitalWrite(11,HIGH);   //M1 open
    digitalWrite(8,LOW);   //sample
    digitalWrite(10,HIGH);   //M0 open
    digitalWrite(11,HIGH);   //M1 open
    digitalWrite(8,LOW);   //sample
    digitalWrite(10,HIGH);   //M0 open
    digitalWrite(11,HIGH);   //M1 open
    digitalWrite(8,LOW);   //sample
    digitalWrite(10,HIGH);   //M0 open
    digitalWrite(11,HIGH);   //M1 open
    digitalWrite(8,LOW);   //sample
    digitalWrite(10,HIGH);   //M0 open
    digitalWrite(11,HIGH);   //M1 open
    
    //NOP;
    digitalWrite(8,HIGH);    //hold
    //for vout2
    digitalWrite(10,LOW);    //M0 close
    data1 = analogRead(A0);
    digitalWrite(10,HIGH);    //M0 open

    //for vout3
    digitalWrite(11,LOW);    //M1 close
    data2= analogRead(A0); 
    digitalWrite(11,HIGH);    //M1 open
    vout1_ramp[ch][i] = (data1*Vin)/1023.0;   
    vout2_ramp[ch][i]=(data2*Vin)/1023.0;   
    counter++; 
    i++;   
    
   }
    if(counter==no_of_samples)
    {        
      digitalWrite(9,LOW);
      
      counter =0;
      i=0;
      if(ch==0)     //second sensor and pin selsction
      {
        pinset(ref2_pins);
        digitalWrite(6,LOW);
        digitalWrite(5,HIGH);
        digitalWrite(6,LOW);
        digitalWrite(5,HIGH);
        
      }
      else if(ch==1)    //third sensor and pin selection
      {
        pinset(ref3_pins);
        digitalWrite(6,HIGH);
        digitalWrite(5,LOW);
        digitalWrite(6,HIGH);
        digitalWrite(5,LOW);
        
      }
      else if(ch==2)      //go to main loop
      {
        check_bit=1;
      }
      ch++;
    }
  
  }
  
  
