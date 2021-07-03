#include <PinChangeInterrupt.h>

const byte rise_Pin = 4;

int b[5]={1,1,1,1,1};
float data1=0,data2=0;
float Vin=5,vout1=0,vout2=0;
float Rref=(b[0]*200+b[1]*550+b[2]*1493+b[3]*5621+b[4]*12000+100),Rsen[100]={};
float v1_ar[100]={};
float v2_ar[100]={};
int count=0,chk=0,num=0;
int avg_count = 0;
double sum_input = 0;
double sum_output = 0;
float avg_input = 0;
float avg_output = 0; 
float maxm=0,minm=0;
double sum=0,avg=0;
float t=1E-6;//1nF
float constant=(0.9*t*Rref);

void setup() {
  pinMode(rise_Pin,LOW);
  Serial.begin(9600);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(rise_Pin), read_func, RISING);
  
}

void read_func(){
  if(digitalRead(4)==HIGH)
  {
    if(count<100)
    {
  data1=analogRead(A0);
  data2=analogRead(A1);
  vout1= (data1*Vin)/1023.0;
  vout2= (data2*Vin)/1023.0;
  //vout1+=0.04;
  if(vout1 > 0.4){
    v1_ar[num]=vout1;
    v2_ar[num]=vout2;
    //Rsen[num]= Rref*(vout1/(vout2 - vout1));
    //Rsen[num] = ((Rref*vout1)-(t*Rref*vout1)+(constant))/(vout2-vout1);
    num++;
  
  }
  count++;
  }
    if(count==100)
    {
      chk=1;  
  }
}
}


void loop() {
  if(chk==1)
  {
      float sum=0;
      detachPinChangeInterrupt(digitalPinToPinChangeInterrupt(rise_Pin)); 
      float maxm=Rsen[0];
      float minm=Rsen[0];
      for(int i=1;i<num;i++)
      {
        if(Rsen[i]>maxm)
        {
          maxm=Rsen[i];
        }
      }
      for(int i=1;i<num;i++)
      {
        if(Rsen[i]<minm)
        {
          minm=Rsen[i];
        }
      }
      Serial.println("vout1");
      for(int i=0;i<num;i++)
      {
        
        Serial.println(v1_ar[i]);
         //sum+=Rsen[i];
      }
      Serial.println("vout2");
      for(int i=0;i<num;i++)
      {
        
        Serial.println(v2_ar[i]);
         //sum+=Rsen[i];
      }
//      float   avg =sum/num;
//      Rsen= Rref*(avg_input/(avg_output - avg_input));
//      
//      Serial.print("Average= "); 
//      Serial.println(avg);  
//      Serial.print("Maximum= "); 
//      Serial.println(maxm);
//      Serial.print("Minimum= "); 
//      Serial.println(minm);
//      //Serial.println(num);
      count=0;   
      sum_input=0;
      sum_output=0;   
      chk=0;    

    }
  }
