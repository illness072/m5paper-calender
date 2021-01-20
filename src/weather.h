#ifndef _WEATHER_H_
#define _WEATHER_H_

#include <Arduino_JSON.h>
#include <HTTPClient.h>

class Weather {
private:
  String _icon;
  String _descr;
  double _temperature;
  double _humidity;
  uint32_t _time;
  String _json;

  Weather() {}
  Weather(JSONVar res)
      : _icon("/" + String((const char *)res["weather"][0]["icon"]) + "@2x.png"),
        _descr((const char *)res["weather"][0]["description"]),
        _temperature((double)res["main"]["temp"]),
        _humidity((double)res["main"]["humidity"]),
        _time((long)res["dt"]),
        _json(JSON.stringify(res)) {}

public:
  static Weather
  load(const String &json) {
    log_d("%s", json.c_str());
    return Weather(JSON.parse(json));
  }

  static Weather
  fetch() {
    const String API_KEY = "AAAAAA";
    const String CITY = "BBBBBB";

    HTTPClient http;
    http.begin("http://api.openweathermap.org/data/2.5/weather?q=" + CITY + "&appid=" + API_KEY
               + "&lang=en&units=metric");
    auto httpCode = http.GET();
    // HTTP header has been send and Server response header has been handled
    log_d("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    if (httpCode != HTTP_CODE_OK) {
      log_e("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      return Weather();
    }
    auto res = JSON.parse(http.getString());
    log_d("%s", JSON.stringify(res).c_str());
    return Weather(res);
  }

  bool
  isValid() {
    return !_json.isEmpty();
  }

  String
  icon() const {
    return _icon;
  }

  String
  descr() const {
    return _descr;
  }

  double
  temperature() const {
    return _temperature;
  }

  double
  humidity() const {
    return _humidity;
  }

  uint32_t
  time() const {
    return _time;
  }

  String
  json() const {
    return _json;
  }
};

#endif // _WEATHER_H_
