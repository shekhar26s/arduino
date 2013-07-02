char msg = '0';
String inData;

void setup() {    
  Serial.begin(9600);  
}  
  
void loop(){  
  inData="";
  
  
  while(Serial.available() > 0){
    char recieved = Serial.read();
    inData += recieved;        
  }
  
  Serial.println(inData);
  delay(1000);
}
