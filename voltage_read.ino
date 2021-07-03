float Ref = 330000;
float Vin= 5;
bool flag = true;


void setup() 
{
  pinMode(13,OUTPUT);    
  Serial.begin(9600);
 
}

void loop()
{
//   //Read voltage
//   int data = analogRead(A0);
//   float vol = Vin*data/1023.0;
//   //for current calculation
//   float curr = vol/Ref;
//   Serial.println(curr,6);
//   Serial.println(vol);
//   delay(1000);

//   //Blink LED
//   digitalWrite(13,HIGH);
//   delay(1000);
//   digitalWrite(13,LOW);
//   delay(1000);

   //Controlled read
   if(flag == true)
   {
     int data = analogRead(A0);
     float vol = Vin*data/1023.0;
     //for current calculation
     float curr = vol/Ref;
     Serial.print("Current = ");
     Serial.println(curr,6);
     Serial.print("Voltage = ");
     Serial.println(vol);
     flag = false;
   }
   
 
}
