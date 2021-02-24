# Turnnie
The obstacle avoidance robot uses two ultrasonic sensors and continuous-servos controlled by Arduino to navigate all obstacles seamlessly.

# Hardware components

* Any arduino uno
* continuous servo
* HC-SR04 Ultrasonic Sensor

# Setup
1. Connect the trigger/echo pins of the left ultrasonic sensor to pin 12 and 13. The trigger/echo pin of the right ultrasonic sensor to pin 6 and 7 Arduino pins. 
2. Connect the left continuous servo to pin two and the continuous servo to pin three.
3. The speed should be controlled by updating the line 26 and 27. Once the robot travels in a straight line, the code should take care of the rest.
