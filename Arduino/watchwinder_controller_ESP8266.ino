const int motorPin = D1;   // PWM-enabled pin for motor control, change to your desired pin
const int potPin = A0;    // analog input pin for potentiometer
const int switchPin = D2; // digital input pin for on/off switch, change to your desired pin
int speed = 0;            // initial motor speed
int potValue = 0;         // potentiometer reading
bool isSwitchOn = false;  // flag to track switch status
bool isMotorRunning = false;   // flag to track motor operation status

unsigned long lastSwitchTime = 0;   // last time the switch was toggled
const unsigned long debounceDelay = 50;   // debounce delay in milliseconds

unsigned long motorStartTime = 0;   // start time of motor operation
unsigned long motorRunTime = 60 * 60 * 1000;   // motor run time in milliseconds (60 minutes)
unsigned long motorStopTime = motorStartTime + motorRunTime;   // stop time of motor operation
unsigned long motorCooldownTime = 120 * 60 * 1000;   // motor cooldown time in milliseconds (120 minutes)

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(switchPin, INPUT_PULLUP);
}

void loop() {
  // check if the switch has been toggled
  if (millis() - lastSwitchTime >= debounceDelay) {
    if (digitalRead(switchPin) == LOW) {
      isSwitchOn = !isSwitchOn;
    }
    lastSwitchTime = millis();
  }

  // check if the motor should be running
  if (isSwitchOn && millis() >= motorStopTime && isMotorRunning) {
    // stop the motor if the run time has elapsed
    analogWrite(motorPin, 0);
    isMotorRunning = false;
    motorStartTime = millis();
    motorStopTime = motorStartTime + motorCooldownTime;
  } else if (isSwitchOn && millis() >= motorStartTime && !isMotorRunning) {
    // start the motor if the cooldown time has elapsed
    potValue = analogRead(potPin);
    speed = map(potValue, 0, 1023, 0, 255);
    analogWrite(motorPin, speed);
    isMotorRunning = true;
    motorStartTime = millis();
    motorStopTime = motorStartTime + motorRunTime;
  } else if (!isSwitchOn && isMotorRunning) {
    // stop the motor if the switch is turned off
    analogWrite(motorPin, 0);
    isMotorRunning = false;
  }
}
