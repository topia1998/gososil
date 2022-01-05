#include "my_solver.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

void program_2() {
	int num = 1000, size, i;
	double sum = 0, v = 0;
	double* x;
	double* r;
	srand((time(NULL)));
	x = (double*)malloc(sizeof(double) * num);
	r = (double*)malloc(sizeof(double) * num);
	double* l = (double*)malloc(sizeof(double) * 3);
	double* avg = (double*)malloc(sizeof(double) * 3);
	double* var = (double*)calloc(3, sizeof(double));
	for (i = 0; i < 3; i++) {
		scanf("%lf", &l[i]);
	}
	for (int j = 0; j < 3; j++) {
		i = 0;
		sum = 0;
		while (i < num) {
			while (1) {
				r[i] = rand() / (double)32767;
				if (r[i] != 0 && r[i] != 1) break;
			}
			x[i] = (log(1 - r[i]) * -1) / l[j];
			sum += x[i];
			i++;
		}
		avg[j] = sum / num;
		for (int k = 0; k < num; k++) {
			var[j] += (x[k] - avg[j]) * (x[k] - avg[j]);
		}
	}
	for (int j = 0; j < 3; j++) {
		printf("%.15lf %.15lf\n", avg[j], var[j] / num);
	}
}

// HOMEWORK
void program2_3()
{
	FILE* fp1;
	FILE* fp2;
	FILE* fp3;
	fp1 = fopen("pdf_table.txt", "r");
	fp2 = fopen("random_event_table.txt", "r");
	fp3 = fopen("histogram.txt", "w");
	int size;
	int result[10] = { 0, };
	fscanf(fp1, "%d", &size);
	double* ran = (double*)calloc(size, sizeof(double));
	for (int i = 0; i < size; i++) {
		fscanf(fp2, "%lf", &ran[i]);
	}
	for (int i = 0; i < size; i++) {
		if (0 < ran[i] && ran[i] < 0.1) result[0]++;
		else if (0.1 <= ran[i] && ran[i] < 0.2) result[1]++;
		else if (0.2 <= ran[i] && ran[i] < 0.3) result[2]++;
		else if (0.3 <= ran[i] && ran[i] < 0.4) result[3]++;
		else if (0.4 <= ran[i] && ran[i] < 0.5) result[4]++;
		else if (0.5 <= ran[i] && ran[i] < 0.6) result[5]++;
		else if (0.6 <= ran[i] && ran[i] < 0.7) result[6]++;
		else if (0.7 <= ran[i] && ran[i] < 0.8) result[7]++;
		else if (0.8 <= ran[i] && ran[i] < 0.9) result[8]++;
		else if (0.9 <= ran[i] && ran[i] < 1) result[9]++;
	}
	for (int i = 0; i < 10; i++) {
		if (i == 9) fprintf(fp3, "0.%d ~ %d.0 :%3d\t", i, i - 8, result[i]);
		else fprintf(fp3, "0.%d ~ 0.%d :%3d\t", i, i + 1, result[i]);
		for (int j = 0; j < size; j++) {
			if (i == 0 && 0 < ran[j] && ran[j] < 0.1) fprintf(fp3, "%lf ", ran[j]);
			else if (i == 1 && 0.1 <= ran[j] && ran[j] < 0.2) fprintf(fp3, "%lf ", ran[j]);
			else if (i == 2 && 0.2 <= ran[j] && ran[j] < 0.3) fprintf(fp3, "%lf ", ran[j]);
			else if (i == 3 && 0.3 <= ran[j] && ran[j] < 0.4) fprintf(fp3, "%lf ", ran[j]);
			else if (i == 4 && 0.4 <= ran[j] && ran[j] < 0.5) fprintf(fp3, "%lf ", ran[j]);
			else if (i == 5 && 0.5 <= ran[j] && ran[j] < 0.6) fprintf(fp3, "%lf ", ran[j]);
			else if (i == 6 && 0.6 <= ran[j] && ran[j] < 0.7) fprintf(fp3, "%lf ", ran[j]);
			else if (i == 7 && 0.7 <= ran[j] && ran[j] < 0.8) fprintf(fp3, "%lf ", ran[j]);
			else if (i == 8 && 0.8 <= ran[j] && ran[j] < 0.9) fprintf(fp3, "%lf ", ran[j]);
			else if (i == 9 && 0.9 <= ran[j] && ran[j] < 1) fprintf(fp3, "%lf ", ran[j]);
		}
		fprintf(fp3, "\n");
	}
}

// HOMEWORK
void program2_2_a()
{
	__int64 start, freq, end;
	float resultTime = 0;

	CHECK_TIME_START;
	FILE* fp_r, * fp_w;
	FILE* fp3;
	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");
	fp3 = fopen("histogram.txt", "w");
	int num, size, i, j;
	int result[10] = { 0, };
	int result2[30] = { 0, };
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
			if (r[i] != 0 && r[i] != 1) {
				break;
			}
			
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
		while (j < size - 1) {
			if (x0 >= x[j] && x0 <= x[j + 1]) break;
			j++;
		}
		double ch = (y[j] + (y[j + 1] - y[j]) * (x0 - x[j]) / (x[j + 1] - x[j]) / 2) * (x0 - x[j]);
		fx0 = ch + cdf[j] - r[i];
		if (fs * fx0 < 0) {
			e = x0;
			fe = fx0;
		}
		else if (fs * fx0 > 0) {
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

	CHECK_TIME_END(resultTime);

	printf("The program2_2_a run time is %f(ms)..\n", resultTime * 1000.0);
}

void program2_2_b()
{
	FILE* fp_r, * fp_w;

	fp_r = fopen("pdf_table.txt", "r");
	fp_w = fopen("random_event_table.txt", "w");
	__int64 start, freq, end;
	float resultTime = 0;

	CHECK_TIME_START;

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
		x0 = e - fe * (e - s) / (fe - fs);
		j = 0;
		while (j < size - 1) {
			if (x0 >= x[j] && x0 <= x[j + 1]) break;
			j++;
		}
		double ch = (y[j] + (y[j + 1] - y[j]) * (x0 - x[j]) / (x[j + 1] - x[j]) / 2) * (x0 - x[j]);
		fx0 = ch + cdf[j] - r[i];
		if (fs * fx0 < 0) {
			e = x0;
			fe = fx0;
		}
		else if (fs * fx0 > 0) {
			s = x0;
			fs = fx0;
		}
		while (n < Nmax) {
			x1 = e - fe * (e - s) / (fe - fs);
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
	CHECK_TIME_END(resultTime);

	printf("The program2_2_b run time is %f(ms)..\n", resultTime * 1000.0);
}