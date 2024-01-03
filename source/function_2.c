#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable : 4996)

const char *suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
const char *face[13] = { "1","2", "3", "4", "5", "6", "7", "8", "9", "10", "10", "10", "10" };

void shuffle(int wDeck[][13]);
void deal(const int wDeck[][13], const char *wFace[], const char *wSuit[]);
void play(int *playerMoney);
int faceResult[52] = { 0 };
char suitResult[52][10];
int getTotal(int handStart, int handEnd);
int getDecision();
void getResult(int dealerTotal, int playerTotal, int bet, int *playerMoney);
void printPoints(int dealerTotal, int playerTotal);
void rule();

int Poker_2() {
	int playerMoney;
	int response;

	do {
		int deck[4][13] = { 0 };
		srand((unsigned int)time(NULL));
		shuffle(deck);
		deal(deck, face, suit);
		rule();

		printf("Enter your money: ");
		scanf("%d", &playerMoney);

		play(&playerMoney);

		printf("\n-----------------------\n");
		printf("Player's Money: $%d\n", playerMoney);
		printf("Play again? (y:0/n:1): ");
		scanf("%d", &response);
	} while (response == 0 && playerMoney > 0);

	printf("-----------------------\n");
	printf("Thanks for playing!\n");

	system("pause");
	return 0;
}

void rule() {
	printf("-----------------------------welcome to BlackJack------------------------------\n\n");
	printf("�D���a(player) �M���a(dealer) ���y�q�P�襤���i�P�Adealer ���Ĥ@�i�P�O�\���C\n");
	printf("�D���� player �i�H�M�w�~��V���a�s�P(hit)\n");
	printf("�C�p�G�s�P�H�᪱�a���I�ƶW�L 21 �I�A�٬��z�P�A�åB���W�鱼�o�@��\n");
	printf("�D�p�G player ���Q�s�P�A�h����ܰ��P(stand)\n");
	printf("�D�p�G���a�S���z�P�B���P��A�N������a�}�P�ɵP�C\n");
	printf("�C���a���ݭn���ۤv�ɵP��j�󵥩� 17 �H�W�A���U�Ӫ��ɵP�A�������I�Ʀөw�C\n");
	printf("�D�p�G���賣�S���z�P�A�h�I�Ƥj����ӡC(���D���W�w�I�ƬۦP�� dealer ���)\n\n");
	printf("------------------------------------start--------------------------------------\n");
}

void play(int *playerMoney) {
	int bet;
	int dealerTotal, playerTotal;

	do {
		printf("Player's Money: $%d\n", *playerMoney);
		printf("Place your bet: ");
		scanf("%d", &bet);

		if (bet > *playerMoney || bet <= 0)
			printf("Error! Your bet must between 1 and %d.\n", *playerMoney);
	} while (bet > *playerMoney || bet <= 0);

	int hand = 2;
	int choice;
	int hit = hand + 2;

	printf("-------------------------------------------------------------------------------\n");
	printf("Dealer : ");
	for (int i = 0; i < hand; i++)
		if (i == 0) printf("%2d of %-8s\n", faceResult[i], suitResult[i]);
	dealerTotal = getTotal(0, hand);

	printf("\nPlayer : ");
	for (int i = hand; i < hand + 2; i++)
		if (i == hand) printf("%2d of %-8s\n", faceResult[i], suitResult[i]);
		else printf("%-2c%2d of %-8s\n\n", '\t', faceResult[i], suitResult[i]);
	playerTotal = getTotal(hand, hand + 2);

	printf("Dealer first: %d\n", faceResult[0]);
	printf("Player Total: %d\n\n", playerTotal);

	do {
		choice = getDecision();
		if (choice == 0) {
			printf("Player : ");
			for (int i = hand; i < hit; i++)
				if (i == hand) printf("%2d of %-8s\n", faceResult[i], suitResult[i]);
				else printf("%-2c%2d of %-8s\n", '\t', faceResult[i], suitResult[i]);
			printf("%-2c%2d of %-8s\n\n", '\t', faceResult[hit], suitResult[hit]);
			playerTotal += faceResult[hit];
			printf("Dealer first: %d\n", faceResult[0]);
			printf("Player Total: %d\n\n", playerTotal);
			hit++;
		}

		if (playerTotal > 21) {
			printf("Busted! Player loses!");
			*playerMoney -= bet;
			return;
		}
	} while (choice == 0);

	if (playerTotal <= 21) {
		while (dealerTotal < 17 && hit < 52) {
			printf("Dealer gets a card....\nDealer:");
			printf("%-2c%-2d of %-8s\n\n", '\t', faceResult[hit], suitResult[hit]);
			dealerTotal += faceResult[hit];
			hit++;

			if (dealerTotal > 21) {
				printPoints(dealerTotal, playerTotal);
				printf("Busted! Player wins!\n");
				printf("-----------------------\n");
				*playerMoney += bet;
				return;
			}
		}
	}
	printPoints(dealerTotal, playerTotal);
	getResult(dealerTotal, playerTotal, bet, playerMoney);
}

void printPoints(int dealerTotal, int playerTotal) {
	printf("Dealer Total: %d\n", dealerTotal);
	printf("Player Total: %d\n\n", playerTotal);
}

void getResult(int dealerTotal, int playerTotal, int bet, int *playerMoney) {
	if (dealerTotal > playerTotal && dealerTotal < 21) {
		printf("Dealer wins!!");
		*playerMoney -= bet;
	}

	else if (dealerTotal > 21) printf("Busted! Player wins!!");
	else if (dealerTotal == playerTotal) {
		printf("Dealer wins!!");
		*playerMoney -= bet;
	}
	else {
		printf("-----------------------\n");
		printf("Player wins!!");
		*playerMoney += bet;
	}

	printf("\nPlayer's Money: $%d", *playerMoney);
}

int getDecision() {
	int decision;

	do {
		printf("hit(0) or stand(1)?: ");
		scanf("%d", &decision);
		printf("-----------------------\n");
	} while (decision != 0 && decision != 1);
	return decision;
}

int getTotal(int handStart, int handEnd) {
	int total = 0;
	for (int i = handStart; i < handEnd; i++)
		total += faceResult[i];
	return total;
}

void shuffle(int wDeck[][13]) {
	int card, row, column;
	for (card = 1; card <= 52; card++) {
		do {
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);
		wDeck[row][column] = card;
	}
}

void deal(const int wDeck[][13], const char *wFace[], const char *wSuit[]) {
	int card, row, column;

	for (card = 1; card <= 52; card++) {
		for (row = 0; row <= 3; row++) {
			for (column = 0; column <= 12; column++) {
				if (wDeck[row][column] == card) {
					faceResult[card - 1] = atoi(wFace[column]);
					strncpy(suitResult[card - 1], wSuit[row], sizeof(suitResult[card - 1]) - 1);
					suitResult[card - 1][sizeof(suitResult[card - 1]) - 1] = '\0';
				}
			}
		}
	}
}


