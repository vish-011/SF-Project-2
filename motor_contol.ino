// Function to adjust motors based on lane position
void adjustMotors(int x) {
  if (x == -1) {
    // If no lane detected, stop the car
    stopCar();
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

// Function to stop the car
void stopCar() {
  leftMotor.run(RELEASE);
  rightMotor.run(RELEASE);
}
