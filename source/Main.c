#include <stdio.h>
#include <stdlib.h>
#include "../include/Poker.h"

int main(void)
{
	int c;
	printf("Do you want to play \"10.30\" or \"21.\"(0/1):");
	scanf("%d", &c);

	switch (c) {
	case 0:
		Poker_1();
		break;
	case 1:
		Poker_2();
		break;
	default:
		printf("Enter 0 or 1\n");
	}
	
	
	system("pause");
	printf("\n");
	return 0;
}