int wait= 1000;
int val=0;
float Rsen=0, R2=0;
int Rref=9860;
float i=0;
void setup() 
{
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  
}

void loop() 
{
  //for 13th pin--000   
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  val =  analogRead(A0); //read data from X0
  delay(wait);
  float vol=(val*5)/1024.0;     //voltage across sensor+mux
  Serial.print("Value 0th=");
  Serial.println(val);
  Serial.print("Voltage=");
  Serial.println(vol);
  delay(wait);
  //unknown resistance calculated
  i=(5-vol)/Rref;     //current
  R2=vol/i;
  Rsen=R2-200;

Serial.print("Resistance across 0th channel=");
  Serial.println(Rsen);

  //from 14th pin--001
  digitalWrite(8,HIGH);   
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  val =  analogRead(A0);
  delay(wait);
  float vol2=(val*5)/1024.0;
  Serial.print("Value 1st=");
  Serial.println(val);
  Serial.print("Voltage=");
  Serial.println(vol2);
  delay(wait);
  i=(5-vol2)/Rref;    
  R2=vol2/i;
  Rsen=R2-200;
  Serial.print("Resistance across 1st channel=");
  Serial.println(Rsen);


  //for 15th pin--010
  digitalWrite(8,LOW);   
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  val =  analogRead(A0);
  delay(wait);
  float vol3=(val*5)/1024.0;
  Serial.print("Value 2nd=");
  Serial.println(val);
  Serial.print("Voltage=");
  Serial.println(vol3);
  delay(wait);
  i=(5-vol3)/Rref;
  R2=vol3/i;
  Rsen=R2-300;
  
Serial.print("Resistance across 2nd channel=");
  Serial.println(Rsen);

  
/*
  for (int i=0;i<8;i++)
  {
  digitalWrite(8,bitRead(i,0));
  digitalWrite(9,bitRead(i,1));
  digitalWrite(10,bitRead(i,2));
  int Sensor1 =  analogRead(A0); //read data from X1
  delay(wait);
  Serial.print(Sensor1);
  }
*/
   
  
}
