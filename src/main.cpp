#include "files.h"
#include "main_page.h"
#include "config.h"
#include <Arduino.h>
#include <M5EPD.h>
#include <WiFi.h>

bool wifiStarted = false;
void
startWiFi(String ssid, String psk) {
  if (!wifiStarted) {
    WiFi.begin(ssid.c_str(), psk.c_str());
    int retry = 3;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      retry--;
      if (retry == 0) {
        return;
      }
    }
    wifiStarted = true;
  }
}

void
setup() {
  M5.begin(false, false, false, true, false);
  Files files;
  Config config = Config::load(files.readConfig());
  Sensor sensor;
  Clock clock;
  Weather weather = Weather::load(files.readWeather());

  // show
  MainPage mainPage;
  mainPage.show(sensor, clock, weather);

  // fetch weather & adjust time
  auto span = clock.getUnixTime() - weather.time();
  log_d("span: %lu", span);
  if (span > 3600) {
    startWiFi(config.ssid(), config.psk());
    auto newWeather = Weather::fetch(config.apiKey(), config.city());
    if (newWeather.isValid()) {
      files.writeWeather(newWeather.json());
      log_d("dt: %lu", newWeather.time());
    }
    log_d("adjust time");
    clock.adjustTime();
  }

  delay(1000);
  M5.shutdown(60);
}

void
loop() {}
