#include "my_solver.h"

extern float (*_sp_f)(float);
extern float (*_sp_fp)(float);

/*********************************************
  Secant Method
**********************************************/
void sp_program1_2(FILE* fp) {
	float x0, x1, temp;
	int n = 0;

	if (fp == NULL)
		return;
	scanf("%f %f", &x0, &x1);
	fprintf(fp, "n\txn1\t\t\t|f(xn1)|\n");
	fprintf(fp, "input : %f\n", x0);
	while (n < Nmax) {
		if (n == 0) fprintf(fp, "%2d %.15e %.15e\n", n, x0, fabs(_sp_f(x0)));
		else if (n == 1) fprintf(fp, "%2d %.15e %.15e\n", n, x1, fabs(_sp_f(x1)));
		else if (n >= 2) {
			temp = x1 - _sp_f(x1) * (x1 - x0) / (_sp_f(x1) - _sp_f(x0));
			fprintf(fp, "%2d %.15e %.15e\n", n, temp, fabs(_sp_f(temp)));
			if (fabs(_sp_f(temp)) < DELTA) return;
			if (n >= Nmax) return;
			if (fabs(temp - x1) < EPSILON) return;

			x0 = x1;
			x1 = temp;
		}
		n++;
	}
}
