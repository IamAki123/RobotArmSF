#include <Servo.h>

const int sensorPin = A0; // Analog pin connected to SIG
Servo myServo; // Create a servo object
unsigned long lastChangeTime = 0; // Track the last time the input signal changed
const unsigned long timeout = 5000; // 5 seconds timeout
int lastSignal = -1; // Track the last signal value

void setup() {
  Serial.begin(9600); // Start the Serial Monitor and Serial Plotter
  Serial.println("Muscle Signal"); // Add a label for the Serial Plotter
  
  myServo.attach(9); // Attach the servo to pin 9
  myServo.write(90); // Initialize the servo to 90 degrees (relaxed state)
}

void loop() {
  int muscleSignal = analogRead(sensorPin); // Read the signal value
  
  // Print only the signal value for Serial Plotter visualization
  Serial.println(muscleSignal);

  // Check if the signal has changed
  if (muscleSignal != lastSignal) {
    lastSignal = muscleSignal;
    lastChangeTime = millis(); // Update the last change time
  }

  // Servo control logic with only two positions
  if (muscleSignal >= 50 && muscleSignal <= 400) {
    // Stressed state
    myServo.write(0); // Move the servo to 0 degrees
  } else if (muscleSignal >= 500 && muscleSignal <= 600) {
    // Relaxed state
    myServo.write(180); // Move the servo to 180 degrees
  }

  // Check for inactivity timeout
  if (millis() - lastChangeTime > timeout) {
    myServo.write(90); // Move the servo to relaxed position after timeout
  }

  delay(10); // Short delay for stable readings
}
