#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <M5EPD.h>
#include <RTCLib.h>

class Clock {
  static constexpr int JST = 3600 * 9;

public:
  Clock() { M5.RTC.begin(); }

  String
  getDateString() const {
    char buf[11];
    RTC_Date RTCdate;
    M5.RTC.getDate(&RTCdate);
    sprintf(buf, "%04d/%02d/%02d", RTCdate.year, RTCdate.mon, RTCdate.day);
    return String(buf);
  }

  String
  getTimeString() const {
    char buf[9];
    RTC_Time RTCtime;
    M5.RTC.getTime(&RTCtime);
    sprintf(buf, "%02d:%02d:%02d", RTCtime.hour, RTCtime.min, RTCtime.sec);
    return String(buf);
  }

  uint32_t
  getUnixTime() const {
    RTC_Date RTCdate;
    RTC_Time RTCtime;
    M5.RTC.getDate(&RTCdate);
    M5.RTC.getTime(&RTCtime);
    DateTime dt(RTCdate.year, RTCdate.mon, RTCdate.day, RTCtime.hour, RTCtime.min, RTCtime.sec);
    return (dt - TimeSpan(0, 9, 0, 0)).unixtime();
  }

  void
  adjustTime() {
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
};

#endif // _CLOCK_H_
