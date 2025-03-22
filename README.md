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



## Classes

<details><summary id="timer-1"><strong>Timer</strong></summary><blockquote>

### Description
A `Timer` object acts like a read-only `unsigned long` that always counts up in milliseconds.
It can be reset to 0 using the `reset()` method.
The value of the `Timer` is prevented from overflowing; once the timer reaches the highest value a `unsigned long` can hold, it will stay there until reset.

### Methods

<details><summary id="timer-2"><strong>Timer</strong> <em>constructor</em></summary><blockquote>

### Description
Creates a `Timer` object.

### Example
``` C++
Timer myTimer;
```

</blockquote></details>

<details><summary id="timer-3"><strong>Timer</strong> <em>operator</em></summary><blockquote>

### Description
Returns the value of the timer in milliseconds.

### Returns
The value of the timer. Data type: `unsigned long`.

### Example
``` C++
if (myTimer >= 2000) {
  // do something
}
```

</blockquote></details>


<details><summary id="timer-reset"><strong>reset()</strong></summary><blockquote>

### Description
Resets the timer to 0.

### Example
``` C++
if (myTimer >= 2000) {
  myTimer.reset();
  // do something else
}
```

</blockquote></details>


### Note
`Timer` is utilized in the `OnDelay`, `OffDelay`, and `Debounce` classes.

</blockquote></details>



<details><summary id="ondelay"><strong>OnDelay</strong></summary><blockquote>


### Description

```
IN: ___/""""""""""""""""""\___
       |
OUT:___|_________/""""""""\___
       |         |
       |<-DELAY->|
```

### Methods

<details><summary id="ondelay-1"><strong>OnDelay</strong> <em>constructor</em></summary><blockquote>

### Description
Creates an `OnDelay` object.

### Syntax
`Ondelay(delay)`

### Parameter
`delay`: the delay in milliseconds to wait before setting the output `true`. Allowed data type: `unsigned long`.

### Example
``` C++
OnDelay myOnDelay(1000);
```

</blockquote></details>


<details><summary id="ondelay-2"><strong>OnDelay</strong> <em>operator</em></summary><blockquote>

### Description
Returns the value of the output.

### Returns
The value of the output. Data type: `bool`.

### Example
``` C++
if (myOnDelay) {
  // do something
}
```

</blockquote></details>


<details><summary id="ondelay-update"><strong>update()</strong></summary><blockquote>

### Description
Updates the input of an `OnDelay` object.

### Syntax
`OnDelay.update(input)`

### Parameter
`input`: the input value. Allowed data type `bool`.

### Returns
The value of the output. Data type: `bool`.  
*Reading the output is optional.*

### Example
``` C++
bool output = myOnDelay.update(input);
```

</blockquote></details>


</blockquote></details>