#include <stdio.h>
#include <string.h>
#include <random>
#include <time.h>

#include <math.h>
#include <time.h>
#include <Windows.h>

#define SIZE 20000

__int64 start, freq, end;
#define CHECK_TIME_START QueryPerformanceFrequency((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&end); a = (float)((float)(end - start) / (freq / 1000.0f))
float compute_time;
float compute_time1, compute_time2;


#define MATDIM 1024
#define HW1_N 100000
float *hw1_x, hw1_E, hw1_var1, hw1_var2;
float hw2_a, hw2_b, hw2_c, hw2_naive_ans[2], hw2_pre_ans[2];

/* hw1 */
void init_hw1(int fixed);
void hw1_calc_e();
void hw1_calc_var1();
void hw1_calc_var2();
/* hw2 */
void hw2_naive();
void hw2_safe();
float hw2_verify(float x);
/* hw3 */
void hw3_1();
void hw3_2();
void hw3_3();
void hw3_4();
void hw3_5();

void main(void)
{
	srand((unsigned)time(NULL));
	int d = 0;
	/* hw1 */
	puts("====== hw1 ======");
	init_hw1(d);
	printf("init_hw1(%d), HW1_N = %d\n", d, HW1_N);
	CHECK_TIME_START;
	hw1_calc_var1();
	CHECK_TIME_END(compute_time);
	compute_time1 = compute_time;
	printf("hw1_calc_var1 = %f ms\n", compute_time);
	printf("hw1_calc_var1 value = %.15f\n", hw1_var1);


	CHECK_TIME_START;
	hw1_calc_e();
	hw1_calc_var2();
	CHECK_TIME_END(compute_time);
	compute_time2 = compute_time;
	printf("hw1_calc_var2 = %f ms\n", compute_time);
	printf("hw1_calc_var2 value = %.15f\n", hw1_var2);
	puts("");
	
	/* hw2 */
	puts("====== hw2 ======");
	printf("a, b, c : ");
	scanf("%f %f %f", &hw2_a, &hw2_b, &hw2_c);
	hw2_naive();
	hw2_safe();
	printf("naive result    : %.15f, %.15f\n", hw2_naive_ans[0], hw2_naive_ans[1]);
	printf("advanced result : %.15f, %.15f\n", hw2_pre_ans[0], hw2_pre_ans[1]);
	puts("");
	printf("Verifying naive ans    : %.15f, %.15f\n", hw2_verify(hw2_naive_ans[0]), hw2_verify(hw2_naive_ans[1]));
	printf("Verifying advanced ans : %.15f, %.15f\n", hw2_verify(hw2_pre_ans[0]), hw2_verify(hw2_pre_ans[1]));
	puts("");

	/* hw3 */
	hw3_1();
	hw3_2();
	hw3_3();
	hw3_4();
	hw3_5();
}

void init_hw1(int fixed)
{
	float *ptr;
	hw1_x = (float *)malloc(sizeof(float)*HW1_N);

	if (fixed)
	{
		float tmp = HW1_N;
		for (int i = 0; i < HW1_N; i++)
		{
			if( i & 1) tmp -= 0.0001;
			hw1_x[i] = tmp;
		}
	}
	else
	{
		srand((unsigned)time(NULL));
		ptr = hw1_x;
		for (int i = 0; i < HW1_N; i++)
			*ptr++ = ((float)rand() / (float)RAND_MAX) * 2;
	}
}
void hw1_calc_e()
{
	hw1_E = 0.0;
	for (int i = 0; i < HW1_N; i++) {
		hw1_E += hw1_x[i];
	}
	hw1_E /= HW1_N;
}
void hw1_calc_var1()
{
	hw1_var1 = 0;
	double tmp1 = 0, tmp2 = 0;

	for (int i = 0; i < HW1_N; i++) {
		tmp1 += (double)(hw1_x[i] * hw1_x[i]);
		tmp2 += (double)hw1_x[i];
	}
	hw1_var1 = HW1_N * tmp1 - tmp2 * tmp2;
	hw1_var1 /= HW1_N * (HW1_N - 1);
}
void hw1_calc_var2()
{
	double tmp = 0.0;
	for (int i = 0; i < HW1_N; i++) {
		tmp += (double)(hw1_x[i] - hw1_E) * (double)(hw1_x[i] - hw1_E);
	}
	tmp /= (double)(HW1_N - 1);
	hw1_var2 = tmp;
}


/* hw2 */
void hw2_naive()
{
	double ans1 = 0, ans2 = 0;
	ans1 = -hw2_b + sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c);
	ans2 = -hw2_b - sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c);
	ans1 /= 2 * hw2_a;
	ans2 /= 2 * hw2_a;

	hw2_naive_ans[0] = ans1;
	hw2_naive_ans[1] = ans2;
}
void hw2_safe()
{
	double ans1 = 0, ans2 = 0;

	if (hw2_b >= 0) {
		ans1 = (-4) * hw2_a * hw2_c;
		ans1 /= (hw2_b + sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c));
		ans1 /= 2 * hw2_a;
		ans2 = (-hw2_b) - sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c);
		ans2 /= (2 * hw2_a);
	}
	else {
		ans1 = (-hw2_b) + sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c);
		ans1 /= (2 * hw2_a);
		ans2 = (-4) * hw2_a * hw2_c;
		ans2 /= (hw2_b - sqrt(hw2_b * hw2_b - 4 * hw2_a * hw2_c));
		ans2 /= 2 * hw2_a;
	}

	hw2_pre_ans[0] = ans1;
	hw2_pre_ans[1] = ans2;
}
float hw2_verify(float x)
{
	return hw2_a * x * x + hw2_b*x + hw2_c;
}

void hw3_1() {
	
	float** arr1;
	float** arr2;
	int i, j, ch = 1;

	printf("************************\n");
	printf("*   Loop Interchange   *\n");
	printf("************************\n");
	printf("The problem is using two nested loops of %d elements with specific iteration order...\n\n", SIZE);

	srand(time(NULL));

	arr1 = (float**)calloc(SIZE, sizeof(float*));
	arr2 = (float**)calloc(SIZE, sizeof(float*));

	for (i = 0; i < SIZE; i++) {
		arr1[i] = (float*)calloc(SIZE, sizeof(float));
	}
	for (i = 0; i < SIZE; i++) {
		arr2[i] = (float*)calloc(SIZE, sizeof(float));
	}

	CHECK_TIME_START;
	for (j = 0; j < SIZE; j++) {
		for (i = 0; i < SIZE; i++) {
			arr1[i][j] = i + i + j + j;
		}
	}
	CHECK_TIME_END(compute_time);
	printf("The runtime before loop interchange is %.3f(ms).\n", compute_time * 1000);

	CHECK_TIME_START;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			arr2[i][j] = i + j + i + j;
			if (arr1[i][j] != arr2[i][j]) ch = 0;
		}
	}
	CHECK_TIME_END(compute_time);
	printf("The runtime after loop interchange is %.3f(ms).\n", compute_time * 1000);

	if (ch == 1) printf("Two arrays have the same elements.\n");
	else printf("There are difference between two arrays.\n");

	free(arr1);
	free(arr2);
}

void hw3_2() {
	float* arr1 = (float*)calloc(SIZE, sizeof(float));
	float* arr2 = (float*)calloc(SIZE, sizeof(float));
	float* arr3 = (float*)calloc(SIZE, sizeof(float));
	float* arr4 = (float*)calloc(SIZE, sizeof(float));
	int i, p = SIZE - 1;

	printf("************************\n");
	printf("*   Loop Peeling   *\n");
	printf("************************\n");
	printf("The problem is using single loop of %d elements with specific iteration order...\n\n", SIZE);

	for (i = 0; i < SIZE; i++) {
		arr1[i] = i;
	}

	srand(time(NULL));


	CHECK_TIME_START;
	for (i = 0; i < SIZE; i++) {
		arr2[i] = arr1[i] + arr1[p];
		p = i;
	}
	CHECK_TIME_END(compute_time);
	printf("The runtime before loop peeling is %.3f(ms).\n", compute_time * 1000);

	CHECK_TIME_START;
	arr4[0] = arr3[0] + arr3[SIZE - 1];
	for (i = 1; i < SIZE; i++) {
		arr4[i] = arr3[i] + arr3[i - 1];
	}
	CHECK_TIME_END(compute_time);
	printf("The runtime after loop peeling is %.3f(ms).\n", compute_time * 1000);
	
	free(arr1); free(arr2); free(arr3); free(arr4);
}

void hw3_3() {
	float* arr1 = (float*)calloc(SIZE, sizeof(float));
	float* arr2 = (float*)calloc(SIZE, sizeof(float));
	float* arr3 = (float*)calloc(SIZE, sizeof(float));
	float* arr4 = (float*)calloc(SIZE, sizeof(float));
	int i = 0, w = 5, ch = 1;

	printf("************************\n");
	printf("*   Loop Unswitching   *\n");
	printf("************************\n");
	printf("The problem is using two loops of %d elements with specific iteration order...\n\n", SIZE);

	srand(time(NULL));

	for (i = 0; i < SIZE; i++) {
		arr2[i] = i + i;
		arr4[i] = i + i;
	}

	CHECK_TIME_START;
	for (i = 0; i < SIZE; i++) {
		arr1[i] += arr2[i];
		if (w > 0)
			arr2[i] = 0;
	}
	CHECK_TIME_END(compute_time);
	printf("The runtime before loop unswitching is %.3f(ms).\n", compute_time * 1000);

	CHECK_TIME_START;
	if (w > 0) {
		for (i = 0; i < SIZE; i++) {
			arr3[i] += arr4[i];
			arr4[i] = 0;
		}
	}
	else {
		for (i = 0; i < SIZE; i++) {
			arr3[i] += arr4[i];
		}
	}
	CHECK_TIME_END(compute_time);
	printf("The runtime after loop unswitching is %.3f(ms).\n", compute_time * 1000);

	for (i = 0; i < SIZE; i++) {
		if (arr3[i] != arr1[i]) ch = 0;
	}
	if (ch == 1) printf("Two arrays have the same elements.\n");
	else printf("There are difference between two arrays.\n");

	free(arr1); free(arr2); free(arr3); free(arr4);
}

void hw3_4() {
	float* arr1 = (float*)calloc(SIZE, sizeof(float));
	float* arr2 = (float*)calloc(SIZE, sizeof(float));
	float* arr3 = (float*)calloc(SIZE, sizeof(float));
	float* arr4 = (float*)calloc(SIZE, sizeof(float));
	int i = 0, ch = 1, tmp = 1;

	printf("************************\n");
	printf("*     Loop Fission     *\n");
	printf("************************\n");
	printf("The problem is using single loop of %d elements with specific iteration order...\n\n", SIZE);

	srand(time(NULL));

	CHECK_TIME_START;
	for (i = 0; i < SIZE; i++) {
		arr3[i] = 1;
	}
	for (i = 0; i < SIZE; i++) {
		arr4[i] = 2;
	}
	CHECK_TIME_END(compute_time);
	printf("The runtime before loop fission is %.3f(ms).\n", compute_time * 1000);

	CHECK_TIME_START;
	for (i = 0; i < SIZE; i++) {
		arr1[i] = 1;
		arr2[i] = 2;
	}
	CHECK_TIME_END(compute_time);
	printf("The runtime after loop fission is %.3f(ms).\n", compute_time * 1000);

	for (i = 0; i < SIZE; i++) {
		if (arr1[i] != arr3[i]) ch = 0;
		if (arr2[i] != arr4[i]) tmp = 0;
	}
	if (ch == 1 && tmp == 1) printf("Two arrays have the same elements.\n");
	else printf("There are difference between two arrays.\n");

	free(arr1); free(arr2); free(arr3); free(arr4);
}

void hw3_5() {
	float* arr1 = (float*)calloc(SIZE, sizeof(float));
	float* arr2 = (float*)calloc(SIZE, sizeof(float));
	int i, ch = 1;
	printf("************************\n");
	printf("*    Loop Splitting    *\n");
	printf("************************\n");
	printf("The problem is using single loop of %d elements with specific iteration order...\n\n", SIZE);

	srand(time(NULL));

	CHECK_TIME_START;
	for (i = 0; i < SIZE; i++) {
		arr1[i] = i * i + i;

	}
	CHECK_TIME_END(compute_time);
	printf("The runtime before loop splitting is %.3f(ms).\n", compute_time * 1000);

	CHECK_TIME_START;
	for (i = 0; i < 500; i++) {
		arr2[i] = i * i + i;
	}
	for (i = 500; i < 2000; i++) {
		arr2[i] = i * i + i;
	}
	for (i = 2000; i < 10000; i++) {
		arr2[i] = i * i + i;
	}
	for (i = 10000; i < SIZE; i++) {
		arr2[i] = i * i + i;
	}
	CHECK_TIME_END(compute_time);
	printf("The runtime after loop splitting is %.3f(ms).\n", compute_time * 1000);

	for (i = 0; i < SIZE; i++) {
		if (arr1[i] != arr2[i]) ch = 0;
	}
	if (ch == 1) printf("Two arrays have the same elements.\n");
	else printf("There are difference between two arrays.\n");

	free(arr1); free(arr2);
}