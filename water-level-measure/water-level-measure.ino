// Ultrasonic Sensor Pins
#define TRIG_PIN D1
#define ECHO_PIN D3

// Pump Control Pin
#define PUMP_PIN D2

// Tank dimensions (in cm)
const int tankHeight = 100;  // Adjust based on the height of your water tank
const int waterLowThreshold = 20;   // Threshold to turn off pump
const int waterHighThreshold = 80;  // Threshold to turn on pump

void setup() {
  Serial.begin(115200);

  // Configure pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, 0); // Ensure pump is initially off
}

long measureDistance() {
  // Send a 10us pulse to the Trig pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the duration of the pulse on the Echo pin
  return pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;  // Convert duration to distance (cm)
}

void controlPump(long waterLevel) {
  if (waterLevel < waterLowThreshold) {
    digitalWrite(PUMP_PIN, LOW); // Turn off the pump
  } else if (waterLevel > waterHighThreshold) {
    digitalWrite(PUMP_PIN, HIGH); // Turn on the pump
  }
}

void loop() {
  long distance = measureDistance();
  long waterLevel = tankHeight - distance;

  controlPump(waterLevel);

  // Output water level and pump status to Serial Monitor
  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.println(" cm");

  delay(1000); // Delay before measuring again
}
