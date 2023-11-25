
//Señales del Encoder
byte signalPin =18;
byte signalPin_2 =19;
byte signalPin_3 =20;
byte posicion_actual=0;


volatile long int home=0;
volatile long int index =0;
volatile long int EstaEnHome = 0;


volatile long int contador_A=0; //cuenta pulsos
volatile long int contador_anterior=0;


//PMW Motores y Enables
int pwm1 = 4;
int pwm2 = 5;
int enable1 = 2;
int enable2 = 3;
int EstoyBusy = 0;             //Variable que indica si la articulación se encuentra ejecutando alguna función
int m = 1;                     //El motor inicia a la derecha, si se desea a izquierda se pone cualquier otro valor


//Pasos del encoder y relaciones mecanica del eje
const int pasos_encoder=512;
double relacion_eje_1=214.13;  //CAMBIAR ESTE VALOR PARA CADA ARTICULACION


//Pasos para una rotación completa (360°) de la articulacion
double relacion_encoder_1=pasos_encoder*relacion_eje_1;


//Coordenadas en pasos
double pasos_1 = 360/109634.56;


//Grados de los comandos
double valorN = 0;
double Precision = 0.5; //Precisión de llegada = 0.5 grados se puede incrementar la presición disminuyendo este valor


//-------------------------------------------------------------------------------------------------------------------------
void setup(){

  Serial.begin(115200);

  //Condifuracion de las señales del Encoder
  pinMode(signalPin, INPUT_PULLUP);
  pinMode(signalPin_2, INPUT_PULLUP);
  pinMode(signalPin_3, INPUT_PULLUP);

  //Declaración de las variables del encoder
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);

  //Se inicia sabiendo en que estado esta Home
  home = digitalRead(signalPin_3); //Se lee el estado actual de home
  index = digitalRead(signalPin_2);  //se lee el estado actual de index

  //Validacion si cuando inicia el brazo, se encuentra en Home.
  if ((home==1) && (index==1)) {    //Ya esta en home
    EstaEnHome = 1; 
  } else {
    EstaEnHome = 0;
  }

  //Declaración de pines interrupt
  attachInterrupt(digitalPinToInterrupt(signalPin), enc_A, FALLING);
  attachInterrupt(digitalPinToInterrupt(signalPin_2), enc_index, CHANGE);
  attachInterrupt(digitalPinToInterrupt(signalPin_3), enc_home, CHANGE);  //Change porque se debe saber donde esta

  //Activa los Enable del driver, dejando los PWM  para enceder/apagar el motor.
  digitalWrite(enable1, HIGH); 
  digitalWrite(enable2, HIGH);
  digitalWrite(pwm2,LOW);
  digitalWrite(pwm1,LOW);

  //Si la articulación no se encuentra en Home, ejecuta la siguiente rutina.
  if (EstaEnHome==0) {
     findhome();
  }

  //Ahora ya esta en home Los contadores se deben colocar a cero
  contador_A=0;
  contador_anterior = 0;
  m = 1; //se pone motor a la derecha por default
  EstoyBusy = 0;
}

//-------------------------------------------------------------------------------------------------------------------------


void loop(){
  //datos para puerto serial
  int incomingByte = 0; // for incoming serial data
  String dataStr = "";
  String comando = "";
  String valor = "";
  
  if (Serial.available() != 0 ) {                 //EVALUACION EN EL MONITOR SERIAL
    if (EstoyBusy == 0){
      //Leer un byte
      incomingByte = Serial.read();
      if (incomingByte!=0){
        if (incomingByte!=13) {                   //MIENTRAS NO SEA CR
           //Ya ha recibido un comando
           if (dataStr.length() >= 3) {           //SI EL COMANDO TIENE ALMENOS 4 CARACTERES
            comando = dataStr.substring(0,3);     //TOMA LOS CARACTERES 0,1,2

            //Comandos válidos
            //GOH = Go Home
            //GOL###.#### = Go Left ###.#### grados
            //GOR###.#### = Go Right ###.#### grados
            //REP = Return Position in Degrees


            if (comando=='GOH') {                 //SI EL COMANDO RECIBIDO ES GOH
              //vaya a home
              EstoyBusy = 1;
              home = digitalRead(signalPin_3);    //Se lee el estado actual de home
              index = digitalRead(signalPin_2);  //se lee el estado actual de index
              if ((home==1) && (index==1)) {
                //ya esta en home
                EstaEnHome = 1;
                contador_A = 0;
                contador_anterior = 0;
              } else {
                EstaEnHome = 0;
              }
              if (EstaEnHome == 0) {
                findhome();
                SiLoHizo();
              }
              dataStr = "";
              comando = "";
              valor = "";
              valorN = 0;
              EstoyBusy = 0;
            } else {


              if (comando == 'GOL') {       //SI EL COMANDO RECIBIDO ES GOL
                //vaya a la izquierda los siguientes digitos son el angulo
                EstoyBusy = 1;
                valor = dataStr.substring(3);
                valorN = valor.toDouble()*(-1); //se pasa a negativo porque va hacia la izquierda
                if ((valorN>-130) && (valorN<=0)) {
                  // valor válido, si puede ejecutar el comando
                  GoAngulo();
                } else {
                  NoLoHizo();
                }
                dataStr = "";
                comando = "";
                valor = "";
                valorN = 0;
                EstoyBusy = 0;
              } else {


                if (comando == 'GOR') {     //SI EL COMANDO RECIBIDO ES GOR
                  //vaya a la derecha los siguientes digitos son el angulo
                  EstoyBusy = 1;
                  valor = dataStr.substring(3);
                  valorN = valor.toDouble(); //se deja positivo porque va a la derecha
                  if ((valorN<130) && (valorN>=0)) {
                    // valor válido, si puede ejecutar el comando
                    GoAngulo();
                  } else {
                    NoLoHizo();
                  }
                  dataStr = "";
                  comando = "";
                  valor = "";
                  valorN = 0;
                  EstoyBusy = 0;
                } else {


                  if (comando == 'REP') {
                    // Deme posición actual (positivo derecha, negativo izquierda)
                    EstoyBusy=1;
                    MandePos();
                    dataStr = "";
                    comando = "";
                    valor = "";
                    valorN = 0;
                    EstoyBusy = 0;
                  } else {
                    dataStr = "";
                    comando = "";
                    valor = "";
                    valorN = 0;
                    EstoyBusy = 0;
                  }
                }
              }
            }
           }
          } else {
          if (incomingByte!=10) {
            dataStr = dataStr + incomingByte;
          }
        }  
      }
    }//Termina, EstoyBusy != 0.
  }
}

//-------------------------------------------------------------------------------------------------------------------------
//FUNCION PARA ENVIAR LA POSICION FINAL AL MONITOR SERIAL
//-------------------------------------------------------------------------------------------------------------------------
void MandePos() {
  Serial.println(pasos_1*contador_A);
}
//-------------------------------------------------------------------------------------------------------------------------
//FUNCION PARA INDICAR QUE SI HA EJECTUADO EL COMANDO
//-------------------------------------------------------------------------------------------------------------------------
void SiLoHizo() {
  Serial.println("OK");
}
//-------------------------------------------------------------------------------------------------------------------------
//FUNCION PARA INDICAR QUE NO HA EJECTUADO EL COMANDO
//-------------------------------------------------------------------------------------------------------------------------
void NoLoHizo() {
  Serial.println("FAIL");
}


//-------------------------------------------------------------------------------------------------------------------------
//FUNCION PARA MOVER LA ARTICULACION SEGUN EL COMANDO ENVIADO
//-------------------------------------------------------------------------------------------------------------------------
void GoAngulo() {
  //para ir a la izquierda o a la derecha antes de encender el motor saber donde estoy para moverme hacia ese lugar
  double PrecisionActual = 0;
  double PrecisionInicial = 0;
  double DondeEstoy = pasos_1*contador_A;
  PrecisionInicial = abs(DondeEstoy - valorN);
  PrecisionActual = PrecisionInicial;
  if (DondeEstoy < valorN) { //debe ir a la derecha
    m = 1;
  } else { //debe ir a la izquierda
    m = -1;
  }

  while ((PrecisionActual > Precision) && (PrecisionActual<=PrecisionInicial)) {
    if(m==1){
      digitalWrite(pwm2,LOW); 
      digitalWrite(pwm1,HIGH); //vaya a la derecha
    }else{
      digitalWrite(pwm1,LOW); 
      digitalWrite(pwm2,HIGH); //vaya a la izquierda
    }
    PrecisionActual = abs((pasos_1*contador_A) - valorN);
  }
  //se salio, o porque llego o porque se paso
  digitalWrite(pwm2,LOW);
  digitalWrite(pwm1,LOW);
  Serial.print(pasos_1*contador_A);  //envie la posicion en la que se quedo
}
//-------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------
//FUNCIONES PARA LOS PINES INTERRUPT
//-------------------------------------------------------------------------------------------------------------------------
void enc_A(){
  if (m==1) {
    contador_A++;
  } else {
    contador_A--;
  }
}


void enc_index(){
   index=digitalRead(signalPin_2);
}


void enc_home(){
    home = digitalRead(signalPin_3);
    if (home==1) {
       index=digitalRead(signalPin_2);
       if ((home==1) && (index==1)) {
        EstaEnHome=1;
       }
    }
}
//-------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------------
//FUNCION PARA ENCONTRA LA POSICION HOME
//-------------------------------------------------------------------------------------------------------------------------
void findhome(){
  int vuelta = -1;
  int retry=0;
  int conteocero = 0;
  int yaenfinal = -1;
  //asegurar que los motores no se estan moviendo
  digitalWrite(pwm2,LOW);
  digitalWrite(pwm1,LOW);
  home = digitalRead(signalPin_3);
  index=digitalRead(signalPin_2);
  if ((home==1) && (index==1)) {
    vuelta = 1;
    EstaEnHome = 1;
    contador_anterior= 0;
    contador_A = 0;    
  }
  else {
    contador_anterior=-999;
    contador_A=0;
  }
  
  while (home != 1 && vuelta !=1) {
    delay(100);
    //active motor en una direccion hasta que encuentre home, si no lo encuentra active el motor en la direccion inversa
    if(m==1){
      digitalWrite(pwm2,LOW); 
      digitalWrite(pwm1,HIGH); //vaya a la derecha
    }else{
      digitalWrite(pwm1,LOW); 
      digitalWrite(pwm2,HIGH); //vaya a la izquierda
    }
    // si el contador sigue estando en el mismo lugar, el motor no se esta moviendo, si lo hace mas de cinco veces debe cambiar de direccion
    if(contador_A==contador_anterior && contador_A!=0){
      retry++;
    }
    if ((contador_anterior==0) && (contador_A==0) && (m==1)) {
      conteocero++;
    }
    if (conteocero>10) {
      //ya paso once veces por aqui, quiere decir que inicio en un extremo y debe cambiar dirección
      //Esto solo puede pasar una vez porque arranco en el extremo derecho, y debe buscar home a la izquierda, 
      //si no encuentra home a la izquierda regresará otra vez por eso se resetea conteocero, 
      //para que cuando regrese, vuelva a iniciar si no encuentra el final
      m = -1;
      conteocero = 0;
    }
    contador_anterior=contador_A;
    if(retry>5){
      if(m==1){
        m=-1;
      }else{
      m=1;
      }
      retry=0;
      contador_A=0;
      contador_anterior=0;
      index = digitalRead(signalPin_2);
      home = digitalRead(signalPin_3);
    }
    
    if(home>0 && index>0){
      digitalWrite(pwm1,LOW);
      digitalWrite(pwm2,LOW);
      vuelta=1;
      EstaEnHome = 1;
    }
  }
}
    

    