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
	printf("．玩家(player) 和莊家(dealer) 輪流從牌堆中抽兩張牌，dealer 的第一張牌是蓋住的。\n");
	printf("．此時 player 可以決定繼續向莊家叫牌(hit)\n");
	printf("。如果叫牌以後玩家的點數超過 21 點，稱為爆牌，並且馬上輸掉這一局\n");
	printf("．如果 player 不想叫牌，則須選擇停牌(stand)\n");
	printf("．如果玩家沒有爆牌且停牌後，就輪到莊家開牌補牌。\n");
	printf("。莊家必需要幫自己補牌到大於等於 17 以上，接下來的補牌再依雙方點數而定。\n");
	printf("．如果雙方都沒有爆牌，則點數大的獲勝。(本題中規定點數相同時 dealer 獲勝)\n\n");
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


