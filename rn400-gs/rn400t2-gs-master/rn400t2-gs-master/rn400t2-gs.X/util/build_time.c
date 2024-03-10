
#include "build_time.h"

time_t build_time(void)
{
	struct tm tm = { 0 };
	time_t timestamp;

  	tm.tm_year = BUILD_YEAR - 1900;
	tm.tm_mon = BUILD_MONTH - 1;
	tm.tm_mday = BUILD_DAY; // this is localtime
    tm.tm_hour = BUILD_HOUR - 9; // localtime to utc time
    tm.tm_min = BUILD_MIN;
    tm.tm_sec = BUILD_SEC;
	timestamp = mktime(&tm);

    return timestamp;
}