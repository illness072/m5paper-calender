#ifndef _WEATHER_H_
#define _WEATHER_H_
#include <Arduino_JSON.h>
class Weather {
private:
  String _icon;
  String _descr;
  double _temperature;
  double _humidity;
  uint32_t _time;
  String _json;

  Weather();
  Weather(JSONVar res);

public:
  static Weather load(const String &json);
  static Weather fetch(String apiKey, String city);
  bool isValid();
  String icon() const;
  String descr() const;
  double temperature() const;
  double humidity() const;
  uint32_t time() const;
  String json() const;
};

#endif // _WEATHER_H_
