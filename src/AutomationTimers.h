#ifndef AutomationTimers_h
#define AutomationTimers_h

#include "Arduino.h"

#ifndef ULONG_MAX
#define ULONG_MAX ((unsigned long)0 - 1)
#endif

class AutomationTimersClass {
  public:
    void update();
    unsigned long getCurrentMillis();
  protected:
    static unsigned long _currentMillis;
};

class Timer : private AutomationTimersClass {
  public:
    operator unsigned long();
    void reset();
    void set(unsigned long setMillis);
  private:
    unsigned long _startMillis = 0;
    unsigned long _elapsedMillis;
};

class DigitalTimerProcess {
  public:
    operator bool() {return _output;};
    virtual bool update(bool input) = 0;
    void setDelay(unsigned long delay);
  protected:
    Timer _timer;
    unsigned long _delay;
    bool _output;
    bool _firstRun = true;
};

class OnDelay : public DigitalTimerProcess {
  public:
    OnDelay(unsigned long delay);
    bool update(bool input);
};

class OffDelay : public DigitalTimerProcess {
  public:
    OffDelay(unsigned long delay);
    bool update(bool input);
};

class Debounce : public DigitalTimerProcess {
  public:
    Debounce(unsigned long delay);
    bool update(bool input);
};

class SquareWave : private AutomationTimersClass {
  public:
    SquareWave(unsigned long totalPeriod, float dutyCycle = 0.5);
    SquareWave(unsigned long onPeriod, unsigned long offPeriod);
    operator bool();
  private:
    unsigned long _totalPeriod;
    unsigned long _onPeriod;
    unsigned long _startMillis;
};

class Edge {
  public:
    operator bool();
    void update(bool input);
    bool rising();
    bool falling();
    bool change();
  private:
    bool _currentValue;
    bool _previousValue;
};

class LinearRamp {
  public:
    LinearRamp(float rate);
    operator float();
    float update(float input);
    void setRate(float rate);
  private:
    Timer _timer;
    float _deltaMilliseconds;
    float _target = 0;
    float _start = 0;
    float _output = 0;
    float _rate = 1.0;
};

extern AutomationTimersClass AutomationTimers;

#endif
