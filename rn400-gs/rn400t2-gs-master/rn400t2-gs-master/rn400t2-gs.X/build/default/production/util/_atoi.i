
# 1 "util/_atoi.c"

# 9 "util/_atoi.h"
long _atoi(const char* str);

# 4 "util/_atoi.c"
long _atoi(const char* str)
{
long ret = 0;
int sign = 1;
char* p = (char*)str;

while (('-' == *p) || (*p == '+')) {
if (*p == '-') sign = -1;
p++;
}

while ((*p >= '0') && (*p <= '9')) {
ret = (ret * 10) + (*p - '0');
p++;
}

return (ret * sign);
}
