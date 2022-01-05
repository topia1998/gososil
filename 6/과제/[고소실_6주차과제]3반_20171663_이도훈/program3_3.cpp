#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_3_h(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	fvec[0] = (sin(x[0] * x[1] + M_PI / 6) + sqrt(x[0] * x[0] * x[1] * x[1] + 1)) + 2.8 * cos(x[0] - x[1]);
	fvec[1] = (x[0] * exp(x[0] * x[1] + M_PI / 6) - sin(x[0] - x[1])) - 1.66 * sqrt(x[0] * x[0] * x[1] * x[1] + 1);
	/********************************/
}

void program3_3(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { 16.0, 0.0 };	//need to initilize x0
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_found_3-3.txt", "w");
	if (fp_w == NULL) {
		fprintf(fp_w, "%s file open error...\n", "roots_found_3-3.txt");
		return;
	}

	/********************************/
	hybrd1_(fcn3_3_h, &n, x, fvec, &tol, &info, wa, &lwa);
	fprintf(fp_w, "(x, y) : %.10lf %.10lf\n", x[0], x[1]);
	fprintf(fp_w, "info : %d\n", info);
	fprintf(fp_w, "함수 1 : %.10lf\n", (sin(x[0] * x[1] + M_PI / 6) + sqrt(x[0] * x[0] * x[1] * x[1] + 1)) / cos(x[0] - x[1]) + 2.8);
	fprintf(fp_w, "함수 2 : %.10lf\n", (x[0] * exp(x[0] * x[1] + M_PI / 6) - sin(x[0] - x[1])) / sqrt(x[0] * x[0] * x[1] * x[1] + 1) - 1.66);
	/********************************/

	fclose(fp_w);
}