#include "files.h"

Files::Files() { SPIFFS.begin(true); }

void
Files::writeWeather(const String weather) {
  log_d("%s", weather);
  saveFile(SPIFFS, "/weather.json", weather);
}

String
Files::readWeather() const {
  return readFileAsString(SPIFFS, "/weather.json");
}

String
Files::readConfig() const {
  return readFileAsString(SPIFFS, "/config.json");
}

String
Files::readFileAsString(fs::FS &fs, const char *path) {
  File file = fs.open(path, "r");
  if (!file || file.isDirectory()) {
    return String("");
  }
  return file.readString();
}

JSONVar
Files::readFileAsJson(fs::FS &fs, const char *path) {
  return JSON.parse(readFileAsString(fs, path));
}

void
Files::saveFile(fs::FS &fs, const char *path, JSONVar json) {
  saveFile(fs, path, JSON.stringify(json));
}

void
Files::saveFile(fs::FS &fs, const char *path, String value) {
  File file = fs.open(path, "w");
  if (!file || file.isDirectory()) {
    return;
  }
  file.println(value);
}
