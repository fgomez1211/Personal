
//---------------------------------------------------------------
// Declaracion de variables y asignacion de pin

int pinA
int pinB
int pinC
int pinD
int pinE
int pinF
int pinG
int pinD

  //Este digito el transistor
int DIG1



//-----------------------------------------------
/* Funcion chooseDigit. En esta funcion yo le indico al programa cuales segmentos 
   son los que va a encender dependiendo de cada caso. 
   
   Ejemplo: en el caso 1, el debe de encender los segmentos: b y c. por lo 
   tanto b y c estaran en HIGH y los demas, en LOW. Y
   asi sucesivamente. 
 */

void chooseDigit(char num){
  switch(num){

   default:
     digitalWrite(pinA, HIGH);
     digitalWrite(pinB, HIGH);
     digitalWrite(pinC, HIGH);
     digitalWrite(pinD, HIGH);
     digitalWrite(pinE, HIGH);
     digitalWrite(pinF, HIGH);
     digitalWrite(pinG, LOW);
     digitalWrite(pinDP, LOW);
   break;

   case 1:
     digitalWrite(pinA, LOW);
     digitalWrite(pinB, HIGH);
     digitalWrite(pinC, HIGH);
     digitalWrite(pinD, LOW);
     digitalWrite(pinE, LOW);
     digitalWrite(pinF, LOW);
     digitalWrite(pinG, LOW);
     digitalWrite(pinDP, LOW);

     break;

   case 2:
     digitalWrite(pinA, HIGH);
     digitalWrite(pinB, HIGH);
     digitalWrite(pinC, LOW);
     digitalWrite(pinD, HIGH);
     digitalWrite(pinE, HIGH);
     digitalWrite(pinF, LOW);
     digitalWrite(pinG, HIGH);
     digitalWrite(pinDP, LOW);
     break;  

   case 3:
     digitalWrite(pinA, HIGH);
     digitalWrite(pinB, HIGH);
     digitalWrite(pinC, HIGH);
     digitalWrite(pinD, HIGH);
     digitalWrite(pinE, LOW);
     digitalWrite(pinF, LOW);
     digitalWrite(pinG, HIGH);
     digitalWrite(pinDP, LOW);
     break;  

   case 4:
     digitalWrite(pinA, LOW);
     digitalWrite(pinB, HIGH);
     digitalWrite(pinC, HIGH);
     digitalWrite(pinD, LOW);
     digitalWrite(pinE, LOW);
     digitalWrite(pinF, HIGH);
     digitalWrite(pinG, HIGH);
     digitalWrite(pinDP, LOW);
     break;
       
   case 5:
     digitalWrite(pinA, HIGH);
     digitalWrite(pinB, LOW);
     digitalWrite(pinC, HIGH);
     digitalWrite(pinD, HIGH);
     digitalWrite(pinE, LOW);
     digitalWrite(pinF, HIGH);
     digitalWrite(pinG, HIGH);
     digitalWrite(pinDP, LOW);
     break;  

   case 6:
     digitalWrite(pinA, HIGH);
     digitalWrite(pinB, LOW);
     digitalWrite(pinC, HIGH);
     digitalWrite(pinD, HIGH);
     digitalWrite(pinE, HIGH);
     digitalWrite(pinF, HIGH);
     digitalWrite(pinG, HIGH);
     digitalWrite(pinDP, LOW);
     break;     

   case 7:
     digitalWrite(pinA, HIGH);
     digitalWrite(pinB, HIGH);
     digitalWrite(pinC, HIGH);
     digitalWrite(pinD, LOW);
     digitalWrite(pinE, LOW);
     digitalWrite(pinF, LOW);
     digitalWrite(pinG, LOW);
     digitalWrite(pinDP, LOW);
     break;  

   case 8:
     digitalWrite(pinA, HIGH);
     digitalWrite(pinB, HIGH);
     digitalWrite(pinC, HIGH);
     digitalWrite(pinD, HIGH);
     digitalWrite(pinE, HIGH);
     digitalWrite(pinF, HIGH);
     digitalWrite(pinG, HIGH);
     digitalWrite(pinDP, LOW);
     break;  
     
   case 9:
     digitalWrite(pinA, HIGH);
     digitalWrite(pinB, HIGH);
     digitalWrite(pinC, HIGH);
     digitalWrite(pinD, HIGH);
     digitalWrite(pinE, LOW);
     digitalWrite(pinF, HIGH);
     digitalWrite(pinG, HIGH);
     digitalWrite(pinDP, LOW);
     break;
  }
}

void setup() {
  // Indicar si las variables creadas arriba son entradas o salidas.
  pinMode (pinA, );
  pinMode (pinB, );
  pinMode (pinC, );
  pinMode (pinD, );
  pinMode (pinE, );
  pinMode (pinF, );
  pinMode (pinG, );
  pinMode (pinDP, );

  pinMode (DIG1, );

  Serial.begin(9600);

}


void loop(){

  //Realizar el mapeo de la variable de X a Y.
  int timer = map(analogRead(A1), 0, 1023, X, Y);
  Serial.println(timer); 
  
  for (int i = 0; i <= Z; i++) {
    chooseDigit(i);
    digitalWrite(DIG1, HIGH ); 
    delay(timer);
  
 }
  }


