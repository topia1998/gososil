#include "my_solver.h"

#define SOLNUMS 3
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_4(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	// origin function F(x)
	if (*iflag == 1) {
		/********************************/
		fvec[0] = x[0] + x[1] + x[2] - 3;
		fvec[1] = x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 5;
		fvec[2] = exp(x[0]) + x[0] * x[1] - x[0] * x[2] - 1;
		/********************************/
	}
	// Jacobi matrix J(x)
	else if (*iflag == 2) {
		/********************************/
		fjac[0] = 1;						fjac[3] = 1;		fjac[6] = 1;
		fjac[1] = 2 * x[0];					fjac[4] = 2 * x[1];	fjac[7] = 2 * x[2];
		fjac[2] = exp(x[0]) + x[1] - x[2];	fjac[5] = x[0];		fjac[8] = -1 * x[0];
		/********************************/
	}
}

void practice3_4(void) {
	int n = SOLNUMS;
	double x[SOLNUMS] = { 0.1, 1.2, 2.5 };	//need to initilize x0
	double x2[SOLNUMS] = { 1.0, 0.0, 1.0 };
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

	FILE* fp_w = fopen("roots_3-4.txt", "w");
	if (fp_w == NULL) {
		fprintf(fp_w, "%s file open error...\n", "roots_3-4.txt");
		return;
	}

	/********************************/

	hybrj1_(fcn3_4, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
	fprintf(fp_w, "(0.1, 1.2, 2.5) : %.10lf %.10lf %.10lf\n", x[0], x[1], x[2]);
	fprintf(fp_w, "�Լ� 1 : %.10lf\n", x[0] + x[1] + x[2] - 3);
	fprintf(fp_w, "�Լ� 2 : %.10lf\n", x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 5);
	fprintf(fp_w, "�Լ� 3 : %.10lf\n", exp(x[0]) + x[0] * x[1] - x[0] * x[2] - 1);

	hybrj1_(fcn3_4, &n, x2, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);
	fprintf(fp_w, "(1.0, 0.0, 1.0) : %.10lf %.10lf %.10lf\n", x2[0], x2[1], x2[2]);
	fprintf(fp_w, "�Լ� 1 : %.10lf\n", x2[0] + x2[1] + x2[2] - 3);
	fprintf(fp_w, "�Լ� 2 : %.10lf\n", x2[0] * x2[0] + x2[1] * x2[1] + x2[2] * x2[2] - 5);
	fprintf(fp_w, "�Լ� 3 : %.10lf\n", exp(x2[0]) + x2[0] * x2[1] - x2[0] * x2[2] - 1);
	/********************************/

	fclose(fp_w);
}
