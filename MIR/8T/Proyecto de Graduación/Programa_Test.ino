
//Señales del Encoder
byte signalPin =18;
//byte signalPin_2 =19;
byte signalPin_3 =19;

byte signalPin_4 =20;

byte posicion_actual=0;


volatile long int home=0;
volatile long int index =0;


volatile long int contador_A=0;
volatile long int contador_anterior=0;
volatile long int contador_B=0;

//PMW Motores y Enables
int pwm1 = 4;
int pwm2 = 5;
int enable1 = 2;
int enable2 = 3;


//Pasos del encoder y relaciones entre el encoder y los engranajes.
const int pasos_encoder=512;
double relacion_eje_1=214.13;
double Posicion_actual=0;


//Pasos para una rotación completa de cada articulacion
double relacion_encoder_1=pasos_encoder*relacion_eje_1;

//Coordenadas de prueba en grados
double  grados_eslabon_1 =0;

//Coordenadas en pasos
double pasos_1 = (grados_eslabon_1/360) * relacion_encoder_1;


void setup(){

  Serial.begin(9600);
  //Señal del Encoder
  pinMode(signalPin, INPUT_PULLUP);
  pinMode(signalPin_3, INPUT_PULLUP);
  pinMode(signalPin_4, INPUT_PULLUP);
  //Declaración de las variables del encoder
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);

  attachInterrupt(digitalPinToInterrupt(signalPin), enc_A, FALLING);
  //attachInterrupt(digitalPinToInterrupt(buttonPin), enc_B, FALLING);
  attachInterrupt(digitalPinToInterrupt(signalPin_3), enc_index, FALLING);
  attachInterrupt(digitalPinToInterrupt(signalPin_4), enc_home, FALLING);


  //Activa los Enable del driver, dejando los PWM  para enceder/apagar el motor.
  digitalWrite(enable1, HIGH); 
  digitalWrite(enable2, HIGH);

  digitalWrite(pwm2,LOW);
  digitalWrite(pwm1,LOW);

  Serial.println("Iniciando rutina...");
  Serial.println("Buscando POS Home...");
  findhome();
  Serial.print("POS Home Encontrada!");
  digitalWrite(pwm2,LOW);
  digitalWrite(pwm1,LOW);
  contador_A=0;


}


void loop(){

 delay(5000);


  if (Serial.available() > 0) { // Revisar si hay un valor para leer en el puerto serial.
    grados_eslabon_1 = Serial.parseInt(); // Leer los grados desde el puerto serial.
    Serial.print("Grados: "); // Imprimir la etiqueta del valor leido
    Serial.println(grados_eslabon_1); // Imprimir el valor leido.
    delay(2000);
    }

  double pasos_1 = (grados_eslabon_1/360) * relacion_encoder_1; //Calculo de pasos a moverse según el valor leido en el puerto serial

  if (grados_eslabon_1 <0 && contador_A < pasos_1){           //Validación para movimiento antihorario.
    digitalWrite(pwm2,LOW);
    digitalWrite(pwm1,HIGH);
    Serial.println(contador_A);
    Serial.println(pasos_1);
    }
    else{
      grados_eslabon_1 =0;
      digitalWrite(pwm1,LOW);
      Posicion_actual = (contador_A/relacion_encoder_1) * 360;
      Serial.print("Posicion_actual: " );
      Serial.println(Posicion_actual);
      grados_eslabon_1 = 0;
      delay(5000);
      }



  if (grados_eslabon_1 >0 && contador_A < pasos_1){        //Validación para movimiento antihorario.
      digitalWrite(pwm2,LOW);
      digitalWrite(pwm1,HIGH);
      Serial.println(contador_A);
      Serial.println(pasos_1);
      }
      else{
        grados_eslabon_1 =0;
        digitalWrite(pwm2,LOW);
        Posicion_actual = (contador_A/relacion_encoder_1) * 360;
        Serial.print("Posicion_actual: " );
        Serial.println(Posicion_actual);
        delay(5000);
      }



  if (grados_eslabon_1 =0){
    digitalWrite(pwm1,LOW);
    digitalWrite(pwm2,LOW);
    }


}

// Función interrupt para el Canal A del encoder.
//--------------------------------------
void enc_A(){
    contador_A++;
}
//--------------------------------------



// Función interrupt para el Canal Index del encoder
//--------------------------------------
void enc_index(){
    index++;
}
//--------------------------------------



// Función interrupt para el Canal Home del encoder
//--------------------------------------
void enc_home(){
    home++;
    index=0;
}
//--------------------------------------


//------------------------------------------------------------------------------------------
// FUNCION: findhome(). Ejecuta una rutina para encontrar la POS Home de la articulación.
// Para encontrar la POS Home la articulación debe de encontrar un pulso del pin Home. 
// Mientras detecta el pulso, debe encontrar un siguiente pulso en Index.
// Cuando el brazo llega a un extremo de su rotación y no detecta el POS Home, 
// este valida si tiene la misma posición que la anterior
// si esto sucede 5 veces, la articulación se movera hacia el otro sentido para intentar buscar POS Home.

void findhome(){
  int m = 1;                          //Variable utilizada para indicar que se mueva el motor.
  int vuelta = -1;                    //Variable utilizada para indicar la cantidad de vueltas del encoder.
  int retry=0;                        
  contador_anterior=-999;
  contador_A=0;
  index=0;
  home = 0;

  while (home != 1 && vuelta !=1) {
    delay(100);
    if(m==1){
      digitalWrite(pwm2,LOW);
      digitalWrite(pwm1,HIGH);
    }else{
      digitalWrite(pwm1,LOW);
      digitalWrite(pwm2,HIGH);
    }

    if(contador_A==contador_anterior && contador_A!=0){
      retry++;
    }    

    if(contador_A!=contador_anterior){
      contador_anterior=contador_A;
    }

    if(retry>5){
      if(m==1){
        m=-1;
      }else{
      m=1;
      }
      retry=0;
      contador_A=0;
      contador_anterior=0;
      index=0;
      home=0;
    }

    if(home>0 && index>0){
      digitalWrite(pwm1,LOW);
      digitalWrite(pwm2,LOW);
      vuelta=1;
    }
    }
    Serial.print(contador_A);
    Serial.print(" , ");
    Serial.print(contador_anterior);
    Serial.print(" , ");
    Serial.print(home);
    Serial.print(" , ");
    Serial.print(m);
    Serial.print(" , ");
    Serial.print(index);
    Serial.print(" , ");  
    Serial.println(vuelta);
}
    


// */
  
    
