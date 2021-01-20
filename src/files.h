#ifndef _FILES_H_
#define _FILES_H_

#include <Arduino.h>
#include <Arduino_JSON.h>
#include <M5EPD.h>

class Files {
public:
  Files() { SPIFFS.begin(true); }

  void
  writeWeather(const String weather) {
    log_d("%s", weather);
    saveFile(SPIFFS, "/weather.json", weather);
  }

  String
  readWeather() {
    return readFileAsString(SPIFFS, "/weather.json");
  }

private:
  static String
  readFileAsString(fs::FS &fs, const char *path) {
    File file = fs.open(path, "r");
    if (!file || file.isDirectory()) {
      return String("");
    }
    return file.readString();
  }

  static JSONVar
  readFileAsJson(fs::FS &fs, const char *path) {
    return JSON.parse(readFileAsString(fs, path));
  }

  static void
  saveFile(fs::FS &fs, const char *path, JSONVar json) {
    saveFile(fs, path, JSON.stringify(json));
  }

  static void
  saveFile(fs::FS &fs, const char *path, String value) {
    File file = fs.open(path, "w");
    if (!file || file.isDirectory()) {
      return;
    }
    file.println(value);
  }
};

#endif // _FILES_H_
