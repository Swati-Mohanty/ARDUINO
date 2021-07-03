#define NOP __asm__ __volatile__("nop\n\t");

int delay_time = 4;   //4ms
int switch_time = 2000;
float c_t = 0;  //100E-9/(4*1E-3);

float data1=0,data2=0;
float Vin= 5;
float vout1=0,vout2=0;

float Rsen1= 0;
float Rsen2= 0;
float Rsen3= 0;
float Rref_arr[7] = {12000.0, 5751.0, 1493.00,820.0, 548.0, 200.0,100.0};

float Rref=0;
float Rref1=0;  
float Rref2=0; 
float Rref3=0;

int d[]={0,0,0,0,0,0,0}, pin_select[7]={};
int store_mat[7][7]={};
int ref1_pins[7] = {};
int ref2_pins[7] = {};
int ref3_pins[7] = {};

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

void loop()
{
  while(flag==true)
  {
    //ch0 
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
    digitalWrite(6,LOW);      //LSB for MC
    
    d[0]=0;       //B6  //LOW-->switch ON(closed)-->R inactive
    d[1]=0;       //B5
    d[2]=0;       //B4
    d[3]=0;       //B3
    d[4]=0;       //B2
    d[5]=0;       //B1
    d[6]=0;       //B0--100K
    pinset(d);
    
    //float r = res_calc(d);
    data1 = analogRead(A0);
    vout1 = (data1*Vin)/1023.0;
    Serial.print("Vout1= ");
    Serial.println(vout1);
    data2 = analogRead(A1);
    vout2 = (data2*Vin)/1023.0;
    Serial.print("Vout2= ");
    Serial.println(vout2);
    
    //float R = r*((vout1)/(vout2-vout1));
    flag=false;
    
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
    if(pin_select[k]==1)        //HIGH-->switch OFF(open)-->R active
    {
      temp+= Rref_arr[k];
    }
  } 
  temp=temp+51.0;
  return(temp);
}
