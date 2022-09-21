
//---------------------------------------------------------------
// Declaracion de variables y asignacion de pin
//7 Segment Display + Switch/Case + Dip Switch + Multiplexing

int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;
int pinDP = 9;

int DIG1 = 13;
int DIG2 = 12;
int DIG3 = 11;
int DIG4 = 10;

int timerValue = 1;

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
  // put your setup code here, to run once:
  pinMode (pinA, OUTPUT);
  pinMode (pinB, OUTPUT);
  pinMode (pinC, OUTPUT);
  pinMode (pinD, OUTPUT);
  pinMode (pinE, OUTPUT);
  pinMode (pinF, OUTPUT);
  pinMode (pinG, OUTPUT);
  pinMode (pinDP, OUTPUT);

  pinMode (DIG1, OUTPUT);
  pinMode (DIG2, OUTPUT);
  pinMode (DIG3, OUTPUT);
  pinMode (DIG4, OUTPUT);

  Serial.begin(9600);

}

//---------------------------------------------

void pickDigit(int digit){
  
  digitalWrite(DIG1, LOW);
  digitalWrite(DIG2, LOW);
  digitalWrite(DIG3, LOW);
  digitalWrite(DIG4, LOW);

  switch(digit){
    case 1: digitalWrite(DIG1, HIGH); break;
    case 2: digitalWrite(DIG2, HIGH);
      		digitalWrite(pinDP, LOW); break;
    case 3: digitalWrite(DIG3, HIGH); break;
    default:digitalWrite(DIG4, HIGH); break;
  }
}

//---------------------------------------------

void sevenSegment(int number){
/* En la función sevenSegment, La primera seccion toma cualquier 
   valor de 4 digitos decimales y los separa en 4digitos, para desplegar
   cada numero en cada digito de los 4 displays en su respectivo orden.
 */


  unsigned char thousands = int ((number/1000));
  unsigned char hundreds  = int ((number/100)%10);
  unsigned char tens      = int ((number/10)%10);
  unsigned char ones      = int (number%10);


  int timerValue = analogRead(A5);
  chooseDigit(thousands);
  pickDigit(1);
  delay(timerValue);  

  chooseDigit(hundreds);
  pickDigit(2);
  delay(timerValue);

  chooseDigit(tens);
  pickDigit(3);
  delay(timerValue);

  chooseDigit(ones);
  pickDigit(4);
  delay(timerValue);
}

//---------------------------------------------


//---------------------------------------------


void loop(){
  /*El entero "sensorValue": 
  	1. va a leer el valor del potenciometro
  	2. Lo va a imprimir en el monitor serial
    3. Lo va a procesar en la funcion sevenSegment(7)
    4. Esto tendrá un delay de 1ms
  
  */ 
  
  
  int sensorValue = map(analogRead(A2), 0, 1023, 100, 200);
  Serial.println(sensorValue);
  sevenSegment(sensorValue);  
  delay(1);
  
 }