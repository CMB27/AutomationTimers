/*
  OffDelayExample

  This example demonstrates how to setup and use the OffDelay class of the AutomationTimers library (https://github.com/CMB27/AutomationTimers).

  This program will turn the built-in LED on when a button pressed, but wait half a second to turn it off once the button is released.
  This requires a pushbutton to be wired between pin 2 and ground.
  The button input and LED output values are displayed via the Serial Monitor or Serial Plotter.
  
  Created: 2025-03-08
  By: C. M. Bulliner
  Last Modified: 2026-08-31
  By: C. M. Bulliner
  
*/

#include <AutomationTimers.h>

#define BUTTON_PIN 2

OffDelay myOffDelay(500);

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  AutomationTimers.update();

  bool input = !digitalRead(BUTTON_PIN);
  myOffDelay.update(input);

  digitalWrite(LED_BUILTIN, myOffDelay);

  Serial.print("input:");
  Serial.print(input);
  Serial.print(",");
  Serial.print("output:");
  Serial.print(myOffDelay);
  Serial.println();

  delay(50);
}
