
#include <stdio.h>
#include "_ftoa.h"

#define DOT_LEN 2

#if 1
unsigned _ftoa(const float num, char* str)
{
    int len = sprintf (str, "%.2f", num);
    if (len < 0) len = 0;
    return len;
}
#else
unsigned _ftoa(const float num, char* str)
{
	long shifter;
	long ipart, n, i;
	float fpart;
	unsigned len = 0;
	char* p = str;

	n = ipart = (long)num;
	if (num < 0){
		n *= -1;
		*p = '-';
		p++; len++;
	}

	shifter = n;
	do {
		shifter /= 10;
		p++; len++;
	} while (shifter);

	*p = '.'; len++;

	do {
		*--p = (n % 10) + '0';
		n /= 10;
	} while (n);

	fpart = num - (float)ipart;
	if (fpart < 0) fpart *= (-1);

	for (i = 0 ; i < DOT_LEN/* + 1*/ ; i++) { fpart *= 10; }

	p = str + len;
	n = (int)fpart;

	p += DOT_LEN; len += DOT_LEN;
	*p = '\0';

	/*i = n % 10;
	n /= 10;

	if (i >= 5) n += 1;*/

	for (i = 0 ; i < DOT_LEN ; i++) {
		if (n) {
			*--p = (n % 10) + '0';
			n /= 10;
		} else {
			*--p = '0';
		}
	}

	return len;
}
#endif
