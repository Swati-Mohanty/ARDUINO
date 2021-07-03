
float data1=0,data2=0;
float Vin= 3.3;
float Vout= 0,vol=0,vout1=0;
float Rsen1_arr[3]= {};
float Rsen2_arr[3]= {};
float Rsen3_arr[3]= {};


float Rref_arr[5] = {51.00,100.00,820.00,1600.00,18000.00};

float Rref=0;
float Rref1=0;  
float Rref2=0; 
float Rref3=0;
float buffer=0;
long int sumR=0;
int i=0,d[]={1,0,0,0,0}, pin_select[5]={};
int store_mat[5][5]={};
bool flag = true;


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
  
  
  analogReference(EXTERNAL);
  Serial.begin(9600);
  
}


void loop()
{
  if(flag==true)
  {
     Rref1 = reference_calculation();
     Serial.print("Reference :");
     Serial.println(Rref1);

     //Sensor value calculation
     
      flag=false;
    }
}

    
    

 /*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/   

float reference_calculation()
{
   float vout2[5] = {0.904, 0.913, 2.751, 1.131, 0.987};      
      vout1 = 0.9;
      Serial.print("VOUT1 ");
      Serial.println(vout1);
  
      //First Sensor selection
      
      Serial.println("1st reference calculation----> ");  
    
      //0th channel resistance 
      float vol_array[5]={};
      double temp_res_array[5]={};
      int count=0;
    int j=0;
      pinset(d);     //MSB high,  Rref1 used
  
      
      
      for(int i=0; i<5; i++)
      {
       vol = vout2[i];     
        Serial.print("VOUT2 ");
        Serial.println(vol);
        if(vol>3.0)
        {
          d[i]=0;
          d[i+1]=1;
          pinset(d);
        }
        else
        {
          vol_array[j]=vol;
          store_array(d,count);
          count++;
          j++;
          d[i+1]=1;
          pinset( d);
        }
        
      }

    //find best Refernce corresponding to highest voltage

    float maxm = vol_array[0];
    int index ;
    for(int j=1;j<count;j++)
     {
      if (vol_array[j]>maxm )
      {
        maxm = vol_array[j];
        index = j;
      }
      
     }
     for(int a=0;a<5;a++)
     {
      pin_select[a]=store_mat[index][a];
     }
     Rref = res_calc(pin_select);
     return(Rref);
  
}

void store_array(int d[],int c)
{
  for(int i=0;i<5;i++)
  {
    store_mat[c][i]=d[i];
  }
}


void pinset(int d[])
{
    digitalWrite(12, d[0]);    //MSB -->DO
    digitalWrite(13, d[1]);
    digitalWrite(2, d[2]);
    digitalWrite(3, d[3]);
    digitalWrite(4,d[4]);
  
}

float res_calc(int pin_select[])
{
  float temp=0;
  for(int k=0;k<5;k++)
  {
    if(pin_select[k]==1)
    {
      temp+= Rref_arr[k];
    }
  }
  return(temp);
}
 
  
