#include "my_solver.h"

extern double (*_f)(double);
extern double (*_fp)(double);

/*********************************************
  Bisection Method -- HOMEWORK
**********************************************/
void program1_3(FILE *fp) {
	double a0, b0, x0, x1, temp;
	int n = 0;
	scanf("%lf %lf", &a0, &b0);
	fprintf(fp, "input : %lf %lf\n", a0, b0);
	fprintf(fp, "n\txn1\t\t\t|f(xn1)|\n");
    x0 = _f(a0);
    x1 = _f(b0);
	while (n < Nmax) {
		temp = (a0 + b0) / 2;
		fprintf(fp, "%2d %.15e %.15e\n", n, temp, fabs(_f(temp)));
		if (fabs(_f(temp)) < DELTA) {
			return;
		}
		if (n >= Nmax) {
			return;
		}
		if (fabs(a0 - b0) < EPSILON) {
			return;
		}
		if (x0 * _f(temp) > 0) {
			a0 = temp;
		}
		else if (x0 * _f(temp) < 0) {
			b0 = temp;
		}
		n++;
	}
}