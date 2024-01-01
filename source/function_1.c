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
		printf("����");
		break;
	case DIAMONDS:
		printf("���");
		break;
	case CLUBS:
		printf("����");
		break;
	case SPADES:
		printf("�®�");
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
		printf("�A��쪺�P�G");
		print_card(player_cards[0]);
		printf("\n");

		computer_cards[0] = draw_card(deck, &num_cards_in_deck);
		if (computer_cards[0].value == 0) {
			break;
		}

		while (1) {
			float player_score = calculate_score(player_cards, num_player_cards);
			float computer_score = calculate_score(computer_cards, num_computer_cards);

			printf("�A���P�G");
			print_cards(player_cards, num_player_cards, 0);
			printf("�ثe�I�ơG%.1f\n", player_score);

			printf("�q�����P�G");
			print_cards(computer_cards, num_computer_cards, 1);
			printf("\n");

			printf("�O�_�n�[�P�H(y/n): ");
			scanf(" %c", &should_continue);

			if (should_continue == 'y') {
				player_cards[num_player_cards] = draw_card(deck, &num_cards_in_deck);
				if (player_cards[num_player_cards].value == 0) {
					break;
				}
				printf("�A��쪺�P�G");
				print_card(player_cards[num_player_cards]);
				printf("\n");
				num_player_cards++;
			}
			else {
				break;
			}

			if (calculate_score(player_cards, num_player_cards) > 10.5) {
				printf("�A�z�P�F�A�q����ӡI\n");
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

		printf("�A���P�G");
		print_cards(player_cards, num_player_cards, 0);
		printf("�`�I�ơG%.1f\n", calculate_score(player_cards, num_player_cards));

		printf("�q�����P�G");
		print_cards(computer_cards, num_computer_cards, 0);
		printf("�`�I�ơG%.1f\n", calculate_score(computer_cards, num_computer_cards));

		if (calculate_score(player_cards, num_player_cards) > 10.5) {
			printf("�A�z�P�F�A�q����ӡI\n");
		}
		else if (calculate_score(computer_cards, num_computer_cards) > 10.5) {
			printf("�q���z�P�F�A�A��ӡI\n");
		}
		else if (calculate_score(player_cards, num_player_cards) > calculate_score(computer_cards, num_computer_cards)) {
			printf("�A��ӡI\n");
		}
		else if (calculate_score(player_cards, num_player_cards) < calculate_score(computer_cards, num_computer_cards)) {
			printf("�q����ӡI\n");
		}
		else {
			printf("�����I\n");
		}

	end_game:
		printf("�O�_�~��C���H(y/n): ");
		scanf(" %c", &should_continue);

	} while (should_continue == 'y' && num_cards_in_deck > 0);

	free(deck);
	printf("�P�w�o���A�C�������I\n");

	return 0;
}
