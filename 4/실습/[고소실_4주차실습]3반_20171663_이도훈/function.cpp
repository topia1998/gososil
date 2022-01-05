#define _USE_MATH_DEFINES
#include <math.h>

double _f1(double x) {
	return (pow(x, 2.0) - 4 * x + 4 - log(x));
}

double _fp1(double x) {
	return (2 * x - 4 - 1 / x);
}

double _f2(double x) {
	return (x + 1 - 2 * sin(x * M_PI));
}

double _fp2(double x) {
	return (1 - 2 * M_PI * cos(x * M_PI));
}

double _f3(double x) {
	return (pow(x, 4.0) - 11.0 * pow(x, 3.0) + 42.35 * pow(x, 2.0) - 66.55 * x + 35.1384);
}

double _fp3(double x) {
	return (4 * pow(x, 3.0) - 33.0 * pow(x, 2.0) + 2.0 * 42.35 * x - 66.55);
}

double _f_sqrt(double x) {
	return x * x - 2.0;
}

double _fp_sqrt(double x) {
	return 2.0 * x;
}

double _f_vehicle(double x) {
	return 0.0;
}

double _fp_vehicle(double x) {
	return 0.0;
}

double _f_comp(double x) {
	return log(x) - 1;
}

double _fp_comp(double x) {
	return 1 / x;
}
