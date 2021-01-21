#include "clock.h"
#include <M5EPD.h>
#include <RTCLib.h>

Clock::Clock() { M5.RTC.begin(); }

String
Clock::getDateString() const {
  char buf[11];
  RTC_Date RTCdate;
  M5.RTC.getDate(&RTCdate);
  sprintf(buf, "%04d/%02d/%02d", RTCdate.year, RTCdate.mon, RTCdate.day);
  return String(buf);
}

String
Clock::getTimeString() const {
  char buf[9];
  RTC_Time RTCtime;
  M5.RTC.getTime(&RTCtime);
  sprintf(buf, "%02d:%02d:%02d", RTCtime.hour, RTCtime.min, RTCtime.sec);
  return String(buf);
}

uint32_t
Clock::getUnixTime() const {
  RTC_Date RTCdate;
  RTC_Time RTCtime;
  M5.RTC.getDate(&RTCdate);
  M5.RTC.getTime(&RTCtime);
  DateTime dt(RTCdate.year, RTCdate.mon, RTCdate.day, RTCtime.hour, RTCtime.min, RTCtime.sec);
  return (dt - TimeSpan(0, 9, 0, 0)).unixtime();
}

void
Clock::adjustTime() {
  configTime(JST, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");
  delay(2000);
  auto t = time(NULL);
  auto tm = localtime(&t);
  RTC_Time RTCtime;
  RTCtime.hour = tm->tm_hour;
  RTCtime.min = tm->tm_min;
  RTCtime.sec = tm->tm_sec;
  M5.RTC.setTime(&RTCtime);
  RTC_Date RTCdate;
  RTCdate.year = tm->tm_year + 1900;
  RTCdate.mon = tm->tm_mon + 1;
  RTCdate.day = tm->tm_mday;
  M5.RTC.setDate(&RTCdate);
}
