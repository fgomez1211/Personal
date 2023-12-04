//---------------------------------------------------
//Código para Articulacion 2
//Brazo Robótico SCORBOT-ER 9

//Declaración de señales del encoder
byte signalPin_1 =18; //Señal del Canal A del Encoder
byte signalPin_2 =19; //Señal indexx del Encoder
byte signalPin_3 =20; //Señal Home del Encoder


//Variables utilizadas para encontrar la POS Home en la rutina
volatile long int home=0;                     //Es = 1 si el encoder se encuentra sobre el sensor optico de home.
volatile long int indexx =0;                   //Es = 1 si el encoder da una rotación completa
volatile long int EstaEnHome = 0;             //Si EstaEnHome = 1, la articulación esta en Home.


//Variable que llevará el conteo de pasos el Encoder
volatile long int contador_A=0;             //Contador actual de pulsos del canal A del encoder
volatile long int contador_anterior=0;      //Contador actual de pulsos del canal A del encoder


//Declaración de señales PMW y Enables para el motor.
int enable1 = 2;      //Enable sentido antihorario
int enable2 = 3;      //Enable sentido horario
int pwm1 = 4;         //Activación sentido antihorario
int pwm2 = 5;         //Activación sentido horario
int EstoyBusy = 0;    //Indica si la articulación se encuentra ejecutando alguna función
int m = 1;            //Variable que indica el sentido de rotación. Default es horario, -1 es antihorario.


//Pasos del encoder y relación mecanica del eje
const int pasos_encoder=512;   //Pasos por cada rotación del encoder.
double relacion_eje_1=243.8;  //Relación mecánica de la articulación 2 del SCORBOT-ER9


//Pasos para una rotación completa (360°) de la articulacion
double relacion_encoder_1=pasos_encoder*relacion_eje_1;


//Factor para el cálculo de la posición instantánea
double pasos_1 = 360/relacion_encoder_1;    //Relación para convertir de pasos a grados.

//Grados de los comandos
double valorN = 0;
double Precision = 0.5; //Precisión de llegada = 0.5 grados se puede incrementar la presición disminuyendo este valor


//-------------------------------------------------------------------------------------------------------------------------
void setup(){

  Serial.begin(115200);
  Serial.println("Inicializando Controlador...");

  //Definición de señales del Encoder
  pinMode(signalPin_1, INPUT_PULLUP);
  pinMode(signalPin_2, INPUT_PULLUP);
  pinMode(signalPin_3, INPUT_PULLUP);

  //Definición de las variables del motor
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);

  //Se inicia sabiendo en que estado esta Home
  index = digitalRead(signalPin_2);  //se lee el estado actual de index
  home = digitalRead(signalPin_3); //Se lee el estado actual de home

  //Validacion cuando inicia el brazo, se encuentra en Home.
  if ((home==1) && (index==1)) {    //Ya esta en home
    EstaEnHome = 1; 
  } else {
    EstaEnHome = 0;
  }

  //Configuración de señales en pines interrupt.
  attachInterrupt(digitalPinToInterrupt(signalPin_1), enc_A, FALLING);
  attachInterrupt(digitalPinToInterrupt(signalPin_2), enc_index, RISING);
  attachInterrupt(digitalPinToInterrupt(signalPin_3), enc_home, CHANGE);  //Change porque se debe saber donde esta

  //Activa los Enable del driver, dejando los PWM  para enceder/apagar el motor.
  digitalWrite(enable1, HIGH); 
  digitalWrite(enable2, HIGH);
  digitalWrite(pwm2,LOW);
  digitalWrite(pwm1,LOW);

  //Si la articulación no se encuentra en Home, ejecuta la siguiente rutina.
  delay(2);
  Serial.println(" ");
  Serial.println(" ");

  //Esta sección inicia la rutina de Home al inicio del controlador.
  /*Serial.println("Buscando Home.....");
  if (EstaEnHome==0) {                       
     GoBottom();
     findhome();
     }else{
      Serial.println("POS Home Encontrada");
     }
  */

  Serial.println("Controlador listo para recibir comandos....");
  //Ahora que ya esta en Home, los contadores se deben colocar a cero
  contador_A=0;             
  contador_anterior = 0;
  m = 1;                        
  EstoyBusy = 0;            
}

//-------------------------------------------------------------------------------------------------------------------------


void loop(){

  String dataStr;                               //ALMACENA LOS EL DATO SERIAL RECIBIDO
  String comando = "";                          //ALMACENA LOS PRIMEROS CARACTERES QUE SERAN LA INSTRUCCION
  String valor = "";                            //ALMACENA EL VALOR NUMERICO RECIBIDO EN EL PUERTO SERIAL
  while (Serial.available()) {
    char incomingByte = Serial.read();
    dataStr += incomingByte;                   //CONCATENACION DE LOS CARACTERES RECIBIDOS.
    delay(2);
    }
  if (dataStr.length() > 0 ) {                 //EVALUACION EN EL MONITOR SERIAL
    if (EstoyBusy == 0){
      //Ya ha recibido un comando
      if (dataStr.length() >= 3) {            //SI EL COMANDO TIENE ALMENOS 3 CARACTERES
        comando = dataStr.substring(0,3);     //TOMA LOS CARACTERES PRIMEROS 3 CARACTERES DE dataStr
        //COMANDOS VALIDOS:
        //GOH = GO HOME
        //GOL###.#### = GO LEFT ###.#### GRADOS
        //GOR###.#### = GO RIGHT ###.#### GRADOS
        //REP = RETURN POSITION IN DEGREES
//----------------------------------------------------------------------------------------------------------------------        
        if (comando=="GOH") {                 //SI EL COMANDO RECIBIDO ES GOH
          EstoyBusy = 1;                      //Esta ejecutando una acción
          home = digitalRead(signalPin_3);    //Se lee el estado actual de home
          index = digitalRead(signalPin_2);   //se lee el estado actual de index
          if ((home==1) && (index==1)) {      //Si ambas señales están en 1, el brazo ya se encuentra en Home
            //ya esta en home
            EstaEnHome = 1;
            contador_A = 0;
            contador_anterior = 0;
          } else {
            EstaEnHome = 0;
            }
            if (EstaEnHome == 0) {  
                GoBottom();            //Si no, entonces ejecuta findhome() y luego envía el comando SiLoHizo
                findhome();
                SiLoHizo();
                }
          dataStr = "";                       //Reinicio de variables
          comando = "";
          valor = "";
          valorN = 0;
          EstoyBusy = 0;
        } else {
//----------------------------------------------------------------------------------------------------------------------
              if (comando == "GOL") {                   //SI EL COMANDO RECIBIDO ES GOL
                EstoyBusy = 1;                          //Esta ejecutando una acción
                valor = dataStr.substring(3);           //ALMACENA LOS CARACTERES EN VALOR A PARTIR DEL TERCERO
                valorN = valor.toDouble()*(-1);         //Se pasa a negativo porque va a la izquierda
                if ((valorN>-169) && (valorN<=0)) {     //Valor válido, si puede ejecutar el comando
                  GoAngulo();
                } else {
                  NoLoHizo();
                  }
                dataStr = "";                           //Reinicio de variables
                comando = "";
                valor = "";
                valorN = 0;
                EstoyBusy = 0;
              } else {
//----------------------------------------------------------------------------------------------------------------------
                    if (comando == "GOR") {                 //SI EL COMANDO RECIBIDO ES GOR
                      EstoyBusy = 1;                        //Esta ejecutando una acción
                      valor = dataStr.substring(3);         //ALMACENA LOS CARACTERES EN VALOR A PARTIR DEL TERCERO
                      valorN = valor.toDouble();            //Se deja positivo porque va a la derecha
                      if ((valorN<115) && (valorN>=0)) {    //Valor válido, si puede ejecutar el comando
                        GoAngulo();
                      } else {
                        NoLoHizo();
                      }
                      dataStr = "";                         //Reinicio de variables
                      comando = "";
                      valor = "";
                      valorN = 0;
                      EstoyBusy = 0;
                    } else {
//----------------------------------------------------------------------------------------------------------------------              
                          if (comando == "REP") {           //SI EL COMANDO RECIBIDO ES REP
                            EstoyBusy=1;                    //Esta ejecutando una acción
                            MandePos();                     //EJECUTA FUNCION MandePos()
                            dataStr = "";                   //Reinicio de variables
                            comando = "";
                            valor = "";
                            valorN = 0;
                            EstoyBusy = 0;
                          } else {
                                dataStr = "";                //Reinicio de variables
                                comando = "";
                                valor = "";
                                valorN = 0;
                                EstoyBusy = 0;
                            }
                      }
                }
          }
      }
    }
  }
}

//-------------------------------------------------------------------------------------------------------------------------
//FUNCION PARA ENVIAR LA POSICION FINAL AL MONITOR SERIAL
void MandePos() {
  Serial.print("Posición Actual: ");
  Serial.print(pasos_1*contador_A);
  Serial.println("°");
}
//FUNCION PARA INDICAR QUE SI HA EJECTUADO EL COMANDO
void SiLoHizo() {
  Serial.println("OK");
}
//FUNCION PARA INDICAR QUE NO EJECUTO EL COMANDO
void NoLoHizo() {
  Serial.println("FAIL");
}
//-------------------------------------------------------------------------------------------------------------------------
//FUNCION PARA MOVER LA ARTICULACION SEGUN VALOR INGRESADO EN EL MONITOR SERIAL
//-------------------------------------------------------------------------------------------------------------------------
void GoAngulo() {
  //Para ir a la izquierda o a la derecha antes de encender el motor, 
  //hay que saber donde está para moverse al lugar hacia ese lugar
  double PrecisionActual = 0;
  double PrecisionInicial = 0;
  double DondeEstoy = pasos_1*contador_A;

  PrecisionInicial = abs(DondeEstoy - valorN);
  PrecisionActual = PrecisionInicial;

  if (DondeEstoy < valorN) { //debe ir a la DEBE IR A LA DERECHA
    m = 1;
  } else { //DEBE IR A LA IZQUIERDA
    m = -1;
  }

  while ((PrecisionActual > Precision) && (PrecisionActual<=PrecisionInicial)) {
    if(m==1){
      digitalWrite(pwm2,LOW); 
      digitalWrite(pwm1,HIGH); //SE MUEVE A LA IZQUIERDA
    }else{
      digitalWrite(pwm1,LOW); 
      digitalWrite(pwm2,HIGH); //SE MUEVE A LA DERECHA
    }
    PrecisionActual = abs((pasos_1*contador_A) - valorN);
    Serial.println(pasos_1*contador_A);
  }
  digitalWrite(pwm2,LOW);                    //PONE EN BAJO LA SEÑAL DE LOS MOTORES
  digitalWrite(pwm1,LOW);
  Serial.print("Posición Alcanzada: ");
  Serial.println(pasos_1*contador_A);
}
//-------------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------------
//FUNCIONES PARA LOS PINES INTERRUPT

void enc_A(){                           //Función para el conteo de pulsos provenientes del canal B del Encoder
  if (m==1) {
    contador_A++;
  } else {
    contador_A--;
  }
}

void enc_index(){                      //Función para el conteo de pulsos provenientes del Index Pulse del Encoder
    index = 1;
  }

void enc_home(){
    home = digitalRead(signalPin_3);   //Función para el conteo de pulsos provenientes del Home del Encoder
    if (home==1) {
      index = 0;
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
  m=1;
  while (home != 1 && vuelta !=1) {
    delay(50);
    //Activa el motor en una direccion hasta que encuentre home, si no lo encuentra activa el motor en la direccion inversa
    if(m==1){
      digitalWrite(pwm2,LOW); 
      digitalWrite(pwm1,HIGH); //vaya a la derecha
    }else{
      digitalWrite(pwm1,LOW); 
      digitalWrite(pwm2,HIGH); //vaya a la izquierda
    }
    //Si el contador sigue estando en el mismo lugar, el motor no se esta moviendo,
    //Si lo hace mas de cinco veces debe cambiar de direccion
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
      Serial.println("POS Home Encontrada");
    }
  }
  contador_anterior= 0;
  contador_A = 0;
}

//-------------------------------------------------------------------------------------------------------------------------
//La Función GoBottom se ejecuta antes que la función GoHome. Eso se debe a que Home tiene 2 posiciones,
//y para evitar que el posicionamiento del robot cambie, se corre una rutina para que el motor se mueva hacia un extremo
//y cuando este llegue al extremo y retorne, siempre econtrará la misma posición Home.
//La función GoBottom hace que la articulación se mueve hacia un extremo. 
//-------------------------------------------------------------------------------------------------------------------------
void GoBottom() {
  digitalWrite(pwm2,LOW);             //Se deshabilita el movimiento en ambos sentidos.
  digitalWrite(pwm1,LOW);
  int retry=0;
  int conteocero = 0;
  contador_anterior= 0;
  contador_A = 0;    
  m=1;
  while (retry < 10) {
    delay(100);
    digitalWrite(pwm1,LOW);           //habilitar pwm2 hará que se mueva en sentido horario
    digitalWrite(pwm2,HIGH);          //Habilitar pwm2 hará que se mueva en sentido antihorario
    if(contador_A==contador_anterior && contador_A!=0){
      retry++;
    }
    contador_anterior = contador_A;
  }
  digitalWrite(pwm2,LOW);             //Se deshabilita el movimiento en ambos sentidos para iniciar GoHome
  digitalWrite(pwm1,LOW); 
}
