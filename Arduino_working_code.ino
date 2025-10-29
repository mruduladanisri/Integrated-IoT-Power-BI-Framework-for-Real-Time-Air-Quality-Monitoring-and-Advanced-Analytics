#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

// Replace with your WiFi credentials
const char* ssid = "GSR-Wifi";
const char* password = "Gsr@1976";

// Google Apps Script Web App URL
const char* scriptURL = "https://script.google.com/macros/s/AKfycbzmI9_sV5ze14dz_Z0N3dAwhMAUujwTLayxNToPU9NKp4ew15h6xiDFjXYvzPkYKkpWLg/exec";

#define LED_PIN 17     // LED control pin
#define SENSOR_PIN 33  // Analog pin for reading dust sensor (via Voltage Divider)

// MQ sensor pin definitions
#define MQ135_PIN 36
#define MQ7_PIN 39
#define MQ4_PIN 34
#define MQ2_PIN 35
#define MQ5_PIN 32

// Sensor variables
float temperature, pressure, altitude;
int mq135ppm, mq4ppm, mq2ppm, mq7ppm, mq5ppm;
float voltage, dustDensity;

void dustsen(); // Function prototype

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(LED_PIN, OUTPUT);
  Serial.print("Connecting to WiFi...");
  
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    if (millis() - startTime > 10000) {
      Serial.println("\nWiFi connection failed. Restarting...");
      ESP.restart();
    }
  }
  Serial.println("\nConnected to WiFi!");

  // Initialize BMP280 sensor
  if (!bmp.begin(0x76)) {
    Serial.println(F("BMP280 sensor not found! Check wiring."));
    while (1);
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
}

void loop() {
  readSensors();
  sendToGoogleSheets();
  delay(3600000);  // Send data every 5 seconds
}

void readSensors() {
  temperature = bmp.readTemperature();
  pressure = bmp.readPressure() / 100.0F;
  altitude = bmp.readAltitude(1013.25);

  mq135ppm = map(analogRead(MQ135_PIN), 0, 4095, 0, 1000);
  mq4ppm = map(analogRead(MQ4_PIN), 0, 4095, 0, 1000);
  mq2ppm = map(analogRead(MQ2_PIN), 0, 4095, 0, 1000);
  mq7ppm = map(analogRead(MQ7_PIN), 0, 4095, 0, 1000);
  mq5ppm = map(analogRead(MQ5_PIN), 0, 4095, 0, 1000);

  // Print values to Serial Monitor
  Serial.println("\n------ Sensor Readings ------");
  Serial.printf("Temperature: %.2f °C\n", temperature);
  Serial.printf("Pressure: %.2f hPa\n", pressure);
  Serial.printf("Altitude: %.2f meters\n", altitude);
  Serial.printf("MQ135: %d PPM\n", mq135ppm);
  Serial.printf("MQ4: %d PPM\n", mq4ppm);
  Serial.printf("MQ2: %d PPM\n", mq2ppm);
  Serial.printf("MQ7: %d PPM\n", mq7ppm);
  Serial.printf("MQ5: %d PPM\n", mq5ppm);
  Serial.println("-----------------------------");
}

void sendToGoogleSheets() {
  dustsen();
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(scriptURL);
    http.addHeader("Content-Type", "application/json");

    // Create JSON payload
    String jsonPayload = "{";
    jsonPayload += "\"sensor1\": " + String(temperature) + ", ";
    jsonPayload += "\"sensor2\": " + String(pressure) + ", ";
    jsonPayload += "\"sensor3\": " + String(altitude) + ", ";
    jsonPayload += "\"sensor4\": " + String(mq135ppm) + ", ";
    jsonPayload += "\"sensor5\": " + String(mq4ppm) + ", ";
    jsonPayload += "\"sensor6\": " + String(mq2ppm) + ", ";
    jsonPayload += "\"sensor7\": " + String(mq7ppm) + ", ";
    jsonPayload += "\"sensor8\": " + String(mq5ppm) + ", ";
    jsonPayload += "\"sensor9\": " + String(dustDensity);
    jsonPayload += "}";  // Closing JSON object

    // Send POST request
    int httpResponseCode = http.POST(jsonPayload);

    // Print response
    if (httpResponseCode > 0) {
      Serial.printf("Data sent successfully: %d\n", httpResponseCode);
    } else {
      Serial.printf("Error sending data: %d\n", httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi Disconnected!");
  }
}

void dustsen() {
  digitalWrite(LED_PIN, LOW);  // Turn LED ON
  delayMicroseconds(280);      // Wait 280µs

  int sensorValue = analogRead(SENSOR_PIN);  // Read sensor value
  digitalWrite(LED_PIN, HIGH);               // Turn LED OFF
  delayMicroseconds(40);                     // Wait 40µs

  voltage = sensorValue * (3.3 / 4095.0);  // Convert ADC value to voltage
  dustDensity = (voltage - 0.1) / 0.005;   // Convert to Dust Density (µg/m³)

  Serial.print("Raw Value: ");
  Serial.print(sensorValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);
  Serial.print("V | Dust Density: ");
  Serial.print(dustDensity);
  Serial.println(" µg/m³");
}