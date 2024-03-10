
# 1 "app_linear_regression.c"

# 13 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\stdint.h"
typedef signed char int8_t;

# 20
typedef signed int int16_t;

# 28
typedef __int24 int24_t;

# 36
typedef signed long int int32_t;

# 52
typedef unsigned char uint8_t;

# 58
typedef unsigned int uint16_t;

# 65
typedef __uint24 uint24_t;

# 72
typedef unsigned long int uint32_t;

# 88
typedef signed char int_least8_t;

# 96
typedef signed int int_least16_t;

# 109
typedef __int24 int_least24_t;

# 118
typedef signed long int int_least32_t;

# 136
typedef unsigned char uint_least8_t;

# 143
typedef unsigned int uint_least16_t;

# 154
typedef __uint24 uint_least24_t;

# 162
typedef unsigned long int uint_least32_t;

# 181
typedef signed char int_fast8_t;

# 188
typedef signed int int_fast16_t;

# 200
typedef __int24 int_fast24_t;

# 208
typedef signed long int int_fast32_t;

# 224
typedef unsigned char uint_fast8_t;

# 230
typedef unsigned int uint_fast16_t;

# 240
typedef __uint24 uint_fast24_t;

# 247
typedef unsigned long int uint_fast32_t;

# 268
typedef int32_t intmax_t;

# 282
typedef uint32_t uintmax_t;

# 289
typedef int16_t intptr_t;




typedef uint16_t uintptr_t;

# 15 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\stdbool.h"
typedef unsigned char bool;

# 4 "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/PIC18F-J_DFP/1.4.41/xc8\pic\include\__size_t.h"
typedef unsigned size_t;

# 14 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\string.h"
extern void * memcpy(void *, const void *, size_t);
extern void * memmove(void *, const void *, size_t);
extern void * memset(void *, int, size_t);

# 36
extern char * strcat(char *, const char *);
extern char * strcpy(char *, const char *);
extern char * strncat(char *, const char *, size_t);
extern char * strncpy(char *, const char *, size_t);
extern char * strdup(const char *);
extern char * strtok(char *, const char *);


extern int memcmp(const void *, const void *, size_t);
extern int strcmp(const char *, const char *);
extern int stricmp(const char *, const char *);
extern int strncmp(const char *, const char *, size_t);
extern int strnicmp(const char *, const char *, size_t);
extern void * memchr(const void *, int, size_t);
extern size_t strcspn(const char *, const char *);
extern char * strpbrk(const char *, const char *);
extern size_t strspn(const char *, const char *);
extern char * strstr(const char *, const char *);
extern char * stristr(const char *, const char *);
extern char * strerror(int);
extern size_t strlen(const char *);
extern char * strchr(const char *, int);
extern char * strichr(const char *, int);
extern char * strrchr(const char *, int);
extern char * strrichr(const char *, int);

# 30 "C:\Program Files\Microchip\xc8\v2.32\pic\include\c90\math.h"
extern double fabs(double);
extern double floor(double);
extern double ceil(double);
extern double modf(double, double *);
extern double sqrt(double);
extern double atof(const char *);
extern double sin(double) ;
extern double cos(double) ;
extern double tan(double) ;
extern double asin(double) ;
extern double acos(double) ;
extern double atan(double);
extern double atan2(double, double) ;
extern double log(double);
extern double log10(double);
extern double pow(double, double) ;
extern double exp(double) ;
extern double sinh(double) ;
extern double cosh(double) ;
extern double tanh(double);
extern double eval_poly(double, const double *, int);
extern double frexp(double, int *);
extern double ldexp(double, int);
extern double fmod(double, double);
extern double trunc(double);
extern double round(double);

# 14 "app_linear_regression.h"
typedef struct {


float x[10];
float y[10];

# 24
uint8_t position;
float time_cnt;

float sum_x;
float sum_x2;
float sum_y;
float sum_xy;

float slope;
float offset;

# 39
} s_Linear_reg;

# 47
void Linear_regression_init(s_Linear_reg* p);
void Linear_regression(s_Linear_reg* p, float uVoltage);

# 17 "app_linear_regression.c"
static float slope_average(s_Linear_reg* p, float slope);

volatile uint8_t g_time_cnt;


void Linear_regression_init(s_Linear_reg* p)
{
uint8_t index;


for (index = 0; index < 10; index++) {
p->x[index] = 0.0f;
p->y[index] = 0.0f;
}

# 38
p->position = 0;
p->time_cnt = 0.0f;

p->sum_x = 0.0f;
p->sum_y = 0.0f;
p->sum_x2 = 0.0f;
p->sum_xy = 0.0f;
p->slope = 0.0f;
p->offset = 0.0f;
}

# 58
void Linear_regression(s_Linear_reg* p, float uVoltage)
{
uint8_t index;
float slp;

p->sum_x = 0.0f;
p->sum_y = 0.0f;
p->sum_x2 = 0.0f;
p->sum_xy = 0.0f;


if (p->time_cnt != 60) {
p->time_cnt = p->time_cnt + 1.0f;
if ( fmod(p->time_cnt, (float)(60/10)) == 0.0f ) {
p->x[p->position] = p->time_cnt;
p->y[p->position] = uVoltage;
p->position++;
}
} else {
g_time_cnt++;
if (g_time_cnt == 60/10) {
g_time_cnt = 0;
for (index = 0; index < 10 -1; index++) {
p->x[index] = (p->x[index +1] - (float)(60/10));
p->y[index] = p->y[index +1];
}
p->x[10 -1] = (float)60;
p->y[10 -1] = uVoltage;
}
}


for (index = 0; index < 10; index++) {
p->sum_x += p->x[index];
p->sum_y += p->y[index];
p->sum_x2 += p->x[index] * p->x[index];
p->sum_xy += p->x[index] * p->y[index];
}


p->slope = (10*p->sum_xy - p->sum_x*p->sum_y) / (10*p->sum_x2 - p->sum_x*p->sum_x);
p->offset = (p->sum_y - p->slope*p->sum_x) / 10;
}

