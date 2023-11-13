

const byte signalPin =2;
const byte signalPin_2 =3;

int motor = 7;
int contador_A=0;
int contador_B=0;

//PMW Motores y Enables
int pwm1 = 8;
int pwm2 = 9;
int enable1 = 10;
int enable2 = 11;


//Pasos del encoder y relaciones entre el encoder y los engranajes.
int pasos_encoder=10;
float relacion_eje_1=214.13;
float relacion_eje_2=243.8;
float relacion_eje_3=213.33;
float relacion_eje_4=180;
float relacion_eje_5=180;


//Pasos para una rotación completa de cada articulacion
float relacion_encoder_1=pasos_encoder*relacion_eje_1;
float relacion_encoder_2=pasos_encoder*relacion_eje_2;
float relacion_encoder_3=pasos_encoder*relacion_eje_3;
float relacion_encoder_4=pasos_encoder*relacion_eje_4;
float relacion_encoder_5=pasos_encoder*relacion_eje_5;


//Coordenadas de prueba en grados
int grados_eslabon_1 =3;
int grados_eslabon_2 =30;
int grados_eslabon_3 =30;
int grados_eslabon_4 =30;
int grados_eslabon_5 =30;



//Coordenadas en pasos
float pasos_1 = grados_eslabon_1 * relacion_encoder_1;
float pasos_2 = grados_eslabon_2 * relacion_encoder_2;
float pasos_3 = grados_eslabon_3 * relacion_encoder_3;
float pasos_4 = grados_eslabon_4 * relacion_encoder_4;
float pasos_5 = grados_eslabon_5 * relacion_encoder_5;





void setup(){
  pinMode(motor,OUTPUT);
  pinMode(signalPin, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(signalPin), enc_A, FALLING);
  attachInterrupt(digitalPinToInterrupt(signalPin_2), enc_B, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(buttonPin), enc_index, FALLING);
  //attachInterrupt(digitalPinToInterrupt(buttonPin_2), enc_home, CHANGE);
  digitalWrite(enable1, HIGH); 
  digitalWrite(enable2, HIGH);
}


void loop(){
  if (contador_A <pasos_1){
    digitalWrite(pwm1,HIGH);
    Serial.println(contador_A);
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

void enc_B(){
  if (digitalRead(signalPin_2) == LOW){
    contador_B++;
  }
}



// */
  
    
