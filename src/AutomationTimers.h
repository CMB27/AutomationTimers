#ifndef AutomationTimers_h
#define AutomationTimers_h

#include <Arduino.h>

#ifndef ULONG_MAX
#define ULONG_MAX ((unsigned long)0 - 1)
#endif

class TimeGetter {
  public:
    operator unsigned long() {return _currentTime;};
    unsigned long update(unsigned long currentTime);
  protected:
    unsigned long _currentTime;
};

class AutomationTimersClass {
  public:
    void update();
    unsigned long getCurrentMillis();
};

class Timer {
  public:
    Timer(TimeGetter& timeGetter);
    Timer();
    operator unsigned long();
    void reset();
    void set(unsigned long setTime);
  private:
    TimeGetter& _timeGetter;
    unsigned long _startTime = 0;
    unsigned long _elapsedTime;
};

class DigitalTimerProcess {
  public:
    DigitalTimerProcess(TimeGetter& timeGetter, unsigned long delay);
    DigitalTimerProcess(unsigned long delay);
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
    using DigitalTimerProcess::DigitalTimerProcess;
    bool update(bool input);
};

class OffDelay : public DigitalTimerProcess {
  public:
    using DigitalTimerProcess::DigitalTimerProcess;
    bool update(bool input);
};

class Debounce : public DigitalTimerProcess {
  public:
    using DigitalTimerProcess::DigitalTimerProcess;
    bool update(bool input);
};

class SquareWave {
  public:
    SquareWave(TimeGetter& timeGetter, unsigned long totalPeriod, float dutyCycle = 0.5);
    SquareWave(TimeGetter& timeGetter, unsigned long onPeriod, unsigned long offPeriod);
    SquareWave(TimeGetter& timeGetter, int onPeriod, int offPeriod);
    SquareWave(unsigned long totalPeriod, float dutyCycle = 0.5);
    SquareWave(unsigned long onPeriod, unsigned long offPeriod);
    SquareWave(int onPeriod, int offPeriod);
    operator bool();
  private:
    TimeGetter& _timeGetter;
    Timer _timer;
    unsigned long _totalPeriod;
    unsigned long _onPeriod;
    void _setup(unsigned long totalPeriod, float dutyCycle);
    void _setup(unsigned long onPeriod, unsigned long offPeriod);
    void _setup(int onPeriod, int offPeriod);
};

class SampleTimer {
  public:
    SampleTimer(TimeGetter& timeGetter, unsigned long samplePeriod);
    SampleTimer(unsigned long samplePeriod);
    operator bool();
  private:
    TimeGetter& _timeGetter;
    Timer _timer;
    unsigned long _samplePeriod;
    unsigned long _sampleTime;
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
    LinearRamp(TimeGetter& timeGetter, float rate);
    LinearRamp(float rate);
    operator float();
    float update(float input);
    void setRate(float rate);
    float update(float input, float rate);
  private:
    Timer _timer;
    float _deltaTime;
    float _target = 0;
    float _start = 0;
    float _output = 0;
    float _rate = 1.0;
};

extern AutomationTimersClass AutomationTimers;

#endif
