#include "main_page.h"
#include "binaryttf.h"

String
MainPage::formatDouble(double num, int prec) {
  char buf[10];
  dtostrf(num, 2, prec, buf);
  return String(buf);
}

MainPage::MainPage() : canvas(M5EPD_Canvas(&M5.EPD)) {
  canvas.loadFont(binaryttf, sizeof(binaryttf));
  canvas.createCanvas(960, 540);
  canvas.createRender(TEXTSIZE_BATTERY);
  canvas.createRender(TEXTSIZE_DATE);
  canvas.createRender(TEXTSIZE_TIME);
  canvas.createRender(TEXTSIZE_SENSOR_LABEL);
  canvas.createRender(TEXTSIZE_SENSOR_VALUE);
}

void
MainPage::show(const Sensor &sensor, const Clock &clock, const Weather &weather) {
  canvas.setTextDatum(TL_DATUM);

  // Battery
  canvas.setTextSize(TEXTSIZE_BATTERY);
  canvas.drawString(String((int)(sensor.getBatteryPercent() * 100)) + "%", 850, 10);

  // Date & Time
  canvas.setTextSize(TEXTSIZE_DATE);
  canvas.drawString(clock.getDateString(), 100, 50);
  canvas.setTextSize(TEXTSIZE_TIME);
  canvas.setTextDatum(TC_DATUM);
  canvas.drawString(clock.getTimeString(), 960 / 2, 170);
  canvas.setTextDatum(TL_DATUM);

  // Temperature & Humidity
  canvas.setTextSize(TEXTSIZE_SENSOR_LABEL);
  canvas.drawString("temperature", 100, 370);
  canvas.drawString("humidity", 400, 370);
  canvas.setTextSize(TEXTSIZE_SENSOR_VALUE);
  canvas.drawString(sensor.getTempertureString(1) + "'C", 200, 410);
  canvas.drawString(sensor.getHumidityString(1) + "%", 500, 410);

  // weather
  canvas.fillRect(760, 370, 100, 100, 1);
  canvas.drawPngFile(SPIFFS, weather.icon().c_str(), 760, 370);
  canvas.setTextSize(TEXTSIZE_SENSOR_LABEL);
  canvas.setTextDatum(TC_DATUM);
  canvas.drawString(weather.descr(), 810, 480);
  canvas.setTextDatum(TL_DATUM);
  canvas.setTextSize(TEXTSIZE_BATTERY);
  canvas.drawString(formatDouble(weather.temperature(), 1) + "'C", 200, 470);
  canvas.drawString(formatDouble(weather.humidity(), 1) + "%", 500, 470);

  //canvas.setTextSize(TEXTSIZE_SENSOR_LABEL);
  //canvas.drawString("span:" + String(clock.getUnixTime() - weather.time()), 800, 50);

  M5.EPD.Clear(true);
  canvas.pushCanvas(0, 0, UPDATE_MODE_GC16);
}
