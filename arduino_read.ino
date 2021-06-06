float v1_arr[10]={};
float v2_arr[10]={};
float Rsen_arr[5]={};
int chk=0;
bool flag=true;
const float delta_t=100;
double cap=0.001;
float Rref=2475;

void setup()
{
  // put your setup code here, to run once:

}

void loop()
{
  if((chk==1)&&(flag==true))
  {
    for(int i=0;i<5;i++)
    {
      float temp1 = (v2_arr[i+5]-v1_arr[i+5])/Rref;
      float temp2 = ((v2_arr[i+4]-v1_arr[i+4])-(v2_arr[i+5]-v1_arr[i+5]));
      float temp3 = (cap*temp2)/delta_t;
      float buffer = temp1+temp3;
      Rsen_arr[i] = v1_arr[i+5]/buffer;
    }
    for(int j=0;j<5;j++)
    {
      Serial.println(Rsen_arr[j]);
    }
    flag = false;
  }

}
