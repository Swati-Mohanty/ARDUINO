#include <TimerOne.h>

void setup() 
{
  pinMode(9,OUTPUT);
  pinMode(5,OUTPUT);
  Timer1.initialize();

}

void loop()
{
  if(Serial.available())
  {
    Timer1.attachInterrupt(timer_isr);
  }

}

void timer_isr()
{
  digitalWrite(9,HIGH);
  digitalWrite(5,HIGH);
}
