
#ifndef __STRING_H_
#define __STRING_H_

#ifdef __cplusplus
extern "C"
{
#endif

	unsigned _strcpy(char* dest, const char* source);
	void _strncpy(char *_to, const char *_from, int _n);
	unsigned _strlen(const char* source);
	void _strcat(char* dest, const char* source);

    unsigned char _strncmp(const char* src1, const char* src2, int n, int i);
    void _strclr(char* dest, int n);

    unsigned char _isdigit(const char* src, int n);

#ifdef __cplusplus
}
#endif

#endif //__STRING_H_