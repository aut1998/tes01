#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <TridentTD_LineNotify.h>

// Replace with your Wi-Fi credentials and LINE Notify token
#define SSID        "Chxda"
#define PASSWORD    "0807018263"
#define LINE_TOKEN  "nIAobN0RDbmlINnQ3CiRmLABR4tD3geE8WGF5frQSqV"

Adafruit_MPU6050 mpu;
// TridentTD_LineNotify LINE;

// Threshold for tilt detection (adjust as needed)
const float tiltThreshold = 0.5; // Example threshold, in degrees

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  Serial.println("Adafruit MPU6050 test!");

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("");

  // Connect to Wi-Fi
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n", SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP: %s\n", WiFi.localIP().toString().c_str());

  // Set LINE Notify token
  LINE.setToken(LINE_TOKEN);
}

void loop() {
  // Get new sensor events with the readings
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Print out the values
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  // Check for tilt condition
  if (a.acceleration.x > 5 || a.acceleration.x < -5) {
    // Bike is tilted, send LINE Notify message
    LINE.notify("อุ๊ย!! ล้มแล้วววววววว");
  }

  Serial.println("");
  delay(500);
}
