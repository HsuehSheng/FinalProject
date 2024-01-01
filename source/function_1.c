#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum { HEARTS, DIAMONDS, CLUBS, SPADES } Suit;

typedef struct {
	int value;
	Suit suit;
} Card;

Card draw_card(Card* deck, int* num_cards_in_deck) {
	int random_index;
	if (*num_cards_in_deck == 0) {
		Card empty_card = { 0, HEARTS };
		return empty_card;
	}

	random_index = rand() % (*num_cards_in_deck);
	Card drawn_card = deck[random_index];

	deck[random_index] = deck[*num_cards_in_deck - 1];
	(*num_cards_in_deck)--;

	return drawn_card;
}

void print_card(Card card) {
	switch (card.suit) {
	case HEARTS:
		printf("紅心");
		break;
	case DIAMONDS:
		printf("方塊");
		break;
	case CLUBS:
		printf("梅花");
		break;
	case SPADES:
		printf("黑桃");
		break;
	}

	if (card.value == 1) {
		printf("A");
	}
	else if (card.value == 11) {
		printf("J");
	}
	else if (card.value == 12) {
		printf("Q");
	}
	else if (card.value == 13) {
		printf("K");
	}
	else if (card.value >= 2 && card.value <= 10) {
		printf("%d", card.value);
	}
}

float calculate_score(Card cards[], int num_cards) {	
	float score = 0;

	for (int i = 0; i < num_cards; ++i) {
		if (cards[i].value == 11 || cards[i].value == 12 || cards[i].value == 13) {
			score += 0.5;
		}
		else {
			score += cards[i].value;
		}
	}

	return score;
}

void print_cards(Card cards[], int num_cards, int hide_last_card) {
	for (int i = 0; i < num_cards; ++i) {
		if (hide_last_card && i == num_cards - 1) {
			printf("### ");
		}
		else {
			print_card(cards[i]);
			printf(" ");
		}
	}
	printf("\n");
}

int Poker_1() {
	srand((unsigned int)time(NULL));

	const int max_cards = 52;
	Card* deck = (Card*)malloc(max_cards * sizeof(Card));
	int num_cards_in_deck = 0;

	for (int suit = HEARTS; suit <= SPADES; ++suit) {
		for (int value = 1; value <= 13; ++value) {
			deck[num_cards_in_deck].value = value;
			deck[num_cards_in_deck].suit = (Suit)suit;
			num_cards_in_deck++;
		}
	}

	char should_continue;

	do {
		Card player_cards[10];
		Card computer_cards[10];
		int num_player_cards = 1;
		int num_computer_cards = 1;

		player_cards[0] = draw_card(deck, &num_cards_in_deck);
		if (player_cards[0].value == 0) {
			break;
		}
		printf("你抽到的牌：");
		print_card(player_cards[0]);
		printf("\n");

		computer_cards[0] = draw_card(deck, &num_cards_in_deck);
		if (computer_cards[0].value == 0) {
			break;
		}

		while (1) {
			float player_score = calculate_score(player_cards, num_player_cards);
			float computer_score = calculate_score(computer_cards, num_computer_cards);

			printf("你的牌：");
			print_cards(player_cards, num_player_cards, 0);
			printf("目前點數：%.1f\n", player_score);

			printf("電腦的牌：");
			print_cards(computer_cards, num_computer_cards, 1);
			printf("\n");

			printf("是否要加牌？(y/n): ");
			scanf(" %c", &should_continue);

			if (should_continue == 'y') {
				player_cards[num_player_cards] = draw_card(deck, &num_cards_in_deck);
				if (player_cards[num_player_cards].value == 0) {
					break;
				}
				printf("你抽到的牌：");
				print_card(player_cards[num_player_cards]);
				printf("\n");
				num_player_cards++;
			}
			else {
				break;
			}

			if (calculate_score(player_cards, num_player_cards) > 10.5) {
				printf("你爆牌了，電腦獲勝！\n");
				goto end_game;
			}
		}

		while (calculate_score(computer_cards, num_computer_cards) < 8.5) {
			computer_cards[num_computer_cards] = draw_card(deck, &num_cards_in_deck);
			if (computer_cards[num_computer_cards].value == 0) {
				break;
			}
			num_computer_cards++;
		}

		printf("你的牌：");
		print_cards(player_cards, num_player_cards, 0);
		printf("總點數：%.1f\n", calculate_score(player_cards, num_player_cards));

		printf("電腦的牌：");
		print_cards(computer_cards, num_computer_cards, 0);
		printf("總點數：%.1f\n", calculate_score(computer_cards, num_computer_cards));

		if (calculate_score(player_cards, num_player_cards) > 10.5) {
			printf("你爆牌了，電腦獲勝！\n");
		}
		else if (calculate_score(computer_cards, num_computer_cards) > 10.5) {
			printf("電腦爆牌了，你獲勝！\n");
		}
		else if (calculate_score(player_cards, num_player_cards) > calculate_score(computer_cards, num_computer_cards)) {
			printf("你獲勝！\n");
		}
		else if (calculate_score(player_cards, num_player_cards) < calculate_score(computer_cards, num_computer_cards)) {
			printf("電腦獲勝！\n");
		}
		else {
			printf("平局！\n");
		}

	end_game:
		printf("是否繼續遊戲？(y/n): ");
		scanf(" %c", &should_continue);

	} while (should_continue == 'y' && num_cards_in_deck > 0);

	free(deck);
	printf("牌已發完，遊戲結束！\n");

	return 0;
}
