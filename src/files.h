#ifndef _FILES_H_
#define _FILES_H_

#include <Arduino_JSON.h>
#include <M5EPD.h>

class Files {
public:
  Files();
  void writeWeather(const String weather);
  String readWeather() const;
  String readConfig() const;

private:
  static String readFileAsString(fs::FS &fs, const char *path);
  static JSONVar readFileAsJson(fs::FS &fs, const char *path);
  static void saveFile(fs::FS &fs, const char *path, JSONVar json);
  static void saveFile(fs::FS &fs, const char *path, String value);
};

#endif // _FILES_H_
