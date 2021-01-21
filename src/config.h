#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <Arduino_JSON.h>

class Config {
  String _ssid;
  String _psk;
  String _apiKey;
  String _city;

  Config() {}
  Config(JSONVar res)
      : _ssid((const char *)res["wifi"]["ssid"]),
        _psk((const char *)res["wifi"]["psk"]),
        _apiKey((const char *)res["weather"]["api_key"]),
        _city((const char *)res["weather"]["city"]) {}

public:
  static Config
  load(const String &json) {
    log_d("%s", json.c_str());
    return Config(JSON.parse(json));
  }

  String
  ssid() {
    return _ssid;
  }

  String
  psk() {
    return _psk;
  }

  String
  apiKey() {
    return _apiKey;
  }

  String
  city() {
    return _city;
  }
};

#endif //_CONFIG_H_
