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

  
    d[0]=1;
    d[1]=1;
    d[2]=1;
    d[3]=1;
    d[4]=1;
    pinset(d);
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
