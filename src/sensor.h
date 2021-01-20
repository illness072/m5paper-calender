#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <M5EPD.h>

class Sensor {
private:
  static constexpr float BAT_MIN = 3300;
  static constexpr float BAT_MAX = 4350;

public:
  Sensor() {
    M5.SHT30.Begin();
    update();
  }

  void
  update() {
    M5.SHT30.UpdateData();
  }

  float
  getBatteryPercent() const {
    float vol = (float)M5.getBatteryVoltage();
    if (vol < BAT_MIN) {
      vol = BAT_MIN;
    } else if (vol > BAT_MAX) {
      vol = BAT_MAX;
    }
    auto battery = (vol - BAT_MIN) / (BAT_MAX - BAT_MIN);
    if (battery <= 0.01) {
      battery = 0.01;
    } else if (battery > 1.00) {
      battery = 1.00;
    }
    return battery;
  }

  String
  getTempertureString(int prec) const {
    char buf[10];
    dtostrf(M5.SHT30.GetTemperature(), 2, prec, buf);
    return String(buf);
  }

  String
  getHumidityString(int prec) const {
    char buf[10];
    dtostrf(M5.SHT30.GetRelHumidity(), 2, prec, buf);
    return String(buf);
  }
};

#endif // _SENSOR_H_
