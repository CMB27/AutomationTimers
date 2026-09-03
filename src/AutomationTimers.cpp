#include "AutomationTimers.h"


// TimeGetter

unsigned long TimeGetter::update(unsigned long currentTime) {
  _currentTime = currentTime;
  return _currentTime;
}

// Create a default TimeGetter
static TimeGetter defaultTimeGetter;



// AutomationTimersClass

void AutomationTimersClass::update() {
  defaultTimeGetter.update(millis());
}

unsigned long AutomationTimersClass::getCurrentMillis() {
  return defaultTimeGetter;
}



// Timer

Timer::Timer(TimeGetter& timeGetter) : _timeGetter(timeGetter) {

}

Timer::Timer() : _timeGetter(defaultTimeGetter) {

}

Timer::operator unsigned long() {
  if (_elapsedTime != ULONG_MAX) {
    unsigned long tempElapsedTime = _timeGetter - _startTime;
    if (tempElapsedTime < _elapsedTime) _elapsedTime = ULONG_MAX;
    else _elapsedTime = tempElapsedTime;
  }
  return _elapsedTime;
}

void Timer::reset() {
  _elapsedTime = 0;
  _startTime = _timeGetter;
}

void Timer::set(unsigned long setTime) {
  _elapsedTime = setTime;
  _startTime = _timeGetter - _elapsedTime;
}



// DigitalTimerProcess

DigitalTimerProcess::DigitalTimerProcess(TimeGetter& timeGetter, unsigned long delay) : _timer(timeGetter) {
  setDelay(delay);
}

DigitalTimerProcess::DigitalTimerProcess(unsigned long delay) : _timer(defaultTimeGetter) {
  setDelay(delay);
}

void DigitalTimerProcess::setDelay(unsigned long delay) {
  _delay = delay;
}



// OnDelay

bool OnDelay::update(bool input) {
  if (_firstRun) {
    _timer.set(_delay);
    _firstRun = false;
  }
  _output = false;
  if (!input) _timer.reset();
  else if (_timer >= _delay) _output = true;
  return _output;
}



// OffDelay

bool OffDelay::update(bool input) {
  if (_firstRun) {
    _timer.set(_delay);
    _firstRun = false;
  }
  _output = true;
  if (input) _timer.reset();
  else if (_timer >= _delay) _output = false;
  return _output;
}



// Debounce

bool Debounce::update(bool input) {
  if (_firstRun) {
    _timer.set(_delay);
    _output = input;
    _firstRun = false;
  }
  if (input == _output) _timer.reset();
  else if (_timer >= _delay) {
    _output = input;
    _timer.reset();
  }
  return _output;
}



// SquareWave

SquareWave::SquareWave(TimeGetter& timeGetter, unsigned long totalPeriod, float dutyCycle) : _timeGetter(timeGetter), _timer(timeGetter) {
  _setup(totalPeriod, dutyCycle);
}

SquareWave::SquareWave(TimeGetter& timeGetter, unsigned long onPeriod, unsigned long offPeriod) : _timeGetter(timeGetter), _timer(timeGetter) {
  _setup(onPeriod, offPeriod);
}

SquareWave::SquareWave(TimeGetter& timeGetter, int onPeriod, int offPeriod) : _timeGetter(timeGetter), _timer(timeGetter) {
  _setup(onPeriod, offPeriod);
}

SquareWave::SquareWave(unsigned long totalPeriod, float dutyCycle) : _timeGetter(defaultTimeGetter), _timer(defaultTimeGetter) {
  _setup(totalPeriod, dutyCycle);
}

SquareWave::SquareWave(unsigned long onPeriod, unsigned long offPeriod) : _timeGetter(defaultTimeGetter), _timer(defaultTimeGetter) {
  _setup(onPeriod, offPeriod);
}

SquareWave::SquareWave(int onPeriod, int offPeriod) : _timeGetter(defaultTimeGetter), _timer(defaultTimeGetter) {
  _setup(onPeriod, offPeriod);
}

SquareWave::operator bool() {
  if (_timer >= _totalPeriod) _timer.set(_timeGetter % _totalPeriod);
  if (_timer < _onPeriod) return true;
  return false;
}

void SquareWave::_setup(unsigned long totalPeriod, float dutyCycle) {
  _totalPeriod = totalPeriod;
  if (dutyCycle > 1.0) dutyCycle = 1.0;
  if (dutyCycle < 0.0) dutyCycle = 0.0;
  _onPeriod = (unsigned long)((float)_totalPeriod * dutyCycle);
}

void SquareWave::_setup(unsigned long onPeriod, unsigned long offPeriod) {
  _onPeriod = onPeriod;
  _totalPeriod = _onPeriod + offPeriod;
}

void SquareWave::_setup(int onPeriod, int offPeriod) {
  if (onPeriod < 0) onPeriod = 0;
  if (offPeriod < 0) offPeriod = 0;
  _setup((unsigned long)onPeriod, (unsigned long)offPeriod);
}



// SampleTimer

SampleTimer::SampleTimer(TimeGetter& timeGetter, unsigned long samplePeriod) : _timeGetter(timeGetter), _timer(timeGetter) {
  _samplePeriod = samplePeriod;
}

SampleTimer::SampleTimer(unsigned long samplePeriod) : _timeGetter(defaultTimeGetter), _timer(defaultTimeGetter) {
  _samplePeriod = samplePeriod;
}

SampleTimer::operator bool() {
  if (_timer >= _samplePeriod) {
    _timer.set(_timeGetter % _samplePeriod);
    _sampleTime = _timeGetter;
  }
  if (_timeGetter == _sampleTime) return true;
  return false;
}



// Edge

Edge::operator bool() {
  return _currentValue;
}

void Edge::update(bool input) {
  _previousValue = _currentValue;
  _currentValue = input;
}

bool Edge::rising() {
  if (_currentValue > _previousValue) return true;
  return false;
}

bool Edge::falling() {
  if (_currentValue < _previousValue) return true;
  return false;
}

bool Edge::change() {
  if (_currentValue != _previousValue) return true;
  return false;
}



// LinearRamp

LinearRamp::LinearRamp(TimeGetter& timeGetter, float rate) : _timer(timeGetter) {
  setRate(rate);
}

LinearRamp::LinearRamp(float rate) : _timer(defaultTimeGetter) {
  setRate(rate);
}

LinearRamp::operator float() {
  return _output;
}

float LinearRamp::update(float input) {
  if (input != _target) {
    _target = input;
    _start = _output;
    float deltaUnits = _target - _start;
    if (deltaUnits < 0.0) deltaUnits = deltaUnits * -1.0;
    _deltaTime = deltaUnits / _rate;
    _timer.reset();
  }
  if (_timer < _deltaTime) {
    if (_target > _start) _output = _rate * _timer + _start;
    else _output = -_rate * _timer + _start;
  }
  else _output = _target;
  return _output;
}

void LinearRamp::setRate(float rate) {
  if (rate < 0.0) rate = rate * -1.0;
  if (rate != 0.0) _rate = rate;
}

float LinearRamp::update(float input, float rate) {
  setRate(rate);
  return update(input);
}




// Instantiate AutomationTimers
AutomationTimersClass AutomationTimers;
