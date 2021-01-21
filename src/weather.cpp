#include "weather.h"
#include <HTTPClient.h>

Weather::Weather() {}
Weather::Weather(JSONVar res)
    : _icon("/" + String((const char *)res["weather"][0]["icon"]) + "@2x.png"),
      _descr((const char *)res["weather"][0]["description"]),
      _temperature((double)res["main"]["temp"]),
      _humidity((double)res["main"]["humidity"]),
      _time((long)res["dt"]),
      _json(JSON.stringify(res)) {}

Weather
Weather::load(const String &json) {
  log_d("%s", json.c_str());
  return Weather(JSON.parse(json));
}

Weather
Weather::fetch(String apiKey, String city) {
  HTTPClient http;
  http.begin("http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey
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
Weather::isValid() {
  return !_json.isEmpty();
}

String
Weather::icon() const {
  return _icon;
}

String
Weather::descr() const {
  return _descr;
}

double
Weather::temperature() const {
  return _temperature;
}

double
Weather::humidity() const {
  return _humidity;
}

uint32_t
Weather::time() const {
  return _time;
}

String
Weather::json() const {
  return _json;
}
