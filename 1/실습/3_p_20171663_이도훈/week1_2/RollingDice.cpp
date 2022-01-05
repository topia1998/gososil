#include "pch.h"
#include "tipsware.h"
#include "time.h"
#define _USE_MATH_DEFINES
#include "math.h"

NOT_USE_MESSAGE

#define MAX_TRY 100

int main()
{
	//srand(time(NULL));

	SelectPenObject(RGB(0, 0, 0));

	int hit = 0;
	int miss = 0;
	float relProb = 5.0 / 36.0;
	float prob = 0;
	
	// TODO 
	for (int i = 0; i < 10000; i++) {
		int num1 = rand() % 6 + 1;
		int num2 = rand() % 6 + 1;

		if (num1 + num2 == 8) {
			TextOut(120 * (i / 20), 20 * (i % 20), "try %d: %d,%d (hit!)", 1 + i, num1, num2);
			prob++;
		}
		else {
			TextOut(120 * (i / 20), 20 * (i % 20), "try %d: %d,%d", 1 + i, num1, num2);
		}
	}
	
	
	//

	SetTextColor(RGB(128, 0, 0));
	// 실제 주사위 값
	TextOut(0, 420, "실제 값: %.6f", relProb);
	// 계산된 값
	TextOut(0, 440, "계산된 값: %.6f", prob / 10000);

	ShowDisplay();

	return 0;
}
