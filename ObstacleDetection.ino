// Ultra Sound Modules
// Mod1: Straight

const int usMod1Echo_pin;
const int usMod1Trig_pin;

// Motor Pins - L298N Motor Interfacing Module
// Pin1: Left Motor
// Pin2: Right Motor
const int motor1Pin1;
const int motor1Pin2;
const int motor2Pin1;
const int motor2Pin2;

// Pin1  Pin2  Direction 
// 0     0     none
// 1     0     forward
// 0     1     reverse
// 1     1     none

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}


void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);

  delay(1000);

  stopMotors();
}


void goStraight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);

  delay(1000);

  stopMotors();
}


float getDistance(int usModEcho_pin, int usModTrig_pin) {
  // Clears Ultrasound module
  digitalWrite(usModTrig_pin, LOW);
  delayMicroseconds(2);

  //Send Pulse
  digitalWrite(usModTrig_pin, HIGH);
  delayMicroseconds(10);

  digitalWrite(usModTrig_pin, LOW);

  float duration = pulseIn(usModEcho_pin, HIGH); // returns time in microseconds

  float distance = (0.034 * duration)/2; // Speed of sound: 0.034 cm/us

  return distance;
}


void setup() {
  pinMode(usMod1Echo_pin, INPUT);
  pinMode(usMod1Trig_pin, OUTPUT);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

}

void loop() {
  float distanceStraight = getDistance(usMod1Echo_pin, usMod1Trig_pin);

  bool isWallStraight = (distanceStraight < 10)? true: false;

  if(!isWallStraight) turnLeft();

  goStraight();
}
