#include <Servo.h>

Servo steer_motor;
Servo throt_motor;

const int steer_in = 2;
const int throt_in = 3;
const int steer_out = 11;
const int throt_out = 10;

int steer_in_value = 0;
int throt_in_value  = 0;
int steer_out_value = 0;
int throt_out_value  = 0;
// defines variables

const int trigPin = 8;
const int echoPin = 9;
// defines variables

long duration;
int distance;

void setup() {
  pinMode(steer_in, INPUT); // Sets the trigPin as an Output
  pinMode(throt_in, INPUT); // Sets the echoPin as an Input

  steer_motor.attach(steer_out);
  throt_motor.attach(throt_out);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(115200); // Starts the serial communication
}

void loop() {

  steer_in_value = pulseIn(steer_in, HIGH);
  throt_in_value = pulseIn(throt_in, HIGH);

  steer_out_value = steer_in_value;
  throt_out_value = 1500 - (1500 - throt_in_value) / 2;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH, 100000);
  // Calculating the distance
  distance = duration * 0.034 / 2;

  if (distance < 40 && distance != 0) {
    throt_motor.writeMicroseconds(1100);
    delay(1000);
  }
  else {
    throt_motor.writeMicroseconds(throt_out_value);
  }
  steer_motor.writeMicroseconds(steer_out_value);
  /*
    Serial.print("PWM_steer: ");
    Serial.print(steer_in_value);
    Serial.print("\t");
    Serial.print("PWM_throt: ");
    Serial.println(throt_in_value);
  */
  Serial.print("distance: ");
  Serial.println(distance);
}
