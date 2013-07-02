/* Knight Rider ( El coche fatastco )
 *---------------------------------------
 *@desc    -> 
 *@author  ->
 *@license ->
 */
 
//Definimos las variables
int pinArray[] = {2, 3, 4, 5, 6},  //| Pines digitales
    i = 0,                         //| Contador incremental
    timer = 30;                    //| Tiempo de cambio (en ms)
 
//Setup de inicio
void setup(){
  for (i=0;i<5;i++) {         
    pinMode(pinArray[i], OUTPUT);
  }
}

//Cuerpo del codigo
void loop() {
  //De izquierda a derecha
  for (i=0;i<4;i++) {                                                 
    digitalWrite(pinArray[i], HIGH);
    delay(timer);
    digitalWrite(pinArray[i + 1], HIGH);
    delay(timer);
    digitalWrite(pinArray[i], LOW);
    delay(timer*2);
  }
  //De derecha a izquierda
  for (i=4;i>0;i--){
    digitalWrite(pinArray[i], HIGH);
    delay(timer);
    digitalWrite(pinArray[i - 1], HIGH);
    delay(timer);
    digitalWrite(pinArray[i], LOW);
    delay(timer*2);
  }
}
