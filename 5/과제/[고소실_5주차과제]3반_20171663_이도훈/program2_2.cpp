#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

void program2_2()
{
	FILE* fp_r, *fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");

	int num, size, i, j;
	double h, tmp;
	double* cdf;
	double* f;
	double* x;
	double* y;
	double* r;
	srand((time(NULL)));
	scanf("%d", &num);
	fscanf(fp_r, "%d %lf", &size, &h);
	x = (double*)malloc(sizeof(double) * size);
	y = (double*)malloc(sizeof(double) * size);
	cdf = (double*)malloc(sizeof(double) * size);
	f = (double*)malloc(sizeof(double) * size);
	r = (double*)malloc(sizeof(double) * num);
	for (i = 0; i < size; i++) {
		fscanf(fp_r, "%lf %lf", &x[i], &y[i]);
	}
	i = 0;
	while (i < size) {
		tmp = 0;
		j = 0;
		while (j <= i) {
			tmp += y[j];
			j++;
		}
		j = 1;
		while (j <= i - 1) {
			tmp += y[j];
			j++;
		}
		cdf[i] = tmp * h / 2;
		i++;
	}
	i = 0;
	while (i < num) {
		while (1) {
			r[i] = rand() / (double)32767;
			if (r[i] != 0 && r[i] != 1) break;
		}
		i++;
	}
	i = 0;
	while (i < num) {
		j = 0;
		while (j < size) {
			f[j] = cdf[j] - r[i];
			j++;
		}
		i++;
	}
	i = 0;
	while (i < num) {
		double s, e, x0, x1, fs, fe, fx0, fx1;
		int n = 0;
		s = x[0];
		fs = f[0];
		e = x[size - 1];
		fe = f[size - 1];
		x0 = (s + e) / 2;
		j = 0;
		while(j < size - 1) {
			if (x0 >= x[j] && x0 <= x[j + 1]) break;
			j++;
		}
		double ch = (y[j] + (y[j + 1] - y[j]) * (x0 - x[j]) / (x[j + 1] - x[j]) / 2) * (x0 - x[j]);
		fx0 = ch + cdf[j] - r[i];
		if (fs * fx0 < 0){
			e = x0;
			fe = fx0;
		}
		else if (fs * fx0 > 0){
			s = x0;
			fs = fx0;
		}
		while (n < Nmax) {
			x1 = (s + e) / 2;
			j = 0;
			while (j < size - 1) {
				if (x1 >= x[j] && x1 <= x[j + 1]) break;
				j++;
			}
			double ch = (y[j] + (y[j + 1] - y[j]) * (x1 - x[j]) / (x[j + 1] - x[j]) / 2) * (x1 - x[j]);
			fx1 = ch + cdf[j] - r[i];
			if (fs * fx1 < 0) {
				e = x1;
				fe = fx1;

			}
			else if (fs * fx1 > 0) {
				s = x1;
				fs = fx1;
			}
			if (fabs(fx1) < DELTA) {
				fprintf(fp_w, "%.15lf\n", x1);
				break;
			}
			if (n >= Nmax) {
				fprintf(fp_w, "%.15lf\n", x1);
				break;
			}
			if (fabs(x1 - x0) < EPSILON) {
				fprintf(fp_w, "%.15lf\n", x1);
				break;
			}
			n++;
			x0 = x1;
		}
		i++;
	}
	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
