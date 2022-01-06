#include <stdio.h>
#include <random>
#include <time.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

#define N 25
double Taylor_series(double x, int n);
double Taylor_series_ex(double x, int n);
__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;

void main(void)
{
	printf("*** f<-8.3> = %.6e \n", Taylor_series(-8.3, N));
	printf("*** f<-8.3> = %.6e \n", Taylor_series_ex(-8.3, N));
	printf("*** f<-8.3> = %.6e \n", pow(2.71828182846, -8.3));
}




double Taylor_series(double x, int n)
{
	double answer = 0.0, ch = 1;
	int i;

	for (i = 1; i < n; i++) {
		ch /= i;
	}
	answer = ch;
	for (i = n - 1; i >= 1; i--) {
		ch *= i;
		answer = answer * x + ch;
	}

	answer = answer - ch;

	return answer + 1;
}


double Taylor_series_ex(double x, int n)
{
	double answer = 0.0, ch = 1;
	int i;
	for (i = 1; i < n * 2; i++) {
		ch /= i;
	}
	answer = ch;
	for (i = n * 2 - 1; i >= 1; i--) {
		ch *= i;
		answer = answer * x + ch;
	}

	answer = answer - ch;

	return answer + 1;
}
