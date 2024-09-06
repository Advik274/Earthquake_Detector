#include <MPU6050.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// Initialize the MPU6050
MPU6050 MPU;
int GyroX, GyroY, GyroZ;

// Define the pins
int ledPin = 8;      // Digital pin connected to the LED
int buzzerPin = 7;   // Digital pin connected to the buzzer
int contrastPin = 6; // Pin connected to V0 of the LCD for contrast control

// Initialize the LCD with the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Set the LED, buzzer, and contrast pin as OUTPUT
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(contrastPin, OUTPUT);

  // Set initial contrast for the LCD
  analogWrite(contrastPin, 110); // Adjust the contrast if needed

  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);  // Position cursor to column 4, row 0
  lcd.print("BY GROUP 10");  // Print "ICT4D-KH" at the specified position

  lcd.setCursor(1,1);
  lcd.print("QUAKE DETECTOR");
  
  // Initialize serial communication and the MPU6050
  Serial.begin(9600);
  Wire.begin();
  MPU.initialize();
}

void loop() {
  // Get gyroscope data
  MPU.getRotation(&GyroX, &GyroY, &GyroZ);
  
  // Print gyroscope data to Serial Monitor for the Serial Plotter
  Serial.print(GyroX);
  Serial.print(" ");
  Serial.print(GyroY);
  Serial.print(" ");
  Serial.println(GyroZ);

  // Display gyroscope data on the LCD
  
  // Check if any gyroscope value exceeds the threshold
  if (GyroX < -425 || GyroX > 425 || GyroY > 425 || GyroY < -425 || GyroZ > 425 || GyroZ < -425) {
    // Activate the LED and buzzer 5 times
    for (int i = 0; i < 10; i++) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(10);

      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);
      delay(10);
    }
  } else {
    // Ensure the LED and buzzer are off if the threshold is not met
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
  
  delay(100);
  
}
