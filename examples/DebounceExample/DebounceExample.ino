/*
  DebounceExample

  This example demonstrates how to setup and use the Debounce class of the AutomationTimers library (https://github.com/CMB27/AutomationTimers).

  This program will turn the built-in LED on once a button is held down for one second, and wait one second to turn it off once the button is released.
  This requires a pushbutton to be wired between pin 2 and ground.
  The button input and LED output values are displayed via the Serial Monitor or Serial Plotter.
  
  Created: 2025-03-08
  By: C. M. Bulliner
  Last Modified: 2025-03-22
  By: C. M. Bulliner
  
*/

#include <AutomationTimers.h>

Debounce myDebounce(1000);

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  AutomationTimers.update();

  bool input = !digitalRead(2);
  bool output = myDebounce.update(input);

  digitalWrite(LED_BUILTIN, output);

  Serial.print("input:");
  Serial.print(input);
  Serial.print(",");
  Serial.print("output:");
  Serial.print(output);
  Serial.println();

  delay(50);
}
