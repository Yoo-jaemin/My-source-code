
#include "_atof.h"

float _atof(const char* str)
{
	float ret = 0.0f;
	int sign = 1;
	char* p = (char*)str;
	unsigned dotpos = 0;
	unsigned cnt = 0;

	while (('-' == *p) || (*p == '+')) {
		if (*p == '-') sign = -1;
		p++; cnt++;
	}

	while ( ((*p >= '0') && (*p <= '9')) || (*p == '.') ) {
		if (*p == '.') {
			dotpos = cnt;
		} else {
			ret = (ret * 10.0f) + (*p - '0');
		}
		p++; cnt++;
	}

	if (dotpos > 0) {
		dotpos = cnt - dotpos - 1;
		while (dotpos--) ret /= 10.0f;
	}

	return (ret * sign);
}