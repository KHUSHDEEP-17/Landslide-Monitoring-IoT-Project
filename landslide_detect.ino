#include <Wire.h>

#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); // Replace with the
appropriate I2C address of your accelerometer module
sensors_event_t event;
const float threshold = 12; // Adjust this threshold value as per your requirements
const int moisturePin = A0;
const int buzzerPin = 8;
void setup() {
pinMode(buzzerPin, OUTPUT);
pinMode(moisturePin, INPUT);
Serial.begin(9600);
while (!Serial)
delay(10); // Wait for serial connection
Serial.println("Vibration Detection");
if (!accel.begin()) {
Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
while (1);
}
}
void loop() {
int moistureValue = analogRead(moisturePin);

Serial.print("Moisture: ");
Serial.println(moistureValue);
accel.getEvent(&event);
float x = event.acceleration.x;
float y = event.acceleration.y;
float z = event.acceleration.z;
float acceleration = sqrt(x * x + y * y + z * z); // Calculate the magnitude of acceleration
if (acceleration > threshold) {
Serial.println("Vibration detected!");
// Perform additional actions or trigger events as needed
}
if (moistureValue<500) {
// The soil is dry, trigger the buzzer
tone(buzzerPin, 1000); // Generate a 1000Hz tone on the buzzer
delay(1000); // Play the tone for 1 second
noTone(buzzerPin); // Stop the tone
delay(1000); // Pause for 1 second
}
delay(500); // Adjust the delay as per your requirements
}
