
//duty cycle 10 
//changes after delay_time

#define NOP __asm__ __volatile__("nop\n\t");

int delay_time = 47;   //4ms
int switch_time = 2000;   //2sec

float data1=0,data2=0;
float Vin= 5;
float vout1=0;

bool flag = true;


void setup() 
{
 //sensor pins
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);   
  
  pinMode(5,OUTPUT);    //PWM

  
  //analogReference(EXTERNAL);
  Serial.begin(9600);
 

}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop()
{
    
     for(int i=5;i<50;i+=3)
     {
      analogWrite(5, i);
      delay(delay_time);
       int data = analogRead(A0);
       float vol = 5*data/1023.0;
       Serial.println(vol);
     }
     
}
