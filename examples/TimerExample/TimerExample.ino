/*
  TimerExample

  This example demonstrates how to setup and use the Timer class of the AutomationTimers library (https://github.com/CMB27/AutomationTimers).

  This program will count how long a button is pressed in milliseconds.
  It requires a pushbutton to be wired between pin 2 and ground.
  The count in milliseconds is displayed via the Serial Monitor or Serial Plotter.
  
  Created: 2025-03-08
  By: C. M. Bulliner
  Last Modified: 2025-03-22
  By: C. M. Bulliner
  
*/

#include <AutomationTimers.h>

Timer myTimer;

void setup() {
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {

  // AutomationTimers.update() is what actually updates the timer value.
  // It should be run once per loop.
  // It only needs to be run once, even when using multiple Timer objects.
  AutomationTimers.update();
  
  // If pin 2 is HIGH, the timer will be reset to 0, so the timer only counts up when pin 2 is LOW.
  if (digitalRead(2)) myTimer.reset();

  // This will print the timer value in milliseconds.
  Serial.println(myTimer);

  delay(50);
}
