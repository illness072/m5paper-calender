#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <M5EPD.h>

class Clock {
  static constexpr int JST = 3600 * 9;

public:
  Clock();
  String getDateString() const;
  String getTimeString() const;
  uint32_t getUnixTime() const;
  void adjustTime();
};

#endif // _CLOCK_H_
