
# 1 "util/build_time.c"

# 4 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC18F-J_DFP/1.4.41/xc8\pic\include\__size_t.h"
typedef unsigned size_t;

# 8 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\time.h"
typedef long time_t;
struct tm {
int tm_sec;
int tm_min;
int tm_hour;
int tm_mday;
int tm_mon;
int tm_year;
int tm_wday;
int tm_yday;
int tm_isdst;
};

# 25
extern int time_zone;

# 30
extern time_t time(time_t *);
extern int stime(time_t *);

# 47
extern char * asctime(const struct tm *) ;
extern char * ctime(const time_t *) ;
extern struct tm * gmtime(const time_t *) ;
extern struct tm * localtime(const time_t *) ;
extern size_t strftime(char *, size_t, const char *, const struct tm *) ;
extern time_t mktime(struct tm *);

# 79 "util/build_time.h"
time_t build_time(void);

# 4 "util/build_time.c"
time_t build_time(void)
{
struct tm tm = { 0 };
time_t timestamp;

tm.tm_year = ((("Jan 20 2022"[0] == '?')) ? 99 : ( ("Jan 20 2022"[ 7] - '0') * 1000 + ("Jan 20 2022"[ 8] - '0') * 100 + ("Jan 20 2022"[ 9] - '0') * 10 + ("Jan 20 2022"[10] - '0') )) - 1900;
tm.tm_mon = ((("Jan 20 2022"[0] == '?')) ? 99 : ( (("Jan 20 2022"[0] == 'J' && "Jan 20 2022"[1] == 'a' && "Jan 20 2022"[2] == 'n')) ? 1 : (("Jan 20 2022"[0] == 'F')) ? 2 : (("Jan 20 2022"[0] == 'M' && "Jan 20 2022"[1] == 'a' && "Jan 20 2022"[2] == 'r')) ? 3 : (("Jan 20 2022"[0] == 'A' && "Jan 20 2022"[1] == 'p')) ? 4 : (("Jan 20 2022"[0] == 'M' && "Jan 20 2022"[1] == 'a' && "Jan 20 2022"[2] == 'y')) ? 5 : (("Jan 20 2022"[0] == 'J' && "Jan 20 2022"[1] == 'u' && "Jan 20 2022"[2] == 'n')) ? 6 : (("Jan 20 2022"[0] == 'J' && "Jan 20 2022"[1] == 'u' && "Jan 20 2022"[2] == 'l')) ? 7 : (("Jan 20 2022"[0] == 'A' && "Jan 20 2022"[1] == 'u')) ? 8 : (("Jan 20 2022"[0] == 'S')) ? 9 : (("Jan 20 2022"[0] == 'O')) ? 10 : (("Jan 20 2022"[0] == 'N')) ? 11 : (("Jan 20 2022"[0] == 'D')) ? 12 : 99 )) - 1;
tm.tm_mday = ((("Jan 20 2022"[0] == '?')) ? 99 : ( (("Jan 20 2022"[4] >= '0') ? ("Jan 20 2022"[4] - '0') * 10 : 0) + ("Jan 20 2022"[5] - '0') ));
tm.tm_hour = ((("11:28:20"[0] == '?')) ? 99 : (("11:28:20"[0] - '0') * 10 + "11:28:20"[1] - '0')) - 9;
tm.tm_min = ((("11:28:20"[0] == '?')) ? 99 : (("11:28:20"[3] - '0') * 10 + "11:28:20"[4] - '0'));
tm.tm_sec = ((("11:28:20"[0] == '?')) ? 99 : (("11:28:20"[6] - '0') * 10 + "11:28:20"[7] - '0'));
timestamp = mktime(&tm);

return timestamp;
}
