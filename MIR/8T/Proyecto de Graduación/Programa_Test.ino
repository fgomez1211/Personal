

const byte ledPin = 13;
const byte buttonPin =2;
const byte buttonPin_2 =3;
int motor = 7;
int contador_A=0;
int contador_B=0;

//Pasos del encoder y relaciones entre el encoder y los engranajes.
int pasos_encoder=512;
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
int coordenada_x =30;
int coordenada_y =20;
int coordenada_z =10;




void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(motor,OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(buttonPin), enc_A, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPin_2), enc_B, CHANGE);
}


void loop(){
  if (contador_A <coordenada_x){
    digitalWrite(7,HIGH);
    Serial.println(contador_A);
  }
    else{
      digitalWrite(7,LOW);
    }


  if (contador_B <coordenada_y){
    digitalWrite(8,HIGH);
    Serial.println(contador_B);
  }
    else{
      digitalWrite(8,LOW);
    }
}




void enc_A(){
  if (digitalRead(buttonPin) == LOW){
    contador_A++;
  }
}


// /*
void enc_B(){
  if (digitalRead(buttonPin) == LOW){
    contador_B++;
  }
}
// */
