#include <stdio.h>
#include <stdlib.h>
#include "../include/Poker.h"

int main(void)
{
	int choose;
	printf("�п�ܭn���Q�I�b��21�I <1 for 10�I�b�A2 for 21�I>�G");
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