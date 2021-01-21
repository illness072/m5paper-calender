#include "config.h"

Config::Config(JSONVar res)
    : _ssid((const char *)res["wifi"]["ssid"]),
      _psk((const char *)res["wifi"]["psk"]),
      _apiKey((const char *)res["weather"]["api_key"]),
      _city((const char *)res["weather"]["city"]) {}

Config
Config::load(const String &json) {
  log_d("%s", json.c_str());
  return Config(JSON.parse(json));
}

String
Config::ssid() const {
  return _ssid;
}

String
Config::psk() const {
  return _psk;
}

String
Config::apiKey() const {
  return _apiKey;
}

String
Config::city() const {
  return _city;
}
