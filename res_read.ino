int data= 0;
float Vin= 5;
float Vout= 0;
float R1= 1000000;
//float R1=0;
float R2= 0;
//float R3=0;
float Resistance=0;

float buffer= 0;
bool flag=true;

void setup()
{
//analogReference(EXTERNAL);
Serial.begin(9600);

}

void loop()
{
if(Serial.available())
{
while(flag==true)
{
for(int i=0;i<10;i++)
{
data= analogRead(A4);   //actually stored in didgital
if(data)
{
buffer= data * Vin;
Vout= (buffer)/1024.0;        //converted to digital

//unknown resistance calculated
buffer= (Vin/Vout) -1;   
R2= R1 * buffer;

Serial.print("Vout: ");
Serial.println(Vout);
Serial.print("R2: ");
Serial.print(R2);
Serial.println(" ohms");


delay(2000);
}
}
flag=false;
}
}
}



//The Arduino Uno ADC is of 10-bit resolution (so the integer values from 0 - 2^10 = 1024 values). 
//This means that it will map input voltages between 0 and 5 volts into integer values between 0 and 1023. 
//So if we multiply input anlogValue to (5/1024), then we get the digital value of input voltage.
