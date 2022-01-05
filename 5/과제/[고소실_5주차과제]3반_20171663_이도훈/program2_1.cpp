#include "my_solver.h"

void program2_1()
{
	FILE* fp_r, *fp_w;
	__int64 start, freq, end;
	float resultTime = 0;

	fp_r = fopen("sampling_table.txt", "r");
	if (fp_r == NULL) {
		printf("input file not found....\n");
		exit(0);
	}

	fp_w = fopen("pdf_table.txt", "w");

	double r1 = 0, r2 = 0, r3 = 0, r4 = 0;
	int size;
	double h, sum = 0;
	double* x;
	double* y;
	double ch = 0;
	/***************************************************/
	fscanf(fp_r, "%d %lf", &size, &h);
	x = (double*)malloc(sizeof(double) * size);
	y = (double*)malloc(sizeof(double) * size);
	for (int i = 0; i < size; i++) {
		fscanf(fp_r, "%lf %lf", &x[i], &y[i]);
		x[i] = (x[i] - 24) / 560;
	}
	for (int i = 0; i < size - 1; i++) {
		sum = sum + ((y[i] + y[i + 1]) * (x[i + 1] - x[i]) / 2);
	}
	for (int i = 0; i < size; i++) {
		y[i] = y[i] / sum;
	}
	fprintf(fp_w, "%d %lf\n", size, x[1] - x[0]);
	for (int i = 0; i < size; i++) {
		fprintf(fp_w, "%lf %lf\n", x[i], y[i]);
	}
	for (int i = 0; i < size - 1; i++) {
		r1 += ((y[i] + y[i + 1]) * (x[i + 1] - x[i]) / 2);
		if (i == 25) r2 = r1 + (y[i] + (y[i + 1] - y[i]) / (x[i + 1] - x[i])) * (0.25 - x[i]) / 2 * (0.25 - x[i]);
		if (i == 50) r3 = r1 - r2 + (y[i] + (y[i + 1] - y[i]) / (x[i + 1] - x[i])) * (0.5 - x[i]) / 2 * (0.5 - x[i]);
		if (i == 75) r4 = r1 - r2 - r3 + (y[i] + (y[i + 1] - y[i]) / (x[i + 1] - x[i])) * (0.75 - x[i]) / 2 * (0.75 - x[i]);
	}
	printf("*** Integrating the pdf from 0.0 to 1.0 = %lf\n", r1);
	printf("*** Integrating the pdf from 0.0 to 0.25 = %lf\n", r2);
	printf("*** Integrating the pdf from 0.25 to 0.5 = %lf\n", r3);
	printf("*** Integrating the pdf from 0.5 to 0.75 = %lf\n", r4);
	printf("*** Integrating the pdf from 0.75 to 1.0 = %lf\n", r1 - r4 - r3 - r2);
	/***************************************************/

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
