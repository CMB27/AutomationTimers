/*
  TimerExample

  This example demonstrates how to setup and use the Timer class of the AutomationTimers library (https://github.com/CMB27/AutomationTimers).

  This program will count how long a button is pressed in milliseconds.
  It requires a pushbutton to be wired between pin 2 and ground.
  The count in milliseconds is displayed via the Serial Monitor or Serial Plotter.
  
  Created: 2025-03-08
  By: C. M. Bulliner
  Last Modified: 2026-08-31
  By: C. M. Bulliner
  
*/

#include <AutomationTimers.h>

#define BUTTON_PIN 2

Timer myTimer;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {

  // AutomationTimers.update() is what actually updates the timer value.
  // It should be run once per loop.
  // It only needs to be run once, even when using multiple Timer objects.
  AutomationTimers.update();
  
  // If the button pin is HIGH, the timer will be reset to 0, so the timer only counts up when it is LOW.
  if (digitalRead(BUTTON_PIN)) myTimer.reset();

  // This will print the timer value in milliseconds.
  Serial.println(myTimer);

  delay(50);
}
