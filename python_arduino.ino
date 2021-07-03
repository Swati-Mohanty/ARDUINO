const int sec1=10000;
const int sec=1000;
const int Rin=300;
float data=0;
float Vin= 3.3;
float Vout= 0;
float Rsen= 0,R2=0;
float Rref1=328000;//9900   //99.4 Kohms
float Rref2=2180000;//1003000//;  //1.003 Mohms
float Rref3=10.10;//10160000; //10.16 Mohms
float buffer=0;
long int sumR=0;
double sum=0;
float avgR=0,temp=0;
bool flag=true;
char R1_select;
char R2_select;
char R3_select;

void setup()
{
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(2,OUTPUT);
  analogReference(EXTERNAL);
  Serial.begin(9600);
  Serial.println("Select reference range for sensors [without any space]" );
      Serial.println("'1':1K to 100 Kohm ");
      Serial.println("'2':100K to 1 Megaohm ");
      Serial.println("'3':1Megaohm to 10Megaohm ");
      delay(sec1);
      delay(sec1);
      delay(sec);

}


void loop()
{
  for(int a=0;a<3;a++)
  {
    if(a==0)
    { 
    
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);      //LSB
      Serial.println("1st sensor reading----> ");
     
      delay(sec);
      R1_select=Serial.read();
      //R1_select='2';
      switch(R1_select)
      {
        case '1':
        {
          //0th channel resistance w.r.t first reference
          Serial.println("Reference: 1K to 100K");
          digitalWrite(7,LOW);        //LSB
          digitalWrite(8,LOW); 
          
          delay(sec1);
          for(int i=0;i<3;i++)         
           { 
            data= analogRead(A0);   
            delay(sec);
            
            float vol=(data*Vin)/1024.0;     
            
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref1;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
           
           
            }
            Serial.print("Data Read=");
            Serial.println(data);
            avgR=sumR/3.0;
            //Serial.print("Resistance : ");
            Serial.println(avgR);
            
            avgR=0;
            sumR=0;
        }
        break;
        case '2':
        {
          //0th channel resistance w.r.t second reference
          Serial.println("Reference: 100K to 1M");
          digitalWrite(7,HIGH); 
          digitalWrite(8,LOW); 
          delay(sec);
          
          for(int i=0;i<3;i++)         
           {
            data= analogRead(A0);   
            delay(sec);
            
            float vol=(data*Vin)/1024.0;     
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref2;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
            
           
            }
            Serial.print("Data Read=");
            Serial.println(data);
            avgR=sumR/3.0;
            //Serial.print("Resistance : ");
            Serial.println(avgR);
            
            avgR=0;
            sumR=0;
              }
        break;
        case '3':
        {
          //0th channel resistance w.r.t third reference
          Serial.println("Reference: 1M to 10M");
          digitalWrite(7,LOW); 
          digitalWrite(8,HIGH); 
          digitalWrite(13,HIGH);
          delay(sec);
          
          for(int i=0;i<3;i++)         
           {
            data= analogRead(A0);   
            delay(sec);
           
            float vol=(data*Vin)/1024.0;     
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref3;     //current
            R2=vol/buffer;
            //Rsen=R2;
            
            temp=(5.02-R2);
            Rsen=((R2*5.02)/temp);
            sum+=Rsen;
      
           
            }
            Serial.print("Data Read=");
            Serial.println(data);
            avgR=sum/3.0;
            //Serial.print("Resistance : ");
            Serial.print(avgR,3);
            //Serial.print(" ");
            //Serial.println("Mega");
            

            avgR=0;
            sum=0;
              }
        break;
      }
       
      
    }
    
    else if(a==1)
    {
      
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);      //LSB
      Serial.println("2nd sensor reading----> ");
      
      delay(sec);
     R2_select=Serial.read();
      //R2_select='2';
      switch(R2_select)
      {
        case '1':
        {
          //1st channel resistance w.r.t first reference
          Serial.println("Reference: 1K to 100K");
          digitalWrite(7,LOW);        //LSB
          digitalWrite(8,LOW); 
          delay(sec);
          
          for(int i=0;i<3;i++)         
           { 
            data= analogRead(A0);   
            delay(sec);
            
            float vol=(data*Vin)/1024.0;     
            
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref1;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
           
            }
            Serial.print("Data Read=");
            Serial.println(data);
            avgR=sumR/3.0;
           // Serial.print("Resistance : ");
            Serial.println(avgR);

            avgR=0;
            sumR=0;
        }
        break;
        case '2':
        {
          //1st channel resistance w.r.t second reference
          Serial.println("Reference: 100K to 1M");
          digitalWrite(7,HIGH); 
          digitalWrite(8,LOW); 
          delay(sec);
          for(int i=0;i<3;i++)         
           {
            data= analogRead(A0);   
            delay(sec);
           
            
            float vol=(data*Vin)/1024.0;     
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref2;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
            
           
            }
            Serial.print("Data Read=");
            Serial.println(data);
            avgR=sumR/3.0;
            //Serial.print("Resistance : ");
            Serial.println(avgR);
            
            
            avgR=0;
            sumR=0;
              }
        break;
        case '3':
        {
          //1st channel resistance w.r.t third reference
          Serial.println("Reference: 1M to 10M");
          digitalWrite(7,LOW); 
          digitalWrite(8,HIGH); 
          digitalWrite(13,HIGH);
          delay(sec);
          
          for(int i=0;i<3;i++)         
           {
            data= analogRead(A0);   
            delay(sec);
            
            float vol=(data*Vin)/1024.0;     
           
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref3;     //current
            R2=vol/buffer;
            
            temp=(5.05-R2);
            Rsen=((R2*5.05)/temp);
            sum+=Rsen;
      
           
           
            }
            Serial.print("Data Read=");
            Serial.println(data);
            avgR=sum/3.0;
            //Serial.print("Resistance : ");
            Serial.print(avgR,3);
            //Serial.print(" ");
            //Serial.println(" Mega");
            
            avgR=0;
            sum=0;
              }
        break;
      }
    }
    
    else if(a==2)
    {
      
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);      //LSB
      Serial.println("3rd sensor reading----> ");
      
      delay(sec);
      R3_select=Serial.read();
      //R3_select='2';
      switch(R3_select)
      {
        case '1':
        {
          //2nd channel resistance w.r.t first reference
          Serial.println("Reference: 1K to 100K");
          digitalWrite(7,LOW);        //LSB
          digitalWrite(8,LOW); 
          delay(sec);
          
          for(int i=0;i<3;i++)         
           { 
            data= analogRead(A0);   
            delay(sec);
            
            float vol=(data*Vin)/1024.0;     
            
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref1;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
           
           
            }
            Serial.print("Data Read=");
            Serial.println(data);
            avgR=sumR/3.0;
            //Serial.print("Resistance : ");
            Serial.println(avgR);
           
            
            avgR=0;
            sumR=0;
        }
        break;
        case '2':
        {
          //2nd channel resistance w.r.t second reference
          Serial.println("Reference: 100K to 1M");
          digitalWrite(7,HIGH); 
          digitalWrite(8,LOW); 
          delay(sec);
          
          for(int i=0;i<3;i++)         
           {
            data= analogRead(A0);   
            delay(sec);
            
            float vol=(data*Vin)/1024.0;     
            
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref2;     //current
            R2=vol/buffer;
            
            Rsen=R2-Rin;
            sumR+=Rsen;
      
            
           
            }
            Serial.print("Data Read=");
            Serial.println(data);
            avgR=sumR/3.0;
            //Serial.print("Resistance : ");
            Serial.println(avgR);
           
            
            avgR=0;
            sumR=0;
              }
        break;
        case '3':
        {
          //2nd channel resistance w.r.t third reference
          Serial.println("Reference: 1M to 10M");
          digitalWrite(7,LOW); 
          digitalWrite(8,HIGH); 
          digitalWrite(13,HIGH);
          delay(sec);
          
          for(int i=0;i<3;i++)         
           {
            data= analogRead(A0);   
            delay(sec);
           
            float vol=(data*Vin)/1024.0;     
            
            //unknown resistance calculated
            buffer=(Vin-vol)/Rref3;     //current
            R2=vol/buffer;
            //Rsen=R2;
            
            temp=(5.02-R2);
            Rsen=((R2*5.02)/temp);
            sum+=Rsen;
      
            
           
            }
            Serial.print("Data Read=");
            Serial.println(data);
            avgR=sum/3.0;
            //Serial.print("Resistance : ");
            Serial.print(avgR,3);
            //Serial.print(" ");
            //Serial.println("Mega");
            
            avgR=0;
            sum=0;
              }
        break;
      }
    }
    
    else
    {
      Serial.println("No sensor connected");
    }
    delay(sec);
  }
}
       
  
