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
 
  Serial.begin(9600);
 
}

void loop() 
{
  //10% duty cycle
  analogWrite(9, 25);
  //delay(5);
  
  //20% duty cycle
  analogWrite(9, 51);
  //delay(5);
  
  //30% duty cycle
  analogWrite(9, 76);
  //delay(5);
  
  //40% duty cycle
  analogWrite(9, 102);
  //delay(5);
  
  //50% duty cycle
  analogWrite(9, 127);
  //delay(5);

  //60% duty cycle
  analogWrite(9, 160);
  //delay(5);
  

}
/*
void setup() {
// for PWM frequency of 244.14 Hz  
TCCR0B = TCCR0B & B11111000 | B00000100;  
pinMode(5,OUTPUT);

}

void loop() 
{
analogWrite(5,51);


}

//B00000001-->62500.00 Hz
//B00000010-->7812.50 Hz
//B00000011-->976.56 Hz
//B00000100-->244.14 Hz
//B00000101-->61.04 Hz
*/
