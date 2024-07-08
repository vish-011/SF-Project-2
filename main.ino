#include <NewPing.h>
#include <AFMotor.h>
#include <Pixy2.h>

// Pin definitions
#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200
#define STOP_DISTANCE 20

// Motor definitions
#define LEFT_MOTOR 1
#define RIGHT_MOTOR 2

// Motor objects
AF_DCMotor leftMotor(LEFT_MOTOR);
AF_DCMotor rightMotor(RIGHT_MOTOR);

// Sensor objects
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Pixy2 pixy;

void setup() {
  // Initialize motors
  leftMotor.setSpeed(255);
  rightMotor.setSpeed(255);

  // Initialize serial communication
  Serial.begin(9600);

  // Initialize Pixy2 camera
  pixy.init();
}

void loop() {
  // Read distance from ultrasonic sensor
  unsigned int distance = sonar.ping_cm();

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");

  // Autonomous mode
  if (distance < STOP_DISTANCE) {
    stopCar();
  } else {
    int x = laneDetection();
    adjustMotors(x);
  }

  // Manual control mode (e.g., via Bluetooth)
  // Add code here to read input from remote control and adjust motors

  delay(100);
}
