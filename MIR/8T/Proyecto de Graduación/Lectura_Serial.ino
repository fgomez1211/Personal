

String readString;

void setup() {
  Serial.begin(115200);
}

void loop() {

  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the String readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }

  if (readString.length() >0) {
    char comando = readString.charAt(0);
    readString.remove(0,1);

    double valor = readString.toDouble();
    Serial.println(comando);
    Serial.println(valor);
    readString="";
  } 
}