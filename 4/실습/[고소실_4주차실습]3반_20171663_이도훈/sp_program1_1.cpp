#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Newton-Rapson Method
**********************************************/
void sp_program1_1(FILE* fp) {
	float x0, x1;
	int n = 0;

	if (fp == NULL)
		return;
	scanf("%f", &x0);
	fprintf(fp, "n\txn1\t\t\t|f(xn1)|\n");
	fprintf(fp, "input : %lf\n", x0);
	while (n < Nmax) {
		x1 = x0 - _sp_f(x0) / _sp_fp(x0);
		fprintf(fp, "%2d %.15e %.15e\n", n, x0, fabs(_sp_f(x0)));
		if (fabs(_sp_f(x1)) < DELTA) {
			fprintf(fp, "%2d %.15e %.15e\n", n + 1, x1, fabs(_sp_f(x1)));
			return;
		}
		if (n >= Nmax) {
			fprintf(fp, "%2d %.15e %.15e\n", n + 1, x1, fabs(_sp_f(x1)));
			return;
		}
		if (fabs(x1 - x0) < EPSILON) {
			fprintf(fp, "%2d %.15e %.15e\n", n + 1, x1, fabs(_sp_f(x1)));
			return;
		}
		n++;
		x0 = x1;
	}
}
