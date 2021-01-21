#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <M5EPD.h>
#include <Arduino_JSON.h>

class Config {
  String _ssid;
  String _psk;
  String _apiKey;
  String _city;

  Config(JSONVar res);

public:
  static Config load(const String &json);
  String ssid() const;
  String psk() const;
  String apiKey() const;
  String city() const;
};

#endif //_CONFIG_H_
