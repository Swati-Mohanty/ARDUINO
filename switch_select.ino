float data1=0,data2=0;
float Vin=3.3,vout1=0,vout2=0;
int d[5]= {0,0,0,0,0};
bool flag=true;

void setup()
{
  //sensor pins
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);   
  //SnH pins
  pinMode(7,OUTPUT);    //L0--->ADC1-->A0
  pinMode(8,OUTPUT);    //L1--->ADC2-->A1
  //switch pins
  pinMode(12,OUTPUT);        //LSB  B0    pin 18 on uc--->51K
  pinMode(13,OUTPUT);        //D1         pin 19 on uc--->100K
  pinMode(2,OUTPUT);         //D2         pin 4 on uc---->820K
  pinMode(3,OUTPUT);         //D3         pin 5 on uc---->1.6M
  pinMode(4,OUTPUT);         //MSB  B4    pin 6 on uc---->18M
}

void loop()
{
  digitalWrite(9,LOW);    //CLK
  digitalWrite(5,LOW);    //CLKB

  digitalWrite(7,LOW);   //sample the value for adc1
  digitalWrite(8,LOW);   //sample the value for adc2
  
    delay(2000);
    d[0]=1;
    d[1]=1;
    d[2]=0;
    d[3]=0;
    d[4]=0;
    pinset(d);
    data1=analogRead(A0);
    vout1=(data1*Vin)/1023.0;
    Serial.println(vout1);
    delay(2000);
    data2=analogRead(A1);
    vout2=(data2*Vin)/1023.0;
    Serial.println(vout2);
    delay(2000);
    //flag=false;
  
}


void pinset(int d[])
{
    digitalWrite(12, d[0]);    //LSB -->DO
    digitalWrite(13, d[1]);     
    digitalWrite(2, d[2]);      
    digitalWrite(3, d[3]);      
    digitalWrite(4,d[4]);      
  
}
