// Function to detect obstacles using ultrasonic sensor
unsigned int getObstacleDistance() {
  return sonar.ping_cm();
}
