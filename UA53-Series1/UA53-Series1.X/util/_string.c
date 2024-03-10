
#include "_string.h"

unsigned _strcpy(char* dest, const char* source)
{
    unsigned int i = 0;
	if(!source || !dest) return i;
	while(*dest++ = *source++) i++;
    return i;
}

void _strncpy(char *_to, const char *_from, int _n)
{
	if(!_from || !_to || !_n) return;
	while (_n--) *_to++ = *_from++;
}

unsigned _strlen(const char* source)
{
	const char* sc = source;
	while(*sc) ++sc;
	return sc-source;
}

void _strcat(char* dest, const char* source)
{
	while(*dest) ++dest;
	while(*dest++ = *source++);
}

unsigned char _strncmp(const char* src1, const char* src2, int n, int i)
{
    if(!src1 || !src2 || !n || n<0) return 0;
    while (n--) {
        char ch = *src1;
        if (i > 0 && ch == '%') {
            ch = i + '0';
        }
        if (ch != *src2)
            return 0;
        src1++;
        src2++;
    }
    return 1;
}

void _strclr(char* dest, int n)
{
    if(!dest || !n || n<0) return;
    while (n--) *dest++ = '\0';
}

unsigned char _isdigit(const char* src, int n)
{
    while (n--) {
        char ch = *src - '0';
        if (!(ch >= 0 && ch <= 9))
            return 0;
        src++;
    }
    return 1;
}
