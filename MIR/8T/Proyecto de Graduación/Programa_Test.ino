
//--------------------------------------------------------------------------------------------------------------------------------------------

//Declaración de señales del encoder
byte signalPin_1 =18; //Señal del Canal A del Encoder
byte signalPin_2 =19; //Señal Index del Encoder
byte signalPin_3 =20; //Señal Home del Encoder

//Variable para indicar la posición actual de la articulación en grados.
byte posicion_actual=0;


//Variables utilizadas para encontrar la POS Home en la rutina
volatile long int home=0;
volatile long int index =0;
volatile long int contador_anterior=0;


//Variable que llevará el conteo de pasos el Encoder
volatile long int contador_A=0;
//volatile long int contador_B=0;


//Declaración de señales PMW y Enables para el motor.
int pwm1 = 4; //Activación sentido antihorario
int pwm2 = 5; //Activación sentido horario
int enable1 = 2;  //Enable sentido antihorario
int enable2 = 3;  //Enable sentido horario


//Pasos del encoder, relaciones entre el encoder y los engranajes y definición de posición inicial.
const int pasos_encoder=512;
double relacion_articulacion_1=214.13;
double Posicion_actual=0;
double Nueva_posicion=0;


//Pasos para una rotación completa de cada articulacion
double relacion_encoder_1=pasos_encoder*relacion_articulacion_1;

//Coordenadas de prueba en grados
double  grados_eslabon_1 =0;

//Coordenadas en paso
double pasos_1 = 0;

int enable_positivo = false;
int enable_negativo = false;
double pasos_1_positivo = 0;
double pasos_1_negativo = 0;

//--------------------------------------------------------------------------------------------------------------------------------------------

void setup(){

  Serial.begin(115200);

  //Definición de señales del Encoder
  pinMode(signalPin_1, INPUT_PULLUP);
  pinMode(signalPin_2, INPUT_PULLUP);
  pinMode(signalPin_3, INPUT_PULLUP);

  //Definición de las variables del motor
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);

  //Configuración de señales en pines interrupt.
  attachInterrupt(digitalPinToInterrupt(signalPin_1), enc_A, FALLING);
  attachInterrupt(digitalPinToInterrupt(signalPin_2), enc_index, FALLING);
  attachInterrupt(digitalPinToInterrupt(signalPin_3), enc_home, FALLING);

  //Activa los Enable del driver, dejando los PWM  para enceder/apagar el motor.
  digitalWrite(enable1, HIGH); 
  digitalWrite(enable2, HIGH);

  //Se apagan ambos motores  
  digitalWrite(pwm2,LOW);
  digitalWrite(pwm1,LOW);

  //Impresión de etiquetas en monitor serial.
  Serial.println("Iniciando rutina...");
  delay(10);
  Serial.println("Buscando POS Home...");
  Serial.println(grados_eslabon_1);

  //Rutina para encontrar la POS Home. 
  findhome();
  Serial.println("POS Home Encontrada!");
  digitalWrite(pwm2,LOW); //Se apaga el motor para evitar que se mueva de su posición home.
  digitalWrite(pwm1,LOW);
  contador_A=0;   //Reset del contador de pasos del encoder. Esta variable se utilizara para el movimiento de la articulación.
  delay(1000);

}

//--------------------------------------------------------------------------------------------------------------------------------------------

void loop(){

//--------------------------------------------------------------------------------------------------------------------------------------------
// INICIO DE COMUNICACION SERIAL
  if (Serial.available() > 0) {   // Revisa si hay un valor para leer en el puerto serial.
    grados_eslabon_1 = Serial.parseInt(); //Leer los grados desde el puerto serial.
    delay(2000);
    }

    if(grados_eslabon_1>=0){
      pasos_1_positivo = (grados_eslabon_1/360) * relacion_encoder_1; //Calculo de pasos a moverse según el valor leido en el puerto serial
      Serial.print(pasos_1_positivo);
      Serial.print(" , ");
      Serial.println(contador_A);
      enable_positivo = true;
    }

    if(grados_eslabon_1<0){
      grados_eslabon_1 = grados_eslabon_1*(-1);
      pasos_1_negativo = (grados_eslabon_1/360) * relacion_encoder_1;
      Serial.print("Moverse ");
      Serial.print(pasos_1_negativo);
      Serial.print(" , ");
      Serial.println(contador_A);
      enable_negativo = true;
      }

//--------------------------------------------------------------------------------------------------------------------------------------------
// SI EL VALOR INGRESADO EN EL SERIAL ES POSITIVO
  if(enable_positivo==true){
    if(grados_eslabon_1 >0){
      if (contador_A< pasos_1_positivo){
          digitalWrite(pwm1,LOW);
          digitalWrite(pwm2, HIGH);
          Serial.print(contador_A);
          Serial.print(" , ");
          Serial.println(pasos_1);
          }
          else{
            enable_positivo=false;
            pasos_1=0;
            contador_A=0;
            digitalWrite(pwm1,LOW);
            digitalWrite(pwm2, LOW);
            Serial.println("Posicion positiva alcanzada, esperando instruccion... ");
            delay(1000);
            }
    }
  }


//--------------------------------------------------------------------------------------------------------------------------------------------
// SI EL VALOR INGRESADO EN EL SERIAL ES NEGATIVO
  if(enable_negativo==true){
    if(grados_eslabon_1 < 0){
      if (contador_A < pasos_1_negativo){
          digitalWrite(pwm2,LOW);
          digitalWrite(pwm1, HIGH);
          Serial.print(contador_A);
          Serial.print(" , ");
          Serial.println(pasos_1);
          }
          else{
            enable_negativo = false;
            pasos_1=0;
            contador_A=0;
            digitalWrite(pwm1,LOW);
            digitalWrite(pwm2, LOW);
            Serial.println("Posicion negativa alcanzada, esperando instruccion... ");
            delay(1000);
            }            
      }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------

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


//--------------------------------------------------------------------------------------------------------------------------------------------

// FUNCION: findhome(). Ejecuta una rutina para encontrar la POS Home de la articulación.
// Para encontrar la POS Home la articulación debe de encontrar un pulso del pin Home. 
// Mientras detecta el pulso, debe encontrar un siguiente pulso en Index.
// Cuando el brazo llega a un extremo de su rotación y no detecta el POS Home, 
// este valida si tiene la misma posición que la anterior
// si esto sucede 5 veces, la articulación se movera hacia el otro sentido para intentar buscar POS Home.

//--------------------------------------------------------------------------------------------------------------------------------------------


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
  
    
