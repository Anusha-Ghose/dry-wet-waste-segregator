#include <Servo.h>

const int moisturePin = A0;
const int dryThreshold = 1022;

const int trigPin = 7;
const int echoPin = 8;

Servo wasteServo;
const int servoPin = 6;

long duration;
int distanceThreshold = 30;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  wasteServo.attach(servoPin);
  wasteServo.write(90);
  delay(500);
}

void loop() {
  int moistureValue = analogRead(moisturePin);
  Serial.print("Moisture: ");
  Serial.println(moistureValue);

  if (detectWaste()) {
    Serial.println("Object detected");

    Serial.print("Moisture: ");
    Serial.print(moistureValue);
    Serial.print(" Threshold: ");
    Serial.println(dryThreshold);

    if (moistureValue < dryThreshold) {
      Serial.println("Dry Waste");
      Serial.println("Moving servo to 30");
      wasteServo.write(30);
    } else {
      Serial.println("Wet Waste");
      Serial.println("Moving servo to 150");
      wasteServo.write(150);
    }
    delay(1500);
    Serial.println("Moving servo to 90");
    wasteServo.write(90);
    delay(1000);
  }
  delay(500);
}

bool detectWaste() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) {
    Serial.println("No object detected");
    return false;
  }
  int distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  Serial.print("Checking if distance < threshold: ");
  Serial.println(distance < distanceThreshold);

  return distance < distanceThreshold;
}
