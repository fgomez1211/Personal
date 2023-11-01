

const byte ledPin = 13;
const byte buttonPin =2;
int counter=0;


volatile bool toogleState =false;


void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(buttonPin), checkSwitch, FALLING);
}

void loop(){
  Serial.println("Delay Started");
  delay(5000);
  Serial.println("Delay Finished");
  Serial.println("..............");
}

void checkSwitch(){
  if (digitalRead(buttonPin) == LOW){
    toogleState = !toogleState;
    digitalWrite(ledPin, toogleState);
  }
}
