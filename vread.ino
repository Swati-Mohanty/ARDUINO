int a=10;
char c;
void setup()
{
  Serial.begin(9600);

}

void loop()
{
  c=Serial.read();
  if(Serial.available())
  {
    for(int i=0;i<2;i++)
    {
    Serial.print("Value=");
    Serial.println(a);
    a+=10;
    Serial.println("Please wait for 5 seconds to read next value!!");
    delay(5000);
    }
    Serial.print("Value=");
    Serial.println(a);
  }
  

}
