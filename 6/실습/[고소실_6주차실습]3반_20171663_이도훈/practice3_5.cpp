#include "my_solver.h"

#define SOLNUMS 3
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_5(int* n, double* x, double* fvec, int* iflag)
{
	/********************************/
	fvec[0] = 10 * x[0] - 2 * x[1] * x[1] + x[1] - 2 * x[2] - 5;
	fvec[1] = 8 * x[1] * x[1] + 4 * x[2] * x[2] - 9;
	fvec[2] = 8 * x[1] * x[2] + 4;
	/********************************/
}

void practice3_5(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { 1.0, -1.0, 1.0 };	//need to initilize x0
	double x2[SOLNUMS] = { 1.0, 1.0, -1.0 };
	double fvec[SOLNUMS];
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-5.txt", "w");
	if (fp_w == NULL) {
		fprintf(fp_w, "%s file open error...\n", "roots_3-5.txt");
		return;
	}

	/********************************/
	hybrd1_(fcn3_5, &n, x, fvec, &tol, &info, wa, &lwa);
	fprintf(fp_w, "(1.0, -1.0, 1.0) : %.10lf %.10lf %.10lf\n",x[0], x[1], x[2]);
	fprintf(fp_w, "함수 1 : %.10lf\n", 10 * x[0] - 2 * x[1] * x[1] + x[1] - 2 * x[2] - 5);
	fprintf(fp_w, "함수 2 : %.10lf\n", 8 * x[1] * x[1] + 4 * x[2] * x[2] - 9);
	fprintf(fp_w, "함수 3 : %.10lf\n", 8 * x[1] * x[2] + 4);

	hybrd1_(fcn3_5, &n, x2, fvec, &tol, &info, wa, &lwa);
	fprintf(fp_w, "(1.0, 1.0, -1.0) : %.10lf %.10lf %.10lf\n",x2[0], x2[1], x2[2]);
	fprintf(fp_w, "함수 1 : %.10lf\n", 10 * x2[0] - 2 * x2[1] * x2[1] + x2[1] - 2 * x2[2] - 5);
	fprintf(fp_w, "함수 2 : %.10lf\n", 8 * x2[1] * x2[1] + 4 * x2[2] * x2[2] - 9);
	fprintf(fp_w, "함수 3 : %.10lf\n", 8 * x2[1] * x2[2] + 4);
	/********************************/

	fclose(fp_w);
}