# AutomationTimers
This is an Arduino library for managing event timing.
It provides intuitive tools for creating non-blocking timing events in your code.

This library consists of a collection of classes:
- `Timer`: counts up in milliseconds, can be reset
- `OnDelay`: turns an output on a set number of milliseconds after an input is turned on.
- `OffDelay`: turns an output off a set number of milliseconds after an input is turned off.
- `Debounce`: is essentially a combination of both `OnDelay` and `OffDelay`; it can be used to debounce an input.
- `SquareWave`: generates a square wave with a set period and duty cycle.
- `Edge`: detects the rising and falling edge of an input.



## Compatibility
This library should work on any microcontroller board.
It relies on [millis()](https://docs.arduino.cc/language-reference/en/functions/time/millis/) from the Arduino API/Language, but has no other dependencies.



## Examples
- [TimerExample](https://github.com/CMB27/AutomationTimers/blob/main/examples/TimerExample/TimerExample.ino)
- [OnDelayExample](https://github.com/CMB27/AutomationTimers/blob/main/examples/OnDelayExample/OnDelayExample.ino)
- [OffDelayExample](https://github.com/CMB27/AutomationTimers/blob/main/examples/OffDelayExample/OffDelayExample.ino)
- [DebounceExample](https://github.com/CMB27/AutomationTimers/blob/main/examples/DebounceExample/DebounceExample.ino)
- [SquareWaveExample](https://github.com/CMB27/AutomationTimers/blob/main/examples/SquareWaveExample/SquareWaveExample.ino)
- [EdgeExample](https://github.com/CMB27/AutomationTimers/blob/main/examples/EdgeExample/EdgeExample.ino)



## Methods

### Timer
A `Timer` object acts like a special variable type that always counts up in milliseconds.  
I think the best way to explain how this class works is with an example.
``` C++
# include <AutomationTimers.h>

// This creates a Timer object
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
  
}
```
In the example above, the data type `myTimer` returns is an `unsigned long`.
This value is prevented from overflowing; once the timer reaches the highest value a `unsigned long` can hold, it will stay there until reset.

`Timer` is utilized in the `OnDelay`, `OffDelay`, and `Debounce` classes.

