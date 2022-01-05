#include "my_solver.h"
#include <stdio.h>
#include <math.h>

double p1[4], p2[4], p3[4], p4[4], t[4], tr[4];
double c, b;

#define SOLNUMS 4
#define MATCOLS SOLNUMS
#define MATROWS SOLNUMS
#define TOLERANCE 0.0000001

void fcn3_1_h(int* n, double* x, double* fvec, double* fjac, int* ldfjac, int* iflag)
{
	if (*iflag == 1) {
		fvec[0] = pow((x[0] - p1[0]), 2) + pow((x[1] - p2[0]), 2) + pow(x[2] - p3[0], 2) - pow((c * (tr[0] + x[3] - t[0])), 2);
		fvec[1] = pow((x[0] - p1[1]), 2) + pow((x[1] - p2[1]), 2) + pow(x[2] - p3[1], 2) - pow((c * (tr[1] + x[3] - t[1])), 2);
		fvec[2] = pow((x[0] - p1[2]), 2) + pow((x[1] - p2[2]), 2) + pow(x[2] - p3[2], 2) - pow((c * (tr[2] + x[3] - t[2])), 2);
		fvec[3] = pow((x[0] - p1[3]), 2) + pow((x[1] - p2[3]), 2) + pow(x[2] - p3[3], 2) - pow((c * (tr[3] + x[3] - t[3])), 2);
	}
	else if (*iflag == 2) {
		fjac[0] = 2 * (x[0] - p1[0]);	fjac[4] = 2 * (x[1] - p2[0]);	fjac[8] = 2 * (x[2] - p3[0]);	fjac[12] = -2 * c * c * (tr[0] + x[3] - t[0]);
		fjac[1] = 2 * (x[0] - p1[1]);	fjac[5] = 2 * (x[1] - p2[1]);	fjac[9] = 2 * (x[2] - p3[1]);	fjac[13] = -2 * c * c *(tr[1] + x[3] - t[1]);
		fjac[2] = 2 * (x[0] - p1[2]);	fjac[6] = 2 * (x[1] - p2[2]);	fjac[10] = 2 * (x[2] - p3[2]);	fjac[14] = -2 * c * c * (tr[2] + x[3] - t[2]);
		fjac[3] = 2 * (x[0] - p1[3]);	fjac[7] = 2 * (x[1] - p2[3]);	fjac[11] = 2 * (x[2] - p3[3]);	fjac[15] = -2 * c * c * (tr[3] + x[3] - t[3]);
	}
}

void fcn3_1_d(int* n, double* x, double* fvec, int* iflag)
{
	if (*iflag == 1) {
		fvec[0] = pow((x[0] - p1[0]), 2) + pow((x[1] - p2[0]), 2) + pow(x[2] - p3[0], 2) - pow((c * (tr[0] + x[3] - t[0])), 2);
		fvec[1] = pow((x[0] - p1[1]), 2) + pow((x[1] - p2[1]), 2) + pow(x[2] - p3[1], 2) - pow((c * (tr[1] + x[3] - t[1])), 2);
		fvec[2] = pow((x[0] - p1[2]), 2) + pow((x[1] - p2[2]), 2) + pow(x[2] - p3[2], 2) - pow((c * (tr[2] + x[3] - t[2])), 2);
		fvec[3] = pow((x[0] - p1[3]), 2) + pow((x[1] - p2[3]), 2) + pow(x[2] - p3[3], 2) - pow((c * (tr[3] + x[3] - t[3])), 2);
	}
}

void program3_1(void)
{
	char readfile[256];
	char writefile[256];

	double* poly;
	double* zeror, * zeroi;
	long int fail;
	int i;
	int result = 0;
	double x[SOLNUMS];

	int n = SOLNUMS;
	double fvec[SOLNUMS], fjac[MATCOLS * MATROWS];
	int ldfjac = SOLNUMS;
	double tol = TOLERANCE;
	int info;
	double wa[(SOLNUMS * (SOLNUMS + 13)) / 2];
	int lwa = (SOLNUMS * (SOLNUMS + 13)) / 2;

	for (i = 0; i < 3; i++) {
		sprintf(readfile, "GPS_signal_%d.txt", i);
		sprintf(writefile, "GPS_position_3-1_%d.txt", i);
		
		FILE* fp_r = fopen(readfile, "r");
		if (fp_r == NULL) {
			printf("%s file open error...\n", readfile);
			return;
		}

		FILE* fp_w = fopen(writefile, "w");
		if (fp_w == NULL) {
			printf("%s file open error...\n", writefile);
			return;
		}
		fscanf(fp_r, "%lf %lf", &c, &b);
		fscanf(fp_r, "%lf %lf %lf %lf %lf", &p1[0], &p2[0], &p3[0], &t[0], &tr[0]);
		fscanf(fp_r, "%lf %lf %lf %lf %lf", &p1[1], &p2[1], &p3[1], &t[1], &tr[1]);
		fscanf(fp_r, "%lf %lf %lf %lf %lf", &p1[2], &p2[2], &p3[2], &t[2], &tr[2]);
		fscanf(fp_r, "%lf %lf %lf %lf %lf", &p1[3], &p2[3], &p3[3], &t[3], &tr[3]);
		scanf("%lf %lf %lf", &x[0], &x[1], &x[2]);
		x[3] = b;

		hybrj1_(fcn3_1_h, &n, x, fvec, fjac, &ldfjac, &tol, &info, wa, &lwa);

		fprintf(fp_w, "------------------hybrj-----------------------\n");
		fprintf(fp_w, "(x0, x1, x2, x3) : %lf %lf %lf %lf\n", x[0], x[1], x[2], x[3]);
		fprintf(fp_w, "|f1| : %lf\n", fabs(pow((x[0] - p1[0]), 2) + pow((x[1] - p2[0]), 2) + pow(x[2] - p3[0], 2) - pow((c * (tr[0] + x[3] - t[0])), 2)));
		fprintf(fp_w, "|f2| : %lf\n", fabs(pow((x[0] - p1[1]), 2) + pow((x[1] - p2[1]), 2) + pow(x[2] - p3[1], 2) - pow((c * (tr[1] + x[3] - t[1])), 2)));
		fprintf(fp_w, "|f3| : %lf\n", fabs(pow((x[0] - p1[2]), 2) + pow((x[1] - p2[2]), 2) + pow(x[2] - p3[2], 2) - pow((c * (tr[2] + x[3] - t[2])), 2)));
		fprintf(fp_w, "|f4| : %lf\n", fabs(pow((x[0] - p1[3]), 2) + pow((x[1] - p2[3]), 2) + pow(x[2] - p3[3], 2) - pow((c * (tr[3] + x[3] - t[3])), 2)));
		
		double wa2[(SOLNUMS * (3 * SOLNUMS + 13)) / 2];
		int lwa2 = (SOLNUMS * (3 * SOLNUMS + 13)) / 2;
		hybrd1_(fcn3_1_d, &n, x, fvec, &tol, &info, wa2, &lwa2);
		fprintf(fp_w, "------------------hybrd----------------------\n");
		fprintf(fp_w, "(x0, x1, x2, x3) : %lf %lf %lf %lf\n", x[0], x[1], x[2], x[3]);
		fprintf(fp_w, "|f1| : %lf\n", fabs(pow((x[0] - p1[0]), 2) + pow((x[1] - p2[0]), 2) + pow(x[2] - p3[0], 2) - pow((c * (tr[0] + x[3] - t[0])), 2)));
		fprintf(fp_w, "|f2| : %lf\n", fabs(pow((x[0] - p1[1]), 2) + pow((x[1] - p2[1]), 2) + pow(x[2] - p3[1], 2) - pow((c * (tr[1] + x[3] - t[1])), 2)));
		fprintf(fp_w, "|f3| : %lf\n", fabs(pow((x[0] - p1[2]), 2) + pow((x[1] - p2[2]), 2) + pow(x[2] - p3[2], 2) - pow((c * (tr[2] + x[3] - t[2])), 2)));
		fprintf(fp_w, "|f4| : %lf\n", fabs(pow((x[0] - p1[3]), 2) + pow((x[1] - p2[3]), 2) + pow(x[2] - p3[3], 2) - pow((c * (tr[3] + x[3] - t[3])), 2)));
	}
}