#include "my_solver.h"

#define SOLNUMS 2
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_6(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag) {
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/
		fvec[0] = 3 * x[0] * x[0] - 2 * x[1] * x[1] - 1;
		fvec[1] = x[0] * x[0] - 2 * x[0] + x[1] * x[1] + 2 * x[1] - 8;
		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/
		fjac[0] = 6 * x[0];		fjac[2] = -4 * x[1];
		fjac[1] = 2 * x[0] - 2;	fjac[3] = 2 * x[1] + 2;
		/********************************/
	}
}

void practice3_6(void)
{
	int n = SOLNUMS;
	double x[SOLNUMS] = { -4.0, 5.0 };	//need to initilize x0
	double x2[SOLNUMS] = { 4.0, 5.0 };
	double x3[SOLNUMS] = { 4.0, -5.0 };
	double x4[SOLNUMS] = { -4.0, -5.0 };
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-6.txt", "w");
	if (fp_w == NULL) {
		fprintf(fp_w, "%s file open error...\n", "roots_3-6.txt");
		return;
	}

	/********************************/
	hybrj1_(fcn3_6, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
	fprintf(fp_w, "(-4.0, 5.0) : %.10lf %.10lf\n", x[0], x[1]);
	fprintf(fp_w, "함수 1 : %.10lf\n", 3 * x[0] * x[0] - 2 * x[1] * x[1] - 1);
	fprintf(fp_w, "함수 2 : %.10lf\n", x[0] * x[0] - 2 * x[0] + x[1] * x[1] + 2 * x[1] - 8);

	hybrj1_(fcn3_6, &n, x2, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
	fprintf(fp_w, "(4.0, 5.0) : %.10lf %.10lf\n", x2[0], x2[1]);
	fprintf(fp_w, "함수 1 : %.10lf\n", 3 * x2[0] * x2[0] - 2 * x2[1] * x2[1] - 1);
	fprintf(fp_w, "함수 2 : %.10lf\n", x2[0] * x2[0] - 2 * x2[0] + x2[1] * x2[1] + 2 * x2[1] - 8);

	hybrj1_(fcn3_6, &n, x3, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
	fprintf(fp_w, "(4.0, -5.0) : %.10lf %.10lf\n", x3[0], x3[1]);
	fprintf(fp_w, "함수 1 : %.10lf\n", 3 * x3[0] * x3[0] - 2 * x3[1] * x3[1] - 1);
	fprintf(fp_w, "함수 2 : %.10lf\n", x3[0] * x3[0] - 2 * x3[0] + x3[1] * x3[1] + 2 * x3[1] - 8);

	hybrj1_(fcn3_6, &n, x4, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
	fprintf(fp_w, "(-4.0, -5.0) : %.10lf %.10lf\n", x4[0], x4[1]);
	fprintf(fp_w, "함수 1 : %.10lf\n", 3 * x4[0] * x4[0] - 2 * x4[1] * x4[1] - 1);
	fprintf(fp_w, "함수 2 : %.10lf\n", x4[0] * x4[0] - 2 * x4[0] + x4[1] * x4[1] + 2 * x4[1] - 8);
	/********************************/

	fclose(fp_w);
}