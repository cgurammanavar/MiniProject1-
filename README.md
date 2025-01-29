# LCD Character Movement System by Chandrashekar Gurammanavar

## Description
This project implements an interactive LCD display system featuring a custom heart character that can move left and right across a 16x2 LCD screen. The system supports both manual and automatic movement modes, with visual and audio feedback for mode transitions.

## Features
- Custom heart character display on 16x2 LCD
- Dual operation modes:
  - Manual Mode: Character moves one position at a time using left/right buttons
  - Auto Mode: Character moves automatically back and forth across the display
- Mode transition feedback:
  - 3 LED blinks
  - 3 buzzer beeps
- Button debouncing for reliable input
- Current mode display on LCD's bottom row
- Boundary detection to prevent character from moving off-screen

## Hardware Requirements
- Arduino board
- 16x2 LCD display (compatible with Adafruit_LiquidCrystal library)
- 3 push buttons
- 1 LED
- 1 Buzzer
- Resistors (as needed for buttons and LED)
- Breadboard and jumper wires
- USB cable for programming

## Pin Configuration
- LED: Pin 1
- Left Button: Pin 2
- Right Button: Pin 3
- Mode Button: Pin 4
- Buzzer: Pin 5
- LCD: Connected via I2C (address 0)

## Software Dependencies
- Adafruit_LiquidCrystal library

## Installation
1. Connect the hardware components according to the pin configuration
2. Install the Adafruit_LiquidCrystal library via Arduino IDE Library Manager
3. Upload the provided code to your Arduino board

## Usage
1. Power up the system - it starts in manual mode
2. Manual Mode:
   - Press left button to move character left
   - Press right button to move character right
3. Auto Mode:
   - Press mode button to switch to auto mode
   - Character will automatically move back and forth
   - Press mode button again to return to manual mode

## Functions Overview
- `setupLCD()`: Initializes the LCD and loads custom character
- `updateDisplay()`: Refreshes the LCD display with current position and mode
- `handleManualMode()`: Processes button inputs for manual movement
- `toggleMode()`: Handles mode switching with feedback
- `handleAutoMode()`: Controls automatic character movement
- `setup()`: Initializes pins and system configuration
- `loop()`: Main program loop handling input processing and mode execution

## Contributing
Feel free to fork this project and submit pull requests for any improvements or bug fixes.
