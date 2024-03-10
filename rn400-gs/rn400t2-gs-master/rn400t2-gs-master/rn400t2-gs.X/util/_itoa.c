
#include "_itoa.h"

unsigned _itoa(const long num, char* str)
{
	long shifter;
	long n;
	unsigned len = 0;
	char* p = str;

	n = num;
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

	*p = '\0';

	do {
		*--p = (n % 10) + '0';
		n /= 10;
	} while (n);

	return len;
}
