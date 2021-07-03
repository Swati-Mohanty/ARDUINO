long var=10E6;
long vard=23e-5;
bool flag=true;
char ref;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello Leo!");

}

void loop() {
  // put your main code here, to run repeatedly:
  while(flag==true)
  {
 /* Serial.println(var);
  Serial.println(vard,4);
  float a=1/var;
  Serial.println(a,4);
  double b=1/var;
  Serial.println(b,4);*/
  for(int a=0;a<3;a++)
  {
   if(a==0)
   {
    Serial.println("First Sensor");
    Serial.println("Select reference");
    delay(3000);
    ref=Serial.read();
    switch(ref)
    {
      case '1':Serial.print("First reference");
      break;
      case '2':Serial.print("Second reference");
      break;
    }
    free(ref);
   }
   else if(a==1)
   {
    Serial.println("Second Sensor");
    Serial.println("Select reference");
    Serial.println(ref);
    delay(3000);
   ref=Serial.read();
   Serial.println(ref);
    switch(ref)
    {
      case '1':Serial.print("First reference");
      break;
      case '2':Serial.print("Second reference");
      break;
    }
   }
   else if(a==2)
   {
    Serial.println("Third Sensor");
   }
   else
   {
    Serial.print("No Sensor");
   }
  
  }
  flag=false;
  }




}
