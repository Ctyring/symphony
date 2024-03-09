#include "time.h"
#include <time.h>
#include <chrono>
#include "stdint.h"
int64_t g_TimeAdd = 0;

uint64_t CommonFunc::GetCurrTime() {
    time_t t = time(0);

    return (uint64_t)t + g_TimeAdd;
}

bool CommonFunc::SetCurrTimeAdd(int64_t nTimeAdd) {
    g_TimeAdd += nTimeAdd;

    return true;
}

uint64_t CommonFunc::GetCurMsTime() {
    auto time_now = std::chrono::system_clock::now();
    auto duration_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        time_now.time_since_epoch());
    return duration_in_ms.count() + g_TimeAdd * 1000;
}

tm CommonFunc::GetCurrTmTime(uint64_t uTime) {
    if (uTime == 0) {
        uTime = GetCurrTime();
    }

    time_t t = (time_t)uTime;
    tm _tm_time = *localtime(&t);

    return _tm_time;
}

uint64_t CommonFunc::GetDayBeginTime(uint64_t uTime) {
    if (uTime == 0) {
        uTime = GetCurrTime();
    }

    time_t t = (time_t)uTime;
    tm* t_tm = localtime(&t);
    t_tm->tm_hour = 0;
    t_tm->tm_min = 0;
    t_tm->tm_sec = 0;
    t = mktime(t_tm);

    // endtime -= (endtime - _timezone) % 86400;

    return (uint64_t)t;
}

uint64_t CommonFunc::GetWeekBeginTime(uint64_t uTime) {
    if (uTime == 0) {
        uTime = GetCurrTime();
    }

    time_t t = (time_t)uTime;
    tm* t_tm = localtime(&t);
    return (uint64_t)t - (t_tm->tm_wday == 0 ? 6 : t_tm->tm_wday - 1) * 86400 -
           t_tm->tm_hour * 3600 - t_tm->tm_min * 60 - t_tm->tm_sec;
}

uint64_t CommonFunc::GetMonthBeginTime(uint64_t uTime) {
    if (uTime == 0) {
        uTime = GetCurrTime();
    }

    time_t t = (time_t)uTime;
    tm* t_tm = localtime(&t);
    tm newtm;
    newtm.tm_year = t_tm->tm_year;
    newtm.tm_mon = t_tm->tm_mon;
    newtm.tm_mday = 1;
    newtm.tm_hour = 0;
    newtm.tm_min = 0;
    newtm.tm_sec = 0;

    return mktime(&newtm);
}

uint64_t CommonFunc::GetMonthRemainTime(uint64_t uTime) {
    if (uTime == 0) {
        uTime = GetCurrTime();
    }

    time_t t = (time_t)uTime;
    tm* t_tm = localtime(&t);

    tm newtm;
    newtm.tm_mday = 1;
    newtm.tm_hour = 0;
    newtm.tm_min = 0;
    newtm.tm_sec = 0;

    if (t_tm->tm_mon == 11) {
        newtm.tm_year = t_tm->tm_year + 1;
        newtm.tm_mon = 0;
    } else {
        newtm.tm_year = t_tm->tm_year;
        newtm.tm_mon = t_tm->tm_mon + 1;
    }

    return mktime(&newtm) - t;
}

int32_t CommonFunc::GetWeekDay() {
    time_t t = (time_t)GetCurrTime();
    tm* t_tm = localtime(&t);
    return t_tm->tm_wday;
}

int32_t CommonFunc::GetMonthDay() {
    time_t t = (time_t)GetCurrTime();
    tm* t_tm = localtime(&t);
    return t_tm->tm_mday;
}

int32_t CommonFunc::GetMonth(uint64_t uTime /*= 0*/) {
    if (uTime == 0) {
        uTime = GetCurrTime();
    }

    time_t t = (time_t)uTime;
    tm* t_tm = localtime(&t);

    return (t_tm->tm_mon + 1);
}

int32_t CommonFunc::GetTimeZone() {
#ifdef WIN32
    return _timezone / 3600;
#else
    return timezone / 3600;
#endif
}

time_t CommonFunc::YearTimeToSec(int32_t nYear,
                                 int32_t nMonth,
                                 int32_t nDay,
                                 int32_t nHour,
                                 int32_t nMin,
                                 int32_t nSec) {
    time_t t = (time_t)GetCurrTime();
    tm* t_tm = localtime(&t);

    tm newtm;
    newtm.tm_year = (nYear < 0) ? t_tm->tm_year : nYear - 1900;
    newtm.tm_mon = (nMonth < 0) ? t_tm->tm_mon : nMonth - 1;
    newtm.tm_mday = (nDay < 0) ? t_tm->tm_mday : nDay;
    newtm.tm_hour = (nHour < 0) ? t_tm->tm_hour : nHour;
    newtm.tm_min = (nMin < 0) ? t_tm->tm_min : nMin;
    newtm.tm_sec = (nSec < 0) ? t_tm->tm_sec : nSec;
    return mktime(&newtm);
    ;
}

std::string CommonFunc::TimeToString(time_t tTime) {
    tm* t_tm = localtime(&tTime);
    if (t_tm == NULL) {
        return "";
    }

    char szTime[128] = {0};
    strftime(szTime, 128, "%Y-%m-%d %H:%M:%S", t_tm);
    return std::string(szTime);
}

time_t CommonFunc::DateStringToTime(std::string strDate) {
    if (strDate.size() < 14) {
        return 0;
    }

    int32_t nYear;
    int32_t nMonth;
    int32_t nDay;
    int32_t nHour;
    int32_t nMinute;
    int32_t nSecond;

    int32_t nRet = sscanf(strDate.c_str(), "%4d-%2d-%2d %2d:%2d:%2d", &nYear,
                          &nMonth, &nDay, &nHour, &nMinute, &nSecond);
    if (nRet < 6) {
        return 0;
    }

    return YearTimeToSec(nYear, nMonth, nDay, nHour, nMinute, nSecond);
}

uint64_t CommonFunc::GetTickCount() {
#ifdef WIN32
    return ::GetTickCount64();
#else
    uint64_t uTickCount = 0;
    struct timespec on;
    if (0 == clock_gettime(CLOCK_MONOTONIC, &on)) {
        uTickCount = on.tv_sec * 1000 + on.tv_nsec / 1000000;
    }

    return uTickCount;
#endif
}

bool CommonFunc::IsSameDay(uint64_t uTime) {
#ifdef WIN32
    return ((uTime - _timezone) / 86400) ==
           ((GetCurrTime() - _timezone) / 86400);
#else
    return ((uTime - timezone) / 86400) == ((GetCurrTime() - timezone) / 86400);
#endif
}

bool CommonFunc::IsSameWeek(uint64_t uTime) {
    time_t t = GetCurrTime();
    tm t_tmSrc = *localtime(&t);
    uint64_t SrcWeekBegin =
        (uint64_t)t - (t_tmSrc.tm_wday == 0 ? 6 : t_tmSrc.tm_wday - 1) * 86400 -
        t_tmSrc.tm_hour * 3600 - t_tmSrc.tm_min * 60 - t_tmSrc.tm_sec;

    t = uTime;
    tm t_tmDest = *localtime(&t);
    uint64_t SrcWeekDest =
        (uint64_t)t -
        (t_tmDest.tm_wday == 0 ? 6 : t_tmDest.tm_wday - 1) * 86400 -
        t_tmDest.tm_hour * 3600 - t_tmDest.tm_min * 60 - t_tmDest.tm_sec;

    return (SrcWeekBegin - SrcWeekDest) / (86400 * 7) <= 0;
}

bool CommonFunc::IsSameMonth(uint64_t uTime, uint64_t sTime) {
    time_t t1 = uTime;
    tm t_tmSrc1 = *localtime(&t1);

    if (sTime == 0) {
        sTime = GetCurrTime();
    }

    time_t t2 = sTime;
    tm t_tmSrc2 = *localtime(&t2);

    return (t_tmSrc1.tm_mon == t_tmSrc2.tm_mon);
}

int32_t CommonFunc::DiffWeeks(uint64_t uTimeSrc, uint64_t uTimeDest) {
    time_t t = uTimeSrc;
    tm t_tmSrc = *localtime(&t);
    uint64_t SrcWeekBegin =
        (uint64_t)t - (t_tmSrc.tm_wday == 0 ? 6 : t_tmSrc.tm_wday - 1) * 86400 -
        t_tmSrc.tm_hour * 3600 - t_tmSrc.tm_min * 60 - t_tmSrc.tm_sec;

    t = uTimeDest;
    tm t_tmDest = *localtime(&t);
    uint64_t SrcWeekDest =
        (uint64_t)t -
        (t_tmDest.tm_wday == 0 ? 6 : t_tmDest.tm_wday - 1) * 86400 -
        t_tmDest.tm_hour * 3600 - t_tmDest.tm_min * 60 - t_tmDest.tm_sec;

    return uTimeSrc > uTimeDest
               ? (int32_t)((SrcWeekBegin - SrcWeekDest) / (86400 * 7))
               : (int32_t)((SrcWeekDest - SrcWeekBegin) / (86400 * 7));
}

int32_t CommonFunc::DiffDays(uint64_t uTimeSrc, uint64_t uTimeDest) {
#ifdef WIN32
    if (uTimeSrc > uTimeDest) {
        return (int32_t)((uTimeSrc - _timezone) / 86400 -
                         (uTimeDest - _timezone) / 86400);
    }

    return (int32_t)((uTimeDest - _timezone) / 86400 -
                     (uTimeSrc - _timezone) / 86400);
#else
    if (uTimeSrc > uTimeDest) {
        return (int32_t)((uTimeSrc - timezone) / 86400 -
                         (uTimeDest - timezone) / 86400);
    }

    return (int32_t)((uTimeDest - timezone) / 86400 -
                     (uTimeSrc - timezone) / 86400);
#endif
}