#include <ESP8266WiFi.h>         // For Wi-Fi
#include <ESP8266HTTPClient.h>   // For HTTP requests
#include <DHT.h>
#include <Servo.h>               // Use ESP8266 specific servo library

// Wi-Fi credentials
const char* ssid = "Nothing";             // Replace with your Wi-Fi SSID
const char* password = "12345678anmol";   // Replace with your Wi-Fi password

// AWS server details
const char* serverName = "http://3.89.74.81/data";  // Replace with your EC2 public IP

WiFiClient client;  // Declare WiFiClient object

// Define pin connections for RGB LED
#define RED_PIN D2     // Red pin of the RGB LED (GPIO4)
#define GREEN_PIN D3   // Green pin of the RGB LED (GPIO0)
#define BLUE_PIN D4    // Blue pin of the RGB LED (GPIO2)

// Define pin connection for LDR
#define LDR_PIN A0  
#define buzzerPin D8   // Pin for the buzzer

int ldrValue = 0;

// Ultrasonic Sensor configuration
#define TRIG_PIN D5  // Trigger pin of ultrasonic sensor
#define ECHO_PIN D6  // Echo pin of ultrasonic sensor

// Servo configuration
const int servoPin = D7;  // GPIO13 for servo
Servo radarServo;

// DHT Sensor configuration
#define DHTPIN D1      // GPIO5 on NodeMCU
#define DHTTYPE DHT11  // DHT 11 sensor
DHT dht(DHTPIN, DHTTYPE);

// Variables for distance calculation
long duration;
int distance;

// Timing for radar updates
unsigned long lastServoTime = 0;
const long interval = 50;  // Interval for servo update (in milliseconds)
int radarAngle = 0;         // Current servo angle
int radarDirection = 1;     // 1 for clockwise, -1 for counter-clockwise

// Timing for DHT and LDR updates
unsigned long lastDataUpdateTime = 0;
const long dataUpdateInterval = 5000;  // Send data every 5 seconds

// Function to calculate distance using the ultrasonic sensor
long measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long calculatedDistance = duration * 0.034 / 2;  // Calculate distance in cm
  return calculatedDistance;
}

// Function to set the RGB LED color
void setRGB(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

// Function to send data to AWS
void sendDataToAWS(int angle, int distance, float temperature, float humidity, int intensity) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Pass WiFiClient object and server URL
    http.begin(client, serverName);
    http.addHeader("Content-Type", "application/json");

    // Create JSON payload with all data
    String jsonData = "{\"angle\": " + String(angle) +
                      ", \"distance\": " + String(distance) +
                      ", \"temperature\": " + String(temperature) +
                      ", \"humidity\": " + String(humidity) +
                      ", \"intensity\": " + String(intensity) + "}";

    // Send POST request
    int httpResponseCode = http.POST(jsonData);

    // Check server response
    if (httpResponseCode > 0) {
      Serial.println("Data sent successfully");
      Serial.print("Response Code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error in sending data. HTTP Response Code: ");
      Serial.println(httpResponseCode);
    }

    http.end();  // Close the connection
  } else {
    Serial.println("WiFi not connected. Reconnecting...");
    WiFi.begin(ssid, password);
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize the DHT sensor
  dht.begin();

  // Initialize Wi-Fi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Set up pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output

  // Initialize servo
  radarServo.attach(servoPin);
  radarServo.write(90);  // Start at the middle position
  delay(1000);

  Serial.println("Setup Complete");
}

void loop() {
  unsigned long currentMillis = millis();

  // Radar: Sweep servo and measure distance
  if (currentMillis - lastServoTime >= interval) {
    lastServoTime = currentMillis;

    // Update radar angle and direction
    radarAngle += radarDirection * 5;  // Increment/decrement angle
    if (radarAngle >= 170 || radarAngle <= 0) {
      radarDirection *= -1;  // Reverse direction at boundaries
    }

    radarServo.write(radarAngle);
    delay(50);  // Allow servo to reach the position

    distance = measureDistance();

    // Object detection logic
    if (distance < 20) {
      Serial.println("Object detected!");
      digitalWrite(buzzerPin, HIGH);  // Activate buzzer
    } else {
      digitalWrite(buzzerPin, LOW);  // Deactivate buzzer
    }
  }

  // Update and send sensor data every 5 seconds
  if (currentMillis - lastDataUpdateTime >= dataUpdateInterval) {
    lastDataUpdateTime = currentMillis;

    // Read DHT sensor data
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Check if the readings are valid
    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Read LDR value
    ldrValue = analogRead(LDR_PIN);

    // Update RGB LED based on LDR value
    if (ldrValue < 50) {
      setRGB(255, 0, 255);  // Turn on RGB LED (Red)
    } else {
      setRGB(0, 0, 0);      // Turn off RGB LED
    }

    // Send all data to AWS
    sendDataToAWS(radarAngle, distance, temperature, humidity, ldrValue);
  }
}