int sensorPin = A0; // select the input pin for the potentiometer
int sensorValue = 0; // variable to store the value coming from the sensor


float i = 0;
float fixtemp = 20.;
int fixInput = 560;
float fixedDegreeValue = 5.5;

void setup () 
{
  pinMode(13, OUTPUT);
  Serial.begin (9600);
}
 
void loop () 
{
  sensorValue = analogRead(sensorPin);  
  if (sensorValue > fixInput ){
    
    i = sensorValue - fixInput;
    i = i /fixedDegreeValue; 
    Serial.print("Temperature = ");
    fixtemp = fixtemp - i;
    Serial.print(fixtemp);
    Serial.println(" C");
  }  
  else if(sensorValue < fixInput) //thea cup
  {
     i =  fixInput - sensorValue;
    i = i /fixedDegreeValue; 
    fixtemp = fixtemp + i;
    
    Serial.print("Temperature = ");
    Serial.print(fixtemp);
    Serial.println(" C");
  }
  else if(sensorValue == fixInput ){  
    
    Serial.println(" temperature  = 20 C");
    
  }
  if(fixtemp >25.5){
    digitalWrite(13, HIGH);
  }
  if(fixtemp <24.5){
    digitalWrite(13,LOW);
  }
  fixtemp = 20;
}

