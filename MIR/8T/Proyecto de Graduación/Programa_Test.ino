

const byte signalPin =2;
const byte signalPin_2 =3;

int contador_A=0;
int contador_B=0;

//PMW Motores y Enables

int pwm1 = 8;
int pwm2 = 9;
int enable1 = 10;
int enable2 = 11;


//Pasos del encoder y relaciones entre el encoder y los engranajes.
const int pasos_encoder=30;
const int relacion_eje_1=214;
const int relacion_eje_2=244;
const int relacion_eje_3=213;
const int relacion_eje_4=180;
const int relacion_eje_5=180;


//Pasos para una rotación completa de cada articulacion
float relacion_encoder_1=pasos_encoder*relacion_eje_1;
float relacion_encoder_2=pasos_encoder*relacion_eje_2;
float relacion_encoder_3=pasos_encoder*relacion_eje_3;
float relacion_encoder_4=pasos_encoder*relacion_eje_4;
float relacion_encoder_5=pasos_encoder*relacion_eje_5;


//Coordenadas de prueba en grados
const int  grados_eslabon_1 =3;
const int  grados_eslabon_2 =30;
const int  grados_eslabon_3 =30;
const int  grados_eslabon_4 =30;
const int  grados_eslabon_5 =30;



//Coordenadas en pasos
float pasos_1 = grados_eslabon_1 * relacion_encoder_1;
float pasos_2 = grados_eslabon_2 * relacion_encoder_2;
float pasos_3 = grados_eslabon_3 * relacion_encoder_3;
float pasos_4 = grados_eslabon_4 * relacion_encoder_4;
float pasos_5 = grados_eslabon_5 * relacion_encoder_5;





void setup(){
  pinMode(signalPin, INPUT_PULLUP);
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  digitalWrite(enable1, HIGH); 
  digitalWrite(enable2, HIGH);
  digitalWrite(pwm1, LOW);
  digitalWrite(pwm2,LOW);

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(signalPin), enc_A, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(buttonPin), enc_index, FALLING);
  //attachInterrupt(digitalPinToInterrupt(buttonPin_2), enc_home, CHANGE);  

}


void loop(){
  if (contador_A < pasos_1){
    digitalWrite(pwm1,HIGH);
    Serial.println(contador_A);
    Serial.println(pasos_1);
  }
    else{
      digitalWrite(pwm1,LOW);
    }
}


void enc_A(){
  if (digitalRead(signalPin) == LOW){
    contador_A++;
  }
}

void enc_index(){
  if (digitalRead(signalPin) == LOW){
    contador_A++;
  }
}


// */
  
    
