const int motorPin = 9;   // PWM-enabled pin for motor control, change to your desired pin
const int potPin = A0;    // analog input pin for potentiometer
int speed = 0;            // initial motor speed
int potValue = 0;         // potentiometer reading

const int switchPin = 2;    // digital input pin for on/off switch
bool switchState = false;   // current state of on/off switch
bool lastSwitchState = false;   // previous state of on/off switch
unsigned long lastDebounceTime = 0;   // last time the switch was toggled
const unsigned long debounceDelay = 50;   // debounce delay in milliseconds

unsigned long motorStartTime = 0;   // start time of motor operation
unsigned long motorRunTime = 60 * 60 * 1000;   // motor run time in milliseconds (60 minutes)
unsigned long motorStopTime = motorStartTime + motorRunTime;   // stop time of motor operation
unsigned long motorCooldownTime = 120 * 60 * 1000;   // motor cooldown time in milliseconds (120 minutes)

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(potPin, INPUT);

  pinMode(switchPin, INPUT_PULLUP);   // set switch pin to INPUT mode with pull-up resistor enabled
}

void loop() {
  // read and debounce switch input
  bool reading = digitalRead(switchPin);
  if (reading != lastSwitchState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != switchState) {
      switchState = reading;
      if (switchState) {
        // toggle motor state when switch is pressed
        if (motorStopTime <= millis()) {
          motorStartTime = millis();
          motorStopTime = motorStartTime + motorRunTime;
        } else {
          analogWrite(motorPin, 0);
          motorStartTime = 0;
          motorStopTime = 0;
        }
      }
    }
  }
  lastSwitchState = reading;

  // run motor if within run time and switch is on
  if (motorStartTime > 0 && millis() >= motorStartTime && millis() < motorStopTime) {
    potValue = analogRead(potPin);
    speed = map(potValue, 0, 1023, 0, 255);
    analogWrite(motorPin, speed);
  } else {
    // stop motor if outside of run time or switch is off
    analogWrite(motorPin, 0);
  }
}
