#ifndef _MAIN_PAGE_H_
#define _MAIN_PAGE_H_

#include <M5EPD.h>
#include "clock.h"
#include "sensor.h"
#include "weather.h"

class MainPage {
  static constexpr int TEXTSIZE_BATTERY = 32;
  static constexpr int TEXTSIZE_DATE = 72;
  static constexpr int TEXTSIZE_TIME = 180;
  static constexpr int TEXTSIZE_SENSOR_LABEL = 24;
  static constexpr int TEXTSIZE_SENSOR_VALUE = 48;

  M5EPD_Canvas canvas;

  static String formatDouble(double num, int prec = 1);

public:
  MainPage();
  void show(const Sensor &sensor, const Clock &clock, const Weather &weather);
};

#endif // _MAIN_PAGE_H_
