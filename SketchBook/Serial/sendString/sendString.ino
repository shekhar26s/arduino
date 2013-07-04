String inData;
char recieved;
int count= 0;
int lon= 0;

void setup() {    
  Serial.begin(115200);
}  

void llamada(){
  Serial.println(inData);
}

void loop(){
  //Vaciamos el String!
  inData="";
  count=0;
  //Si entran datos.. los recorremos
  while(Serial.available() > 0){
    //Contamos la longitud
    if(count==0){
      lon=Serial.available();
    }
    //Leemos y cargamos el byte en la variable
    recieved = Serial.read();
    inData += recieved;
    //Si la llegamos a 1 hemos terminado
    if((lon-count)==1){ 
      llamada();
    }
    
    delayMicroseconds(500);
    count++;    
  }
  
  delay(500);
}
