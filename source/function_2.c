/*BlackJack
-------------------------------------------------------------------------------
．玩家(player) 和莊家(dealer) 輪流從牌堆中抽兩張牌，dealer 的第一張牌是蓋住的。
．此時 player 可以決定繼續向莊家叫牌(hit)
	。如果叫牌以後玩家的點數超過 21 點，稱為爆牌，並且馬上輸掉這一局
．如果 player 不想叫牌，則須選擇停牌(stand)
．如果玩家沒有爆牌且停牌後，就輪到莊家開牌補牌。
	。莊家必需要幫自己補牌到大於等於 17 以上，接下來的補牌再依雙方點數而定。
．如果雙方都沒有爆牌，則點數大的獲勝。(本題中規定點數相同時 dealer 獲勝)

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

const char *suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
const char *face[13] = { "1","2", "3", "4", "5", "6", "7", "8", "9", "10", "10", "10", "10" };

void shuffle(int wDeck[][13]);
void deal(const int wDeck[][13], const char *wFace[], const char *wSuit[]);
void play();
int suitResult[52] = { 0 };
char faceResult[52][10];
int getTotal(int handStart, int handEnd);
int getDecision();
void getResult(int dealerTotal, int playerTotal);
void printPoints(int dealerTotal, int playerTotal);

int Poker_2() {

	int deck[4][13] = { 0 };
	srand((unsigned int)time(NULL));
	shuffle(deck);
	deal(deck, face, suit);
	play();

	system("pause");
	return 0;
}

void play() {
	//int playerTotal = 0;
	int hand = 2;
	int choice;
	int hit = hand + 2;
	

	printf("Dealer : ");
	for (int i = 0; i < hand; i++)
		if (i == 0) printf("%-2d of %-8s\n", suitResult[i], faceResult[i]);
	int dealerTotal = getTotal(0, hand);

	printf("\nPlayer : ");
	for (int i = hand; i < hand + 2; i++)
		if (i == hand) printf("%-2d of %-8s\n", suitResult[i], faceResult[i]);
		else printf("%-2c%-2d of %-8s\n\n", '\t', suitResult[i], faceResult[i]);
	int playerTotal = getTotal(hand, hand + 2);

	printf("Dealer first: %d\n", suitResult[0]);
	printf("Player Total: %d\n\n", playerTotal);

	do {
		choice = getDecision();
		if (choice == 0) {
			printf("\nPlayer : ");
			for (int i = hand; i < hit; i++)
				if (i == hand) printf("%-2d of %-8s\n", suitResult[i], faceResult[i]);
				else printf("%-2c%-2d of %-8s\n", '\t', suitResult[i], faceResult[i]);
			printf("%-2c%-2d of %-8s\n\n", '\t', suitResult[hit], faceResult[hit]);
			playerTotal += suitResult[hit];
			printf("Dealer first: %d\n", suitResult[0]);
			printf("Player Total: %d\n\n", playerTotal);
			hit++;
		}

		if (playerTotal > 21) {
			printf("Busted! Player loses!");
			return;
		}
	} while (choice == 0);

	if (playerTotal <= 21) {
		while (dealerTotal < 17 && hit < 52) {
			printf("Dealer gets a card....\nDealer:");
			printf("%-2c%-2d of %-8s\n\n", '\t', suitResult[hit], faceResult[hit]);
			dealerTotal += suitResult[hit];
			hit++;

			if (dealerTotal > 21) {
				printPoints(dealerTotal, playerTotal);
				printf("Busted! Player wins!");
				return;
			}
		}
	}
	printPoints(dealerTotal, playerTotal);
	getResult(dealerTotal, playerTotal);
}



void printPoints(int dealerTotal, int playerTotal) {
	printf("Dealer Total: %d\n", dealerTotal);
	printf("Player Total: %d\n\n", playerTotal);
}

void getResult(int dealerTotal, int playerTotal) {
	if (dealerTotal > playerTotal && dealerTotal < 21) printf("Dealer wins!!");
	else if (dealerTotal > 21) printf("Busted! Player wins!!");
	else if (dealerTotal == playerTotal) printf("Dealer wins!!");
	else printf("Player wins!!");
}

int getDecision() {
	int decision;

	do {
		printf("hit(0) or stand(1)?: ");
		scanf("%d", &decision);
	} while (decision != 0 && decision != 1);
	return decision;
}

int getTotal(int handStart, int handEnd) {
	int total = 0;
	for (int i = handStart; i < handEnd; i++)
		total += suitResult[i];
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
					printf("%5s of %-8s\n", wFace[column], wSuit[row]); // Output all cards
					suitResult[card - 1] = atoi(wFace[column]);
					strncpy(faceResult[card - 1], wSuit[row], sizeof(faceResult[card - 1]) - 1);
					faceResult[card - 1][sizeof(faceResult[card - 1]) - 1] = '\0';
				}
			}
		}
	}
}
