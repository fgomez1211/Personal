
int signal = 3;  
int dutty_cicle=10;


void setup() {
  pinMode(signal, OUTPUT);
}

void loop() {
  digitalWrite(signal,HIGH);
  delay(dutty_cicle);
  digitalWrite(signal,LOW);
  delay(dutty_cicle);
  }
