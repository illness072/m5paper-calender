#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <M5EPD.h>

class Sensor {
private:
  static constexpr float BAT_MIN = 3300;
  static constexpr float BAT_MAX = 4350;

public:
  Sensor();
  void update();
  float getBatteryPercent() const;
  String getTempertureString(int prec) const;
  String getHumidityString(int prec) const;
};

#endif // _SENSOR_H_
