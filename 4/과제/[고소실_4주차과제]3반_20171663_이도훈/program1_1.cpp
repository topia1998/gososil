#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Newton-Rapson Method
**********************************************/
void program1_1(FILE* fp) {
	double x0, x1;
	int n = 0;

	if (fp == NULL)
		return;
	scanf("%lf", &x0);
	fprintf(fp, "input : %lf\n", x0);
	fprintf(fp, "n\txn1\t\t\t|f(xn1)|\n");
	while (n < Nmax) {
		x1 = x0 - _f(x0) / _fp(x0);
		fprintf(fp, "%2d %.15e %.15e\n", n, x0, fabs(_f(x0)));
		if (fabs(_f(x1)) < DELTA) {
			fprintf(fp, "%2d %.15e %.15e\n", n + 1, x1, fabs(_f(x1)));
			return;
		}
		if (n >= Nmax) {
			fprintf(fp, "%2d %.15e %.15e\n", n + 1, x1, fabs(_f(x1)));
			return;
		}
		if (fabs(x1 - x0) < EPSILON) {
			fprintf(fp, "%2d %.15e %.15e\n", n + 1, x1, fabs(_f(x1)));
			return;
		}
		n++;
		x0 = x1;
	}
}
