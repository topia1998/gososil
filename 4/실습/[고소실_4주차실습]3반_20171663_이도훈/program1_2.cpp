#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Secant Method
**********************************************/
void program1_2(FILE* fp) {
	double x0, x1, temp;
	int n = 0;

	if (fp == NULL)
		return;
	scanf("%lf %lf", &x0, &x1);
	fprintf(fp, "input : %lf %lf\n", x0, x1);
	fprintf(fp, "n\txn1\t\t\t|f(xn1)|\n");
	while (n < Nmax) {
		if (n == 0) fprintf(fp, "%2d %.15e %.15e\n", n, x0, fabs(_f(x0)));
		else if (n == 1) fprintf(fp, "%2d %.15e %.15e\n", n, x1, fabs(_f(x1)));
		else if (n >= 2) {
			temp = x1 - _f(x1) * (x1 - x0) / (_f(x1) - _f(x0));
			fprintf(fp, "%2d %.15e %.15e\n", n, temp, fabs(_f(temp)));
			if (fabs(_f(temp)) < DELTA) return;
			if (n >= Nmax) return;
			if (fabs(temp - x1) < EPSILON) return;

			x0 = x1;
			x1 = temp;
		}
		n++;
	}
}
