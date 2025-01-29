#include <Adafruit_LiquidCrystal.h>

// LCD Object
Adafruit_LiquidCrystal lcd(0);

// Pin Definitions
const int LED = 1;
const int BUTTON_LEFT = 2;
const int BUTTON_RIGHT = 3;
const int BUTTON_MODE = 4;
const int BUZZER = 5;

// Variables
int characterPosition = 7; // Start position for the heart
bool autoMode = false;     // Start in manual mode

// Heart Character
byte heart[] = {
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
};

// Function to Set Up LCD
void setupLCD() {
  lcd.begin(16, 2);          // Initialize LCD size (16x2)
  lcd.createChar(0, heart);  // Load heart into custom character memory
  //updateDisplay();           // Initial display setup
}

// Function to Update the LCD Display
void updateDisplay() {
  lcd.clear();                               // Clear screen
  lcd.setCursor(characterPosition, 0);      // Move cursor to position
  lcd.write(byte(0));                       // Draw the heart
  lcd.setCursor(5, 1);                      // Move cursor to bottom row
  lcd.print(autoMode ? "AUTO" : "MANUAL");  // Show current mode
}

// Function to Handle Manual Movement
void handleManualMode(bool leftPressed, bool rightPressed) {
  if (leftPressed && characterPosition > 0) {
    characterPosition--;    // Move left
    updateDisplay();
    delay(200);             // Debounce delay
  }
  if (rightPressed && characterPosition < 15) {
    characterPosition++;    // Move right
    updateDisplay();
    delay(200);             // Debounce delay
  }
}

// Function to Handle Mode Switching
void toggleMode(bool modePressed) {
  if (modePressed) {
    autoMode = !autoMode;  // Toggle between manual and auto mode
    if (autoMode) {        // Feedback when entering auto mode
      for (int i = 0; i < 3; i++) {
        digitalWrite(LED, HIGH);
        tone(BUZZER, 1000, 100);  // Play sound for 100ms
        delay(200);
        digitalWrite(LED, LOW);
        delay(200);
      }
    }
    updateDisplay();  // Update display for new mode
    delay(200);       // Debounce delay
  }
}

// Function to Handle Auto Mode
void handleAutoMode() {
  static unsigned long lastMoveTime = 0;  // Tracks time since last move
  static bool movingRight = true;         // Tracks direction of movement

  if (millis() - lastMoveTime >= 500) {  // Move every 500ms
    if (movingRight) {
      if (characterPosition < 15) {
        characterPosition++;  // Move right
      } else {
        movingRight = false;  // Reverse direction
      }
    } else {
      if (characterPosition > 0) {
        characterPosition--;  // Move left
      } else {
        movingRight = true;   // Reverse direction
      }
    }
    updateDisplay();          // Update display
    lastMoveTime = millis();  // Update timer
  }
}
void setup() {
  pinMode(LED, OUTPUT);        // Set LED as output
  pinMode(BUTTON_LEFT, INPUT); // Set buttons as input
  pinMode(BUTTON_RIGHT, INPUT);
  pinMode(BUTTON_MODE, INPUT);
  pinMode(BUZZER, OUTPUT);     // Set buzzer as output
  setupLCD();                  // Initialize LCD
}

// Main Loop Function
void loop() {
  // Read button states 
  bool leftPressed = digitalRead(BUTTON_LEFT); 
  bool rightPressed = digitalRead(BUTTON_RIGHT);
  bool modePressed = digitalRead(BUTTON_MODE);

  if (!autoMode) {
    handleManualMode(leftPressed, rightPressed);  // Handle manual movement
  }

  toggleMode(modePressed);  // Check if mode needs to be toggled

  if (autoMode) {
    handleAutoMode();  // Handle automatic movement
  }

  delay(50);  // Small delay to prevent flickering
}