#include<TimerOne.h>

bool flag =true;
int count=0,chk=0;
int count_arr[4]={4,6,10,20};
void setup() {
  pinMode(9,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);

}
void(* resetFunc) (void) = 0;

void loop() 
{
  while(flag==true)
  {
      Timer1.initialize(2000);    //us==2ms==500Hz
      //if(count<10)
     // {
      Timer1.attachInterrupt(timer_isr_high);
      //}
      //else if (count==10){}
      flag=false;
  }
  if(chk==1)
  {
    Timer1.detachInterrupt();
    Timer1.initialize(100);   //us==0.1ms
    Timer1.attachInterrupt(timer_isr_low);
    count=0;
    chk=0;
  }

}

void timer_isr_high()
{
  if(count<10)
  {
  digitalWrite(9,HIGH);
  digitalWrite(5,HIGH);
  //sample for 40us
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  //hold
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  count++;
  
   if(count==10)
      {
        chk=1;
        
      }
  }
  

}
void timer_isr_low()
{
  digitalWrite(9,LOW);
  digitalWrite(5,LOW);
  resetFunc();
}
