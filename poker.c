//World Poker Championship

#include <stdio.h>
#include <time.h>

enum {
	CLUB,
	DIAMOND,
	HEART,
	SPADE,
	HIGH_CARD,
	ONE_PAIR,
	TWO_PAIR,
	THREE,
	STRAIGHT,
	FLUSH,
	FULL_HOUSE,
	FOUR,
	STRAIGHT_FLUSH,
	SUIT
};
#define DECK 52
typedef struct card {
	int shape, number;
} Card;

void GameTitle(void); // GameTitle
void CardDeck(Card* deck); // build a card deck (52 cards)
void ShuffleDeck(Card* deck); // shuffle the deck
void CardDispenser(Card* deck, Card* plrHand, Card* comHand); // 5 cards into player's hand and computer's
void CardVisualization(Card* hand); // visualize cards
void Cash(int* plrCash); // player's money
void CardChange(Card* deck, Card* plrHand, int* totalCardOutNumber); // exchange cards
void Betting(int* plrCash, int* plrBet); // betting
int HandOrder(Card* hand); // value by evaluating hands to variable
void RankVisulaization(int* handOrder); // print evaluated hand
void ComAi(Card* deck, Card* comHand, int* comHandOrder,
		int* totalCardOutNumber); // computer's play
void WhoWins(int* plrHandOrder, int* comHandOrder, Card* plrHand, Card* comHand,
		int* plrCash, int* plrBet); // winner or loser

int main(void) {

	Card deck[52], plrHand[5], comHand[5];
	int totalCardOutNumber = 10; // total number of dealt cards = 10 (5 for each player)
	int plrCash = 1000, plrBet = 0; // money at start
	int plrHandOrder, comHandOrder; // variables for evaluating hands

	srand((unsigned) time(NULL));

	GameTitle();

	while (plrCash > 0) { //when money comes behind 0, game over
		plrBet = 0; //initiate the variable as 0 on each round
		CardDeck(deck); // build card deck (52 cards)
		ShuffleDeck(deck); // 52장 카드 섞기
		CardDispenser(deck, plrHand, comHand); //dealing cards
		Cash(&plrCash);
		CardVisualization(plrHand);
		Betting(&plrCash, &plrBet);
		CardChange(deck, plrHand, &totalCardOutNumber);
		CardVisualization(plrHand);
		Betting(&plrCash, &plrBet);
		plrHandOrder = HandOrder(plrHand);
		comHandOrder = HandOrder(comHand);
		ComAi(deck, comHand, &comHandOrder, &totalCardOutNumber);
		comHandOrder = HandOrder(comHand);
		printf("<com hand>\n");
		CardVisualization(comHand);
		printf("your rank : ");
		RankVisulaization(&plrHandOrder);
		printf("com rank :  ");
		RankVisulaization(&comHandOrder);
		WhoWins(&plrHandOrder, &comHandOrder, plrHand, comHand, &plrCash,
				&plrBet);
	printf("Game Over\n");
	}
	return 0;
}

void GameTitle(void) {

	printf("World Poker Championship 2016\n");
	printf("콤퓨타랑 다이다이\n");
	printf("=============================\n\n");
}
void CardDeck(Card* deck) {
	int i;
	for (i = 0; i < DECK; i++) {
		if (i >= 0 && i < SUIT) {
			deck[i].shape = SPADE;
			deck[i].number = i + 1;
		} else if (i >= SUIT && i < (SUIT * 2)) {
			deck[i].shape = HEART;
			deck[i].number = (i - SUIT) + 1;
		} else if (i >= (SUIT * 2) && i < (SUIT * 3)) {
			deck[i].shape = DIAMOND;
			deck[i].number = (i - (SUIT * 2)) + 1;
		} else {
			deck[i].shape = CLUB;
			deck[i].number = (i - (SUIT * 3)) + 1;
		}
	}
}
void ShuffleDeck(Card* deck) {

	int index1, index2;
	Card temp;

	for (int i = 0; i < DECK; i++) {
		while (1) {
			index1 = rand() % DECK;
			index2 = rand() % DECK;
			if (index1 != index2)
				break;
		}
		temp = deck[index1];
		deck[index1] = deck[index2];
		deck[index2] = temp;
	}
}
void CardDispenser(Card* deck, Card* plrHand, Card* comHand) {

	for (int i = 0; i < 5; i++) {
		plrHand[i] = deck[i];

		comHand[i] = deck[i + 5];
	}
}
void CardVisualization(Card* hand) {

	for (int i = 0; i < 5; i++) {

		if (hand[i].shape == SPADE) {
			if (hand[i].number == 1)
				printf("A♠ ");
			else if (hand[i].number >= 2 && hand[i].number <= 10)
				printf("%d♠ ", hand[i].number);
			else if (hand[i].number == 11)
				printf("J♠ ");
			else if (hand[i].number == 12)
				printf("Q♠ ");
			else
				printf("K♠ ");
		} else if (hand[i].shape == HEART) {
			if (hand[i].number == 1)
				printf("A♥ ");
			else if (hand[i].number >= 2 && hand[i].number <= 10)
				printf("%d♥ ", hand[i].number);
			else if (hand[i].number == 11)
				printf("J♥ ");
			else if (hand[i].number == 12)
				printf("Q♥ ");
			else
				printf("K♥ ");
		} else if (hand[i].shape == DIAMOND) {
			if (hand[i].number == 1)
				printf("A▲ ");
			else if (hand[i].number >= 2 && hand[i].number <= 10)
				printf("%d▲ ", hand[i].number);
			else if (hand[i].number == 11)
				printf("J▲ ");
			else if (hand[i].number == 12)
				printf("Q▲ ");
			else
				printf("K▲ ");
		} else {
			if (hand[i].number == 1)
				printf("A♣ ");
			else if (hand[i].number >= 2 && hand[i].number <= 10)
				printf("%d♣ ", hand[i].number);
			else if (hand[i].number == 11)
				printf("J♣ ");
			else if (hand[i].number == 12)
				printf("Q♣ ");
			else
				printf("K♣ ");
		}
	}
	printf("\n\n");
}
void Cash(int* plrCash) {
	printf("CASH : %d\n\n", *plrCash);
}
void Betting(int* plrCash, int* plrBet) {
	int bet;
	printf("Bet > ");
	fflush(stdout);
	scanf("%d", &bet);
	printf("\n");
	*plrCash -= bet;
	*plrBet += bet;
}
void CardChange(Card* deck, Card* plrHand, int* totalCardOutNumber) {

	int i, howmany;
	int cardToChange;
	printf("How many changes > ");
	fflush(stdout);
	scanf("%d", &howmany);

	for (i = 0; i < howmany; i++) {
		printf("Card to change > ");
		fflush(stdout);
		scanf("%d", &cardToChange);

		plrHand[cardToChange - 1] = deck[(*totalCardOutNumber) + i];
	}
	*totalCardOutNumber += i;
	printf("\n");
}
int HandOrder(Card* hand) {

	int i, j, handOrder;
	Card temp;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 4; j++) {
			if (hand[j].number > hand[j + 1].number) {
				temp = hand[j];
				hand[j] = hand[j + 1];
				hand[j + 1] = temp;
			}
		}
	}

	if ((hand[0].shape == hand[1].shape && hand[1].shape == hand[2].shape
			&& hand[2].shape == hand[3].shape && hand[3].shape == hand[4].shape)
			&&

			(hand[4].number - hand[3].number == 1
					&& hand[3].number - hand[2].number == 1
					&& hand[2].number - hand[1].number == 1
					&& hand[1].number - hand[0].number == 1))

		handOrder = STRAIGHT_FLUSH;

	else if ((hand[0].number == hand[1].number
			&& hand[1].number == hand[2].number
			&& hand[2].number == hand[3].number)
			||

			(hand[0].number == hand[1].number
					&& hand[1].number == hand[3].number
					&& hand[3].number == hand[4].number)
			||

			(hand[1].number == hand[2].number
					&& hand[2].number == hand[3].number
					&& hand[3].number == hand[4].number))

		handOrder = FOUR;

	else if ((hand[0].number == hand[1].number
			&& hand[2].number == hand[3].number
			&& hand[3].number == hand[4].number)
			||

			(hand[0].number == hand[2].number
					&& hand[1].number == hand[3].number
					&& hand[3].number == hand[4].number)
			||

			(hand[0].number == hand[3].number
					&& hand[1].number == hand[2].number
					&& hand[2].number == hand[4].number)
			||

			(hand[0].number == hand[4].number
					&& hand[1].number == hand[2].number
					&& hand[2].number == hand[3].number)
			||

			(hand[1].number == hand[2].number
					&& hand[0].number == hand[3].number
					&& hand[3].number == hand[4].number)
			||

			(hand[1].number == hand[3].number
					&& hand[0].number == hand[2].number
					&& hand[2].number == hand[4].number)
			||

			(hand[1].number == hand[4].number
					&& hand[0].number == hand[2].number
					&& hand[2].number == hand[3].number)
			||

			(hand[2].number == hand[3].number
					&& hand[0].number == hand[1].number
					&& hand[1].number == hand[4].number)
			||

			(hand[2].number == hand[4].number
					&& hand[0].number == hand[1].number
					&& hand[1].number == hand[3].number)
			||

			(hand[3].number == hand[4].number
					&& hand[0].number == hand[1].number
					&& hand[1].number == hand[2].number))

		handOrder = FULL_HOUSE;

	else if (hand[0].shape == hand[1].shape && hand[1].shape == hand[2].shape
			&& hand[2].shape == hand[3].shape && hand[3].shape == hand[4].shape)

		handOrder = FLUSH;

	else if (hand[4].number - hand[3].number == 1
			&& hand[3].number - hand[2].number == 1
			&& hand[2].number - hand[1].number == 1
			&& hand[1].number - hand[0].number == 1)

		handOrder = STRAIGHT;

	else if ((hand[0].number == hand[1].number
			&& hand[1].number == hand[2].number)
			|| (hand[0].number == hand[1].number
					&& hand[1].number == hand[3].number)
			|| (hand[0].number == hand[1].number
					&& hand[1].number == hand[4].number)
			||

			(hand[0].number == hand[2].number
					&& hand[2].number == hand[3].number)
			|| (hand[0].number == hand[2].number
					&& hand[2].number == hand[4].number)
			|| (hand[0].number == hand[3].number
					&& hand[3].number == hand[4].number)
			||

			(hand[1].number == hand[2].number
					&& hand[2].number == hand[3].number)
			|| (hand[1].number == hand[2].number
					&& hand[2].number == hand[4].number)
			|| (hand[1].number == hand[3].number
					&& hand[3].number == hand[4].number)
			||

			(hand[2].number == hand[3].number
					&& hand[3].number == hand[4].number))

		handOrder = THREE;

	else if ((hand[0].number == hand[1].number
			&& hand[2].number == hand[3].number)
			|| (hand[0].number == hand[1].number
					&& hand[2].number == hand[4].number)
			|| (hand[0].number == hand[1].number
					&& hand[3].number == hand[4].number)
			||

			(hand[0].number == hand[2].number
					&& hand[1].number == hand[3].number)
			|| (hand[0].number == hand[2].number
					&& hand[2].number == hand[3].number)
			|| (hand[0].number == hand[2].number
					&& hand[3].number == hand[4].number)
			||

			(hand[0].number == hand[3].number
					&& hand[1].number == hand[2].number)
			|| (hand[0].number == hand[3].number
					&& hand[1].number == hand[4].number)
			|| (hand[0].number == hand[3].number
					&& hand[2].number == hand[4].number)
			||

			(hand[0].number == hand[4].number
					&& hand[1].number == hand[2].number)
			|| (hand[0].number == hand[4].number
					&& hand[1].number == hand[3].number)
			|| (hand[0].number == hand[4].number
					&& hand[2].number == hand[3].number)
			||

			(hand[1].number == hand[2].number
					&& hand[3].number == hand[4].number)
			|| (hand[1].number == hand[3].number
					&& hand[2].number == hand[4].number)
			|| (hand[1].number == hand[4].number
					&& hand[2].number == hand[3].number))

		handOrder = TWO_PAIR;

	else if (hand[0].number == hand[1].number
			|| hand[0].number == hand[2].number
			|| hand[0].number == hand[3].number
			|| hand[0].number == hand[4].number
			|| hand[1].number == hand[2].number
			|| hand[1].number == hand[3].number
			|| hand[1].number == hand[4].number
			|| hand[2].number == hand[3].number
			|| hand[2].number == hand[4].number
			|| hand[3].number == hand[4].number)

		handOrder = ONE_PAIR;

	else
		handOrder = HIGH_CARD;

	return handOrder;
}
void RankVisulaization(int* handOrder) {
	if (*handOrder == ONE_PAIR)
		printf("One Pair\n");
	else if (*handOrder == TWO_PAIR)
		printf("Two Pair\n");
	else if (*handOrder == THREE)
		printf("Three Of Kind\n");
	else if (*handOrder == STRAIGHT)
		printf("Straight\n");
	else if (*handOrder == FLUSH)
		printf("Flush\n");
	else if (*handOrder == FULL_HOUSE)
		printf("Full House\n");
	else if (*handOrder == FOUR)
		printf("Four Of Kind\n");
	else if (*handOrder == STRAIGHT_FLUSH)
		printf("Straight Flush\n");
	else
		printf("High Card\n");
}
void WhoWins(int* plrHandOrder, int* comHandOrder, Card* plrHand, Card* comHand,
		int* plrCash, int* plrBet) {
	if (*plrHandOrder > *comHandOrder) {
		printf("You win\n\n");
		*plrCash += (*plrBet) * 2;
	}

	else if (*plrHandOrder < *comHandOrder) {
		printf("You lose\n\n");
		*plrCash -= (*plrBet) * 2;
	} else {
		if (plrHand[4].number > comHand[4].number) {
			printf("You win\n\n");
			*plrCash += (*plrBet) * 2;
		} else if (plrHand[4].number < comHand[4].number) {
			printf("You lose\n\n");
			*plrCash -= (*plrBet) * 3;
		} else {
			printf("Draw\n\n");
			*plrCash += *plrBet;
		}
	}

}
void ComAi(Card* deck, Card* comHand, int* comHandOrder,
		int* totalCardOutNumber) {
	if (*comHandOrder < HIGH_CARD) {
		if (comHand[0].shape == comHand[1].shape
				&& comHand[1].shape == comHand[2].shape
				&& comHand[2].shape == comHand[3].shape)
			comHand[4] = deck[*totalCardOutNumber];
		else if (comHand[0].shape == comHand[1].shape
				&& comHand[1].shape == comHand[2].shape
				&& comHand[2].shape == comHand[4].shape)
			comHand[3] = deck[*totalCardOutNumber];
		else if (comHand[0].shape == comHand[1].shape
				&& comHand[1].shape == comHand[3].shape
				&& comHand[3].shape == comHand[4].shape)
			comHand[2] = deck[*totalCardOutNumber];
		else if (comHand[0].shape == comHand[2].shape
				&& comHand[2].shape == comHand[3].shape
				&& comHand[3].shape == comHand[4].shape)
			comHand[1] = deck[*totalCardOutNumber];
		else if (comHand[1].shape == comHand[2].shape
				&& comHand[2].shape == comHand[3].shape
				&& comHand[3].shape == comHand[4].shape)
			comHand[0] = deck[*totalCardOutNumber];
		else {

			comHand[0] = deck[*totalCardOutNumber];
			comHand[4] = deck[*totalCardOutNumber + 1];
		}
	}

	else if (*comHandOrder == ONE_PAIR) {
		if (comHand[0].number == comHand[1].number) {
			comHand[2] = deck[*totalCardOutNumber];
			comHand[3] = deck[*totalCardOutNumber + 1];
		} else if (comHand[0].number == comHand[2].number) {
			comHand[1] = deck[*totalCardOutNumber];
			comHand[3] = deck[*totalCardOutNumber + 1];
		} else if (comHand[0].number == comHand[3].number) {
			comHand[1] = deck[*totalCardOutNumber];
			comHand[2] = deck[*totalCardOutNumber + 1];
		} else if (comHand[0].number == comHand[4].number) {
			comHand[2] = deck[*totalCardOutNumber];
			comHand[3] = deck[*totalCardOutNumber + 1];
		} else if (comHand[1].number == comHand[2].number) {
			comHand[0] = deck[*totalCardOutNumber];
			comHand[3] = deck[*totalCardOutNumber + 1];
		} else if (comHand[1].number == comHand[3].number) {
			comHand[0] = deck[*totalCardOutNumber];
			comHand[2] = deck[*totalCardOutNumber + 1];
		} else if (comHand[1].number == comHand[4].number) {
			comHand[0] = deck[*totalCardOutNumber];
			comHand[2] = deck[*totalCardOutNumber + 1];
		} else if (comHand[2].number == comHand[3].number) {
			comHand[0] = deck[*totalCardOutNumber];
			comHand[1] = deck[*totalCardOutNumber + 1];
		} else if (comHand[2].number == comHand[4].number) {
			comHand[0] = deck[*totalCardOutNumber];
			comHand[1] = deck[*totalCardOutNumber + 1];
		} else if (comHand[3].number == comHand[4].number) {
			comHand[0] = deck[*totalCardOutNumber];
			comHand[2] = deck[*totalCardOutNumber + 1];
		}
	}

	else if (*comHandOrder == TWO_PAIR) {
		if (comHand[0].number == comHand[1].number
				&& comHand[2].number == comHand[3].number)
			comHand[4] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[2].number
				&& comHand[1].number == comHand[3].number)
			comHand[4] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[3].number
				&& comHand[1].number == comHand[2].number)
			comHand[4] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[1].number
				&& comHand[2].number == comHand[4].number)
			comHand[3] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[2].number
				&& comHand[1].number == comHand[4].number)
			comHand[3] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[4].number
				&& comHand[1].number == comHand[2].number)
			comHand[3] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[1].number
				&& comHand[3].number == comHand[4].number)
			comHand[2] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[3].number
				&& comHand[1].number == comHand[4].number)
			comHand[2] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[4].number
				&& comHand[1].number == comHand[3].number)
			comHand[2] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[2].number
				&& comHand[3].number == comHand[4].number)
			comHand[1] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[3].number
				&& comHand[2].number == comHand[4].number)
			comHand[1] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[4].number
				&& comHand[2].number == comHand[3].number)
			comHand[1] = deck[*totalCardOutNumber];
		else if (comHand[1].number == comHand[2].number
				&& comHand[3].number == comHand[4].number)
			comHand[0] = deck[*totalCardOutNumber];
		else if (comHand[1].number == comHand[3].number
				&& comHand[2].number == comHand[4].number)
			comHand[0] = deck[*totalCardOutNumber];
		else if (comHand[1].number == comHand[4].number
				&& comHand[2].number == comHand[3].number)
			comHand[0] = deck[*totalCardOutNumber];
	}

	else if (*comHandOrder == THREE) {
		if (comHand[1].number == comHand[2].number
				&& comHand[2].number == comHand[3].number)
			comHand[0] = deck[*totalCardOutNumber];
		else if (comHand[1].number == comHand[2].number
				&& comHand[2].number == comHand[4].number)
			comHand[0] = deck[*totalCardOutNumber];
		else if (comHand[1].number == comHand[3].number
				&& comHand[3].number == comHand[4].number)
			comHand[0] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[2].number
				&& comHand[2].number == comHand[3].number)
			comHand[1] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[2].number
				&& comHand[2].number == comHand[4].number)
			comHand[1] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[3].number
				&& comHand[3].number == comHand[4].number)
			comHand[1] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[1].number
				&& comHand[1].number == comHand[3].number)
			comHand[2] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[1].number
				&& comHand[1].number == comHand[4].number)
			comHand[2] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[3].number
				&& comHand[3].number == comHand[4].number)
			comHand[2] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[1].number
				&& comHand[1].number == comHand[2].number)
			comHand[3] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[1].number
				&& comHand[1].number == comHand[4].number)
			comHand[3] = deck[*totalCardOutNumber];
		else if (comHand[0].number == comHand[2].number
				&& comHand[2].number == comHand[4].number)
			comHand[3] = deck[*totalCardOutNumber];
	}
}
