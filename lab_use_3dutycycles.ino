//sar reference voltage 0.5V
//with serial input
//duty cycle 20% at starting
//changing 3 times after 2sec
//11%,10%,9%
//software rest enabled
//working with resistors/biochips
//new board with modified circuitry

#define NOP __asm__ __volatile__("nop\n\t");

float data1=0,data2=0;
float Vin= 5;
float vout1=0;

float Rsen1= 0;
float Rsen2= 0;
float Rsen3= 0;
float Rref_arr[5] = {12000.0, 5751.0, 1493.00, 548.0, 219};

float Rref=0,temp1=0,temp2=0;
float Rref1=0;  
float Rref2=0; 
float Rref3=0;

int d[]={0,0,0,0,0}, pin_select[5]={};
int store_mat[5][5]={};
int ref1_pins[5] = {};
int ref2_pins[5] = {};
int ref3_pins[5] = {};

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
       
        digitalWrite(7,LOW);   //sample the value for adc1
        digitalWrite(8,LOW);   //sample the value for adc2
        delay(500);
      
        data1 = analogRead(A0);
        
        vout1 = (data1*Vin)/1023.0;
        Serial.println("Initializing... ");
        Serial.println("VOUT1 ");
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
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(6,LOW);      //LSB for MC
        pinset(ref1_pins);
        delay(1000);
        flag = false;      
     }

   for(int ch=0;ch<3;ch++)
   {
      int i=0;
      
      //11% duty cycle    -->0.55V
      analogWrite(5, 28);
      
      delay(2000);
      data1 = analogRead(A0);
      data2= analogRead(A1); 
      vout1_ramp[i] = (data1*Vin)/1023.0;   
      vout2_ramp[i]=(data2*Vin)/1023.0;
      i++;  
    
      //10% duty cycle    -->0.5V
      analogWrite(5, 25);

      delay(2000);
      data1 = analogRead(A0);
      data2= analogRead(A1); 
      vout1_ramp[i] = (data1*Vin)/1023.0;   
      vout2_ramp[i]=(data2*Vin)/1023.0;
      i++;  

      //9% duty cycle    -->0.45V
      analogWrite(5, 22);
      
      delay(2000);
      data1 = analogRead(A0);
      data2= analogRead(A1); 
      vout1_ramp[i] = (data1*Vin)/1023.0;   
      vout2_ramp[i]=(data2*Vin)/1023.0;  
      i++;

      
       
       if(ch==0)
       {
          float Rsen_arr[5]={};
          float sum=0;
          for(int a=0;a<3;a++)
          {
            Serial.print("vout1 ");
            Serial.println(vout1_ramp[a]);
            Serial.print("vout2 ");
            Serial.println(vout2_ramp[a]);
            Rsen_arr[a]= Rref1*((vout1_ramp[a])/(vout2_ramp[a]-vout1_ramp[a]));
            Serial.println(Rsen_arr[a]);
            sum+=Rsen_arr[a];
          }
          Rsen1= sum/3.0;
          Serial.print("S1 = ");
          Serial.println(Rsen1);
          digitalWrite(11,LOW);
          digitalWrite(10,LOW);
          digitalWrite(6,HIGH);      //LSB for MC
          pinset(ref2_pins);
          delay(1000);
       }
       if(ch==1)
       {
          float Rsen_arr[5]={};
          float sum=0;
          for(int a=0;a<3;a++)
          {
            Serial.print("vout1 ");
            Serial.println(vout1_ramp[a]);
            Serial.print("vout2 ");
            Serial.println(vout2_ramp[a]);
            Rsen_arr[a]= Rref2*((vout1_ramp[a])/(vout2_ramp[a]-vout1_ramp[a]));
            Serial.println(Rsen_arr[a]);
            sum+=Rsen_arr[a];
          }
          Rsen2= sum/3.0;
          Serial.print("S2 = ");
          Serial.println(Rsen2);
          digitalWrite(11,LOW);
          digitalWrite(10,HIGH);
          digitalWrite(6,LOW);      //LSB for MC
          pinset(ref3_pins);
          delay(1000);
      
       }
       if(ch==2)
       {
        float Rsen_arr[5]={};
        float sum=0;
        for(int a=0;a<3;a++)
        {
          Serial.print("vout1 ");
          Serial.println(vout1_ramp[a]);
          Serial.print("vout2 ");
          Serial.println(vout2_ramp[a]);
          Rsen_arr[a]= Rref3*((vout1_ramp[a])/(vout2_ramp[a]-vout1_ramp[a]));
          Serial.println(Rsen_arr[a]);
          sum+=Rsen_arr[a];
        }
        Rsen3= sum/3.0;
        Serial.print("S3 = ");
        Serial.println(Rsen3);
        
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
    delay(2000);
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
  temp=temp+109.0;
  return(temp);
}
