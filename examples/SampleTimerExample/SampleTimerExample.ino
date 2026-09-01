/*
  SampleTimerExample

  This example demonstrates how to setup and use the SampleTimer class of the AutomationTimers library (https://github.com/CMB27/AutomationTimers).

  This program will flash built-in LED once every second.
  The timing of the flash is sent to the Serial Monitor.
  
  Created: 2026-08-07
  By: C. M. Bulliner
  Last Modified: 2026-08-31
  By: C. M. Bulliner
  
*/

#include <AutomationTimers.h>

SampleTimer mySampleTimer(1000);
OffDelay myOffDelay(50);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  AutomationTimers.update();
  
  digitalWrite(LED_BUILTIN, myOffDelay.update(mySampleTimer));
  
  if (mySampleTimer) {
    Serial.print("time:");
    Serial.print(AutomationTimers.getCurrentMillis());
    Serial.println();
  }

  // This delay is not needed.
  // It introduces some timing error.
  // It is included here to show that the error does not accumulate.
  delay(3);
}
