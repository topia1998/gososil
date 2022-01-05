#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_7(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	fvec[0] = 2 * x[0] * x[0] * x[0] - 12 * x[0] - x[1] - 1;
	fvec[1] = 3 * x[1] * x[1] - 6 * x[1] - x[0] - 3;
	/********************************/
}

void practice3_7(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { -4.0, 5.0 };	//need to initilize x0
	double x2[SOLNUMS] = { 4.0, 5.0 };
	double x3[SOLNUMS] = { 4.0, -5.0 };
	double x4[SOLNUMS] = { -4.0, -5.0 };
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-7.txt", "w");
	if (fp_w == NULL) {
		fprintf(fp_w, "%s file open error...\n", "roots_3-7.txt");
		return;
	}

	/********************************/
	hybrd1_(fcn3_7, &n, x, fvec, &tol, &info, wa, &lwa);
	fprintf(fp_w, "(-4.0, 5.0) : %.10lf %.10lf\n", x[0], x[1]);
	fprintf(fp_w, "함수 1 : %.10lf\n", 2 * x[0] * x[0] * x[0] - 12 * x[0] - x[1] - 1);
	fprintf(fp_w, "함수 2 : %.10lf\n", 3 * x[1] * x[1] - 6 * x[1] - x[0] - 3);

	hybrd1_(fcn3_7, &n, x2, fvec, &tol, &info, wa, &lwa);
	fprintf(fp_w, "(4.0, 5.0) : %.10lf %.10lf\n", x2[0], x2[1]);
	fprintf(fp_w, "함수 1 : %.10lf\n", 2 * x2[0] * x2[0] * x2[0] - 12 * x2[0] - x2[1] - 1);
	fprintf(fp_w, "함수 2 : %.10lf\n", 3 * x2[1] * x2[1] - 6 * x2[1] - x2[0] - 3);

	hybrd1_(fcn3_7, &n, x3, fvec, &tol, &info, wa, &lwa);
	fprintf(fp_w, "(4.0, -5.0) : %.10lf %.10lf\n", x3[0], x3[1]);
	fprintf(fp_w, "함수 1 : %.10lf\n", 2 * x3[0] * x3[0] * x3[0] - 12 * x3[0] - x3[1] - 1);
	fprintf(fp_w, "함수 2 : %.10lf\n", 3 * x3[1] * x3[1] - 6 * x3[1] - x3[0] - 3);

	hybrd1_(fcn3_7, &n, x4, fvec, &tol, &info, wa, &lwa);
	fprintf(fp_w, "(-4.0, -5.0) : %.10lf %.10lf\n", x4[0], x4[1]);
	fprintf(fp_w, "함수 1 : %.10lf\n", 2 * x4[0] * x4[0] * x4[0] - 12 * x4[0] - x4[1] - 1);
	fprintf(fp_w, "함수 2 : %.10lf\n", 3 * x4[1] * x4[1] - 6 * x4[1] - x4[0] - 3);
	/********************************/

	fclose(fp_w);
}