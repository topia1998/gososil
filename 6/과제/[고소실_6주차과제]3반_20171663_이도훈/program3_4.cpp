#include "my_solver.h"
#define index_2d(row, col, dim) row+col*dim

void program3_4(void) {
	FILE* fp_r = fopen("linear_system_3-4.txt", "r");
	if (fp_r == NULL) {
		printf("linear_system_3-4.txt file open error...\n");
		return;
	}
	FILE* fp_w = fopen("solution_3-4.txt", "w");
	if (fp_w == NULL) {
		printf("solution_3-4.txt file open error...\n");
		return;
	}
	int ia, n, i, j;
	int* l;
	float* b;
	float* a;
	float* x;
	float* s;
	float* atmp;
	float* btmp;
	fscanf(fp_r, "%d", &n);
	ia = n;
	l = (int*)malloc(sizeof(int) * n);
	a = (float*)malloc(sizeof(float) * pow(n, 2));
	atmp = (float*)malloc(sizeof(float) * pow(n, 2));
	b = (float*)malloc(sizeof(float) * n);
	btmp = (float*)malloc(sizeof(float) * n);
	x = (float*)malloc(sizeof(float) * n);
	s = (float*)malloc(sizeof(float) * n);

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(fp_r, "%f", &a[index_2d(i, j, n)]);
			atmp[index_2d(i, j, n)] = a[index_2d(i, j, n)];
		}
	}
	for (i = 0; i < n; i++) {
		fscanf(fp_r, "%f", &b[i]);
		btmp[i] = b[i];
	}
	gespp_(&n, a, &ia, l, s);
	solve_(&n, a, &ia, l, b, x);

	fprintf(fp_w, "n : %d\n", n);
	for (i = 0; i < n; i++) {
		fprintf(fp_w, "x[%d] = %.6f\n", i, x[i]);
	}

	float ch, tmp1 = 0, tmp2 = 0, result;

	for (i = 0; i < n; i++) {
		ch = 0.0;
		for (j = 0; j < n; j++) {
			ch += atmp[index_2d(i, j, n)] * x[j];
		}
		ch -= btmp[i];
		tmp1 += pow(ch, 2);
	}
	for (int i = 0; i < n; i++) {
		tmp2 += pow(b[i], 2);
	}
	result = sqrt(tmp1) / sqrt(tmp2);

	fprintf(fp_w, "¿ÀÂ÷ : %.6f\n", result);
}