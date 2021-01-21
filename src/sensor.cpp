#include "sensor.h"

Sensor::Sensor() {
  M5.SHT30.Begin();
  update();
}

void
Sensor::update() {
  M5.SHT30.UpdateData();
}

float
Sensor::getBatteryPercent() const {
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
Sensor::getTempertureString(int prec) const {
  char buf[10];
  dtostrf(M5.SHT30.GetTemperature(), 2, prec, buf);
  return String(buf);
}

String
Sensor::getHumidityString(int prec) const {
  char buf[10];
  dtostrf(M5.SHT30.GetRelHumidity(), 2, prec, buf);
  return String(buf);
}
