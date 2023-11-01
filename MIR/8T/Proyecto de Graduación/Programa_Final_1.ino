

const byte ledPin = 13;
const byte buttonPin =2;
int motor = 7;
int counter=0;
int relacion_encoder=512;




volatile bool toogleState =false;


void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(motor,OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(buttonPin), checkSwitch, CHANGE);
}


void loop(){
  if (counter <5){
    digitalWrite(7,HIGH);
    Serial.println(counter);
  }
    else{
      digitalWrite(7,LOW);
    }
}



void checkSwitch(){
  if (digitalRead(buttonPin) == LOW){
    counter++;
  }
}

  
    
