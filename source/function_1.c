#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum { HEARTS, DIAMONDS, CLUBS, SPADES } Suit;

typedef struct {
	int value;  // 使用整數型別表示點數
	Suit suit;
} Card;

Card draw_card(Card* deck, int* num_cards_in_deck) {
	int random_index;
	if (*num_cards_in_deck == 0) {
		// 牌堆用完，回傳一張空的卡牌
		Card empty_card = { 0, HEARTS }; // 或其他預設值
		return empty_card;
	}

	random_index = rand() % (*num_cards_in_deck); // 隨機選擇一張卡牌的索引
	Card drawn_card = deck[random_index]; // 從牌堆中取得卡牌

	// 將最後一張卡牌移到被選擇的位置，縮減牌堆大小
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
			score += 0.5;  // J、Q、K的點數為0.5
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
			printf("### "); // 顯示隱藏的牌
		}
		else {
			print_card(cards[i]);
			printf(" ");
		}
	}
	printf("\n");
}

int Poker_1() {
	srand((unsigned int)time(NULL));  // 初始化隨機數生成器

	const int max_cards = 52;
	Card* deck = (Card*)malloc(max_cards * sizeof(Card));
	int num_cards_in_deck = 0;

	// 初始化牌堆
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
		int num_player_cards = 1; // 一開始只有一張牌
		int num_computer_cards = 1;

		// 開局發牌
		player_cards[0] = draw_card(deck, &num_cards_in_deck);
		if (player_cards[0].value == 0) {
			// 牌堆用完，結束遊戲
			break;
		}
		printf("你抽到的牌：");
		print_card(player_cards[0]);
		printf("\n");

		// 電腦的首張牌
		computer_cards[0] = draw_card(deck, &num_cards_in_deck);
		if (computer_cards[0].value == 0) {
			// 牌堆用完，結束遊戲
			break;
		}

		// 玩家選擇是否加牌
		while (1) {
			float player_score = calculate_score(player_cards, num_player_cards);
			float computer_score = calculate_score(computer_cards, num_computer_cards);

			printf("你的牌：");
			print_cards(player_cards, num_player_cards, 0);
			printf("目前點數：%.1f\n", player_score);

			printf("電腦的牌：");
			print_cards(computer_cards, num_computer_cards, 1); // 隱藏電腦的最後一張牌
			printf("\n");

			printf("是否要加牌？(y/n): ");
			scanf(" %c", &should_continue);

			if (should_continue == 'y') {
				player_cards[num_player_cards] = draw_card(deck, &num_cards_in_deck);
				if (player_cards[num_player_cards].value == 0) {
					// 牌堆用完，結束遊戲
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

			// 檢查玩家是否爆牌
			if (calculate_score(player_cards, num_player_cards) > 10.5) {
				printf("你爆牌了，電腦獲勝！\n");
				goto end_game;
			}
		}

		// 電腦選擇是否加牌
		while (calculate_score(computer_cards, num_computer_cards) < 8.5) {
			computer_cards[num_computer_cards] = draw_card(deck, &num_cards_in_deck);
			if (computer_cards[num_computer_cards].value == 0) {
				// 牌堆用完，結束遊戲
				break;
			}
			num_computer_cards++;
		}

		// 顯示最終結果
		printf("你的牌：");
		print_cards(player_cards, num_player_cards, 0);
		printf("總點數：%.1f\n", calculate_score(player_cards, num_player_cards));

		printf("電腦的牌：");
		print_cards(computer_cards, num_computer_cards, 0);
		printf("總點數：%.1f\n", calculate_score(computer_cards, num_computer_cards));

		// 判斷勝負
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
		// 繼續遊戲的選項
		printf("是否繼續遊戲？(y/n): ");
		scanf(" %c", &should_continue);

	} while (should_continue == 'y' && num_cards_in_deck > 0);

	free(deck);
	printf("牌已發完，遊戲結束！\n");

	return 0;
}