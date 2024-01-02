#include <stdio.h>
#include <stdlib.h>
#include "../include/Poker.h"

int main(void)
{
	int choose;
	printf("請選擇要玩十點半或21點 <1 for 10點半，2 for 21點>：");
	scanf("%d", &choose);
	if (choose == 1)
	{
		Poker_1();
	}
	else
		Poker_2();

	system("pause");
	printf("\n");
	return 0;
}