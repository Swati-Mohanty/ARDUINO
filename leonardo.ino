int data = 0, sec = 2000;
float Vin = 5;
float Vout = 0;
float Rref = 1000000;
float Rsen1 = 0 ,Rsen2 = 0 ,Rsen3 = 0;
float avg = 0, sum = 0;
float buffer = 0;
char ser;

void setup() 
{
  Serial.begin(9600);
  pinMode (4,OUTPUT);     //pin25
  pinMode (6,OUTPUT);     //pin27
  pinMode (12,OUTPUT);    //pin26
}

void loop() 
{
  Serial.println("Calculating resistances w.r.t. 1Mohms!!");
  digitalWrite(4,LOW);
  digitalWrite(6,LOW);
  digitalWrite(12,LOW);
  Serial.println("First Sensor---->");
  for(int i=0;i<5;i++)
  {
    data= analogRead(A4);
    float vol = (data*Vin)/1024.0;
    Serial.println(vol);
    delay(sec);
    buffer = (Vin-vol)/Rref;
    Rsen1 = vol/buffer;
    sum += Rsen1;
  }
  avg = sum/5.0;
  Serial.println("Resistance =" );
  Serial.println(avg);
  sum=0;avg=0;

  digitalWrite(4,LOW);
  digitalWrite(6,LOW);
  digitalWrite(12,HIGH);
  Serial.println("Second Sensor---->");
  for(int i=0;i<5;i++)
  {
    data= analogRead(A4);
    float vol = (data*Vin)/1024.0;
    Serial.println(vol);
    delay(sec);
    buffer = (Vin-vol)/Rref;
    Rsen2 = vol/buffer;
    sum += Rsen2;
  }
  avg = sum/5.0;
  Serial.println("Resistance =" );
  Serial.println(avg);
  sum=0;avg=0;

  digitalWrite(4,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(12,LOW);
  Serial.println("Third Sensor---->");
  for(int i=0;i<5;i++)
  {
    data= analogRead(A4);
    float vol = (data*Vin)/1024.0;
    Serial.println(vol);
    delay(sec);
    buffer = (Vin-vol)/Rref;
    Rsen3 = vol/buffer;
    sum += Rsen3;
  }
  avg = sum/5.0;
  Serial.println("Resistance =" );
  Serial.println(avg);
  sum=0;avg=0;
}
