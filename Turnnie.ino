#include <Servo.h>
#include <NewPing.h>
Servo leftServo;
Servo rightServo;

int lSpeed = 1550;
int rSpeed = 1540;

#define TRIGGER_PIN_1  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.left sensor
#define ECHO_PIN_1     13  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN_2  6  // Arduino pin tied to trigger pin on the ultrasonic sensor. right sensor
#define ECHO_PIN_2     7  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int distance1;

NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
int distance2;

#define pingSpeed 100 // Ping frequency (in milliseconds), fastest we should ping is about 35ms per sensor
unsigned long pingTimer1, pingTimer2;

int leftspeed = 32;
int rightspeed = 40;
boolean startRobot = false;

void setup() {
  Serial.begin(9600);
  leftServo.attach(2);
  rightServo.attach(3);
  stop();

  pingTimer1 = millis() + pingSpeed; // Sensor 1 fires after 100ms (pingSpeed)
  pingTimer2 = pingTimer1 + (pingSpeed / 2); // Sensor 2 fires 50ms later

  Serial.println("Starting...");
}

void loop() {
  if (millis() >= pingTimer1) {
    pingTimer1 += pingSpeed; // Make sensor 1 fire again 100ms later (pingSpeed)
    distance1 = sonar1.ping_in();
  }
  if (millis() >= pingTimer2) {
    pingTimer2 = pingTimer1 + (pingSpeed / 2); // Make sensor 2 fire again 50ms after sensor 1 fires
    distance2 = sonar2.ping_in();
    // Both sensors pinged, process results here
  }
  if ((distance2 > 0 && distance2 < 5) || (distance2 > 0 && distance2 < 5)) {
    startRobot = true;
  }
  if (startRobot) {
    controlMotor();
  }
  delay(10);
}

void forward(int lspeed, int rspeed) {
  leftServo.writeMicroseconds(lSpeed + lspeed);
  rightServo.writeMicroseconds(rSpeed - rspeed);
}

void stop() {
  leftServo.writeMicroseconds(lSpeed);  //stop
  rightServo.writeMicroseconds(rSpeed);   //stop
}

void controlMotor() {
  Serial.print(distance1);
  Serial.print("  ");
  Serial.print(distance2);
  Serial.println("");
  //motor_drive(FORWARD);
  if (distance1 == 0 && distance2 == 0) {
    forward (leftspeed, rightspeed);
  } else if (distance1 > 0 and distance1 < 5 and distance2 > 0 && distance2 < 5) {
    // continuous sound if the obstacle is too close
    forward(leftspeed, -rightspeed);
    Serial.println("rotating left");
    delay(350);
    stop();
    delay(10);
  } else if (distance1 > 0 and distance1 < 5) {
    // continuous sound if the obstacle is too close
    forward(leftspeed, -rightspeed);
    Serial.println("turning left");
    delay(50);
    stop();
    delay(10);
  } else if (distance1 >= 5 and distance1 < 10) {
    // continuous sound if the obstacle is too close
    forward(leftspeed, 0);
    Serial.println("turning left");
    delay(50);
  } else if (distance2 > 0 && distance2 < 5) {
    forward (-leftspeed, rightspeed);
    Serial.println("turning right");
    delay(10);
    stop();
    delay(10);
  } else if (distance2 >= 5 && distance2 < 10) {
    forward (0, rightspeed);
    Serial.println("turning right");
    delay(50);
  } else {
    forward (leftspeed, rightspeed);
  }
}