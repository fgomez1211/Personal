

byte signalPin =18;
//byte signalPin_2 =3;


volatile long int contador_A=0;
volatile long int contador_B=0;

//PMW Motores y Enables

int pwm1 = 4;
int pwm2 = 5;
int enable1 = 2;
int enable2 = 3;


//Pasos del encoder y relaciones entre el encoder y los engranajes.
const int pasos_encoder=512;
double relacion_eje_1=214.13;


//Pasos para una rotación completa de cada articulacion
double relacion_encoder_1=pasos_encoder*relacion_eje_1;

//Coordenadas de prueba en grados
double  grados_eslabon_1 =30;

//Coordenadas en pasos
double pasos_1 = (grados_eslabon_1/360) * relacion_encoder_1;


void setup(){
  Serial.begin(9600);

  //Señal del Encoder
  pinMode(signalPin, INPUT_PULLUP);


  //Declaración de las variables del encoder
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);



  attachInterrupt(digitalPinToInterrupt(signalPin), enc_A, FALLING);
  //attachInterrupt(digitalPinToInterrupt(buttonPin), enc_index, FALLING);
  //attachInterrupt(digitalPinToInterrupt(buttonPin_2), enc_home, CHANGE); 

  //Activa los Enable del driver, dejando los PWM  para enceder/apagar el motor.
  digitalWrite(enable1, HIGH); 
  digitalWrite(enable2, HIGH);
  digitalWrite(pwm2,LOW);e

}


void loop(){


  if (contador_A < pasos_1){
    digitalWrite(pwm2,HIGH);
    Serial.println(contador_A);
    Serial.println(pasos_1);
  }
    else{
      digitalWrite(pwm2,LOW);
      Serial.println("Motor Apagado");
    }
}


void enc_A(){
    contador_A++;
}



//void enc_index(){
  //if (digitalRead(signalPin) == LOW){
    //contador_A++;
  //}
//}


// */
  
    
