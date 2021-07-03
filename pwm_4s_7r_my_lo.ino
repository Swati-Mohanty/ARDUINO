//sar with 7 switches
//with serial input
//displays resistance
//s5ng3e stage read5ng
//0.5V pwm
//my trial logic
//software rest enabled
//BOARD  SENSOR   MUX
//CH3    S1       011
//CH2    S2       010
//CH1    S3       001
//CH0    Scontrol 000


#define NOP __asm__ __volatile__("nop\n\t");

int delay_time ;//= 400;   
int s_delay = 200 ;

float data1=0,data2=0;
float Vin= 5;
float vout1=0;
float vmax =0;

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
int choice;


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
    delay_time = 30;
    execution();

   } 
}
void execution()
{
while(flag==true)
      {
      
        //data1 = analogRead(A0);
        
        //vout1 = (data1*Vin)/1023.0;
        Serial.println("Initializing... ");
        //Serial.println(vout1);
        
        //First Sensor selection
        digitalWrite(11,LOW);
        digitalWrite(10,HIGH);
        digitalWrite(6,HIGH);      //LSB for MC
        delay(delay_time);
      
        ch=0;
        
        data1 = analogRead(A0);
        vout1 = (data1*Vin)/1023.0;
        
        Rref1 = reference_calculation(ch);
        Serial.print("Reference1 :");
        Serial.println(Rref1);
        Rsen1 = ((vout1*Rref1)/(vmax-vout1));
        Serial.println("V1           V2         ");
        Serial.print(vout1);
        Serial.print("          ");
        Serial.println(vmax);
        Serial.print("S1 = ");
        Serial.println(Rsen1);
       
        Serial.println("----------------------------");
      
        //Second Sensor selection
        digitalWrite(11,LOW);
        digitalWrite(10,HIGH);
        digitalWrite(6,LOW);      //LSB for MC
        delay(delay_time);
        
        ch=1;
        data1 = analogRead(A0);
        vout1 = (data1*Vin)/1023.0;
        
        Rref2 = reference_calculation(ch);
        Serial.print("Reference2 :");
        Serial.println(Rref2);
        Rsen2 = ((vout1*Rref2)/(vmax-vout1));
        Serial.println("V1           V2         ");
        Serial.print(vout1);
        Serial.print("          ");
        Serial.println(vmax);
        Serial.print("S2 = ");
        Serial.println(Rsen2);
       
        Serial.println("----------------------------");
      
        //Third Sensor selection
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(6,HIGH);      //LSB for MC
        delay(delay_time);
        
        ch=2;
        data1 = analogRead(A0);
        vout1 = (data1*Vin)/1023.0;
        
        Rref3 = reference_calculation(ch);
        Serial.print("Reference3 :");
        Serial.println(Rref3);
        Rsen3 = ((vout1*Rref3)/(vmax-vout1));
        Serial.println("V1           V2         ");
        Serial.print(vout1);
        Serial.print("          ");
        Serial.println(vmax);
        Serial.print("S3 = ");
        Serial.println(Rsen3);
       
        Serial.println("----------------------------");

        //Control Sensor selection
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(6,LOW);      //LSB for MC
        delay(delay_time);
       
      
        ch=3;
        data1 = analogRead(A0);
        vout1 = (data1*Vin)/1023.0;
        
        Rref4 = reference_calculation(ch);
        Serial.print("Reference4 :");
        Serial.println(Rref4);
        Rctrl = ((vout1*Rref4)/(vmax-vout1));
        Serial.println("V1           V2         ");
        Serial.print(vout1);
        Serial.print("          ");
        Serial.println(vmax);
        Serial.print("Scontrol = ");
        Serial.println(Rctrl);
       
        Serial.println("----------------------------");
     
        
        //hardware reset
        analogWrite(5, 0);
        digitalWrite(11,HIGH);
        digitalWrite(10,HIGH);
        digitalWrite(6,HIGH); 
        //software reset
        Serial.println("RESET DONE");
        delay(1000);
        resetFunc();
        Serial.println("Never should be printed");
        delay(1000);
        
        
     }
}

 float reference_calculation(int ch)
{
 label: float vout2=0;      
  float vol_array[7]={};
  int count=0;
  int j=0;
 
  for(int i=0; i<7; i++)
  {
    d[i]=1;
    pinset(d);
//    for(int k=0;k<7;k++)
//    {
//      Serial.print(d[k]);
//    }
//    Serial.print(" R=");
//    float temp_res= res_calc(d);
//    Serial.println(temp_res);
    delay(s_delay);
    
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
Serial.println(maxm);
   if((maxm==0)&(s_delay<600))
   {
    s_delay = s_delay+100;
    //Serial.println("Second run");
    memset(d,0,sizeof(d));
   
   memset(store_mat,0,sizeof(store_mat));
   memset(vol_array,0,sizeof(vol_array));
    goto label;
    
   }

   
   Serial.println("Algo done");
   s_delay = 200;
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
     vmax=maxm;
   }
   if(ch==1)
   {
    for(int a=0;a<7;a++)
     {
      ref2_pins[a]=pin_select[a];
     }
     vmax=maxm;
   }
   if(ch==2)
   {
    for(int a=0;a<7;a++)
     {
      ref3_pins[a]=pin_select[a];
     }
     vmax=maxm;
   }
   if(ch==3)
   {
    for(int a=0;a<7;a++)
     {
      ref4_pins[a]=pin_select[a];
     }
     vmax=maxm;
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
