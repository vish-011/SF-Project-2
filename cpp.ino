// Include necessary libraries
#include <NewPing.h>
#include <AFMotor.h>
#include <Pixy2.h>

// Pin definitions
#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200
#define LEFT_MOTOR 1
#define RIGHT_MOTOR 2
#define STOP_DISTANCE 20

// Create motor and sensor objects
AF_DCMotor leftMotor(LEFT_MOTOR);
AF_DCMotor rightMotor(RIGHT_MOTOR);
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
    // Stop the car if an obstacle is too close
    leftMotor.run(RELEASE);
    rightMotor.run(RELEASE);
  } else {
    // Detect lane and adjust motors accordingly
    int x = laneDetection();
    adjustMotors(x);
  }

  // Manual control mode (e.g., via Bluetooth)
  // Add code here to read input from remote control and adjust motors
  
  delay(100);
}

int laneDetection() {
  // Process the camera image to detect the lane
  pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks) {
    int x = pixy.ccc.blocks[0].m_x;
    return x;
  }
  
  return -1;
}

void adjustMotors(int x) {
  if (x == -1) {
    // If no lane detected, stop the car
    leftMotor.run(RELEASE);
    rightMotor.run(RELEASE);
  } else if (x < 150) {
    // Turn left
    leftMotor.run(BACKWARD);
    rightMotor.run(FORWARD);
  } else if (x > 170) {
    // Turn right
    leftMotor.run(FORWARD);
    rightMotor.run(BACKWARD);
  } else {
    // Move forward
    leftMotor.run(FORWARD);
    rightMotor.run(FORWARD);
  }
}
