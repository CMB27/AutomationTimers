/*
  OnDelayExample

  This example demonstrates how to setup and use the LinearRamp class of the AutomationTimers library (https://github.com/CMB27/AutomationTimers).
  
  Numeric input values are entered via the Serial Monitor or Serial Plotter and the the input and output values are displayed.
  The output will ramp to the entered setpoint/input value at the set rate: 0.1 units per millisecond.
  
  Created: 2025-03-29
  By: C. M. Bulliner
  
*/

#include <AutomationTimers.h>

LinearRamp myRamp(0.1);
float setpoint = 0;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
}

void loop() {
  AutomationTimers.update();

  if (Serial.available()) {
    String tempString = Serial.readStringUntil('\n');
    tempString.trim();
    setpoint = tempString.toFloat();
  }

  myRamp.update(setpoint);

  Serial.print("input:");
  Serial.print(setpoint);
  Serial.print(",");
  Serial.print("output:");
  Serial.print(myRamp);
  Serial.println();

  delay(50);
}