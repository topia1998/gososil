#include "my_solver.h"

void practice3_2() {
	char readfile[256];
	char writefile[256];

	int NCOEF, DEGREE;

	double* poly;
	double* zeror, * zeroi;
	long int fail;
	int i;
	int result = 0;

	for (int t = 1; t <= 6; t++) {

		sprintf(readfile, "polynomial_3-2_%d.txt", t);
		sprintf(writefile, "roots_3-2_%d.txt", t);

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

		fscanf(fp_r, "%d", &DEGREE);
		NCOEF = DEGREE + 1;

		poly = (double*)malloc(sizeof(double) * NCOEF);
		zeror = (double*)malloc(sizeof(double) * DEGREE);
		zeroi = (double*)malloc(sizeof(double) * DEGREE);

		/********************************/
		for (i = 0; i < NCOEF; i++) {
			fscanf(fp_r, "%lf", &poly[i]);
		}
		rpoly_(poly, &DEGREE, zeror, zeroi, &fail);
		if (fail) {
			fprintf(fp_w, "fail\n");
		}
		else {
			fprintf(fp_w, "r: ");
			for (i = 0; i <  DEGREE; i++) 
				fprintf(fp_w, "%lf ", zeror[i]);	
			fprintf(fp_w, "\ni: ");
			for (i = 0; i < DEGREE; i++) {
				fprintf(fp_w, "%lf ", zeroi[i]);
			}
			fprintf(fp_w, "\n");
		}
		
		if (fail);
		else {
			fprintf(fp_w, "a: ");
			for (i = 0; i < DEGREE; i++) {
				double sum_r = 0;
				double sum_i;
				
				if (zeroi[i] == 0) {
					for (int j = 0; j < DEGREE + 1; j++) {
						sum_r += poly[j] * pow(zeror[i], DEGREE - j);
					}
					fprintf(fp_w, "%lf  ", sum_r);
				}
				else {
					for (int x = 0; x < DEGREE; x++) {
						sum_r = 0; sum_i = 0;
						for (int y = 0; y < DEGREE; y++) {
							double a = zeror[x], b = zeroi[x];
							for (int z = y; z < DEGREE; z++) {
								double c = a, d  = b;
								a = c * zeror[x] - d * zeroi[x];
								b = d * zeror[x] + c * zeroi[x];
							}
							sum_r += a * poly[y];
							sum_i += b * poly[y];
						}
					}
					if (sum_r + poly[DEGREE] == 0 && sum_i == 0) fprintf(fp_w, "%lf  ", 0);
					else fprintf(fp_w, "%lf  ", 0);
				}
			}
		}

		/********************************/
		free(zeroi);
		free(zeror);
		free(poly);

		if (fp_r != NULL) fclose(fp_r);
		if (fp_w != NULL) fclose(fp_w);
	}
}