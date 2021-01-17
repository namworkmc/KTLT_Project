﻿#include "19127048.h"
#include "19127493.h"

void printCardsShuffling(int deck[][RANKS], const char* suits[], const char* ranks[]) {
	
	int key = 1;
	int time = 0;
	bool is_found = false;
	for (time; time < 52; time++)
		for (int i = 0; i < SUITS; i++)
			for (int j = 0; j < RANKS; j++) {
				if (deck[i][j] == key) {
					cout << "(" << suits[i] << ", " << ranks[j] << ")" << endl;
					key++;
					is_found = true;
					break;
				}
				if (is_found)
				{
					is_found = false;
					break;
				}
			}
}
void printHand(int** hand, const char* suits[], const char* ranks[]) {
	for (int i = 0; i < 5; i++)
		cout << "(" << suits[hand[i][0]] << ", " << ranks[hand[i][1]] << ")" << endl;
}

int isStraightFlush(int** hand) {
	if (checkStraight(hand) && checkFlush(hand))
		return 1;
	return 0;
}
int isThreeOfAKind(int** hand) {
	////		CẤP PHÁT ĐỘNG		////
	int** handTest = new int* [5];
	for (int i = 0; i < 5; i++)
	{
		*(handTest + i) = new int[2];
	}


	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			handTest[i][j] = hand[i][j];
		}
	}

	////		SORT RANK		////
	for (int i = 0; i < 5 - 1; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			if (handTest[i][1] > handTest[j][1])
			{
				swap(handTest[i][1], handTest[j][1]);
			}
		}
	}
	///         Check Three of a kind		////
	
	int count1 = 0;
	for (int i = 0; i < 5 - 1; i++)
	{
		if (handTest[i][1] != handTest[i + 1][1])
		{
			count1++;
		}
	}
	if (isTwoPairs(hand) == 0 && count1 == 2)
	{
		DellocateDoublePointer(handTest, 5);
		return 1;
	}
	else
	{
		DellocateDoublePointer(handTest, 5);
		return 0;
	}
}
int isTwoPairs(int** hand) {
	////		CẤP PHÁT ĐỘNG		////
	int** handTest = new int* [5];
	for (int i = 0; i < 5; i++)
	{
		*(handTest + i) = new int[2];
	}


	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			handTest[i][j] = hand[i][j];
		}
	}

	////		SORT RANK		////
	for (int i = 0; i < 5 - 1; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			if (handTest[i][1] > handTest[j][1])
			{
				swap(handTest[i][1], handTest[j][1]);
			}
		}
	}
	///         Check different		////
	int count = 0;
	for (int i = 0; i < 5 - 1; i++)
	{
		if (handTest[i][1] != handTest[i + 1][1])
		{
			count++;
		}
	}
	if (count != 2)
		return 0;
	else {
		if (checkFlush(hand) == false) {
			if (handTest[0][1] == handTest[1][1] && handTest[2][1] == handTest[3][1])
			{
				DellocateDoublePointer(handTest, 5);
				return 1;
			}
			if (handTest[1][1] == handTest[2][1] && handTest[3][1] == handTest[4][1])
			{
				DellocateDoublePointer(handTest, 5);
				return 1;
			}
			if (handTest[0][1] == handTest[1][1] && handTest[3][1] == handTest[4][1])
			{
				DellocateDoublePointer(handTest, 5);
				return 1;
			}
		}
		DellocateDoublePointer(handTest, 5);
		return 0;
	}
}
int isPair(int** hand) {
	////		CẤP PHÁT ĐỘNG		////
	int** handTest = new int* [5];
	for (int i = 0; i < 5; i++)
	{
		*(handTest + i) = new int[2];
	}


	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			handTest[i][j] = hand[i][j];
		}
	}

	////		SORT RANK		////
	for (int i = 0; i < 5 - 1; i++)
	{
		for (int j = i + 1; j < 5; j++)
		{
			if (handTest[i][1] > handTest[j][1])
			{
				swap(handTest[i][1], handTest[j][1]);
			}
		}
	}
	///         Check different		////
	int count = 0;
	for (int i = 0; i < 5 - 1; i++)
	{
		if (handTest[i][1] != handTest[i + 1][1])
		{
			count++;
		}
	}
	if (count == 3 && checkFlush(hand) == false)
	{
		DellocateDoublePointer(handTest, 5);
		return 1;
	}
	else
	{
		DellocateDoublePointer(handTest, 5);
		return 0;
	}
	
}
int getHighestCard(int** hand) {
	int index_of_HighestCard = hand[0][1];
	for (int i = 1; i < 5; i++)
		if (hand[i][1] > index_of_HighestCard)
			index_of_HighestCard = hand[i][1];
	return index_of_HighestCard;
}
int getStatusOfHand(int** hand) {
	return getHighestMark(hand);
}
int* evaluateHands(int n, int s, const char* suits[], const char* ranks[]) {
///         Khởi tạo mảng lưu điểm của người chơi		////
	
	int* ScoreofThePlayer = new int[n];
	for (int i = 0; i < n; i++)
		ScoreofThePlayer[i] = 0;

	int deck[SUITS][RANKS] = { 0 };

///         Tính điểm của n người chơi sau khi chơi s lần		////
	
	for (int time = 1; time <= s; time++) {
		shuffleCards(deck);
		//printMatrix(deck);
		int*** test = dealingForHands(deck, n);
		cout << "Turn #" << time << ":" << endl;
		for (int i = 0; i < n; i++) {
			cout << "Player " << i << "'s card is: " << endl;
			printHand(*(test + i), suits, ranks);
		}
			
		//print3DArray(test, n, 5, 2);
		for (int i = 0; i < n; i++)
			ScoreofThePlayer[i] = ScoreofThePlayer[i] + getStatusOfHand(*(test + i));
	}

	int* RankofThePlayer = new int[n];
	for (int i = 0; i < n; i++)
		RankofThePlayer[i] = i;

///         Xếp hạng cho người chơi		////

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (ScoreofThePlayer[i] < ScoreofThePlayer[j])
			{
				swap(ScoreofThePlayer[i], ScoreofThePlayer[j]);
				swap(RankofThePlayer[i], RankofThePlayer[j]);
			}
		}
	}

	delete[] ScoreofThePlayer;
	ScoreofThePlayer = nullptr;

	return RankofThePlayer;
}
////////////////////////////////////////////////////////////////////////////////
int getHighestMark(int** hand) {
	if (isStraightFlush(hand) == 1)
		return 8;
	if (isFourOfAKind(hand) == 1)
		return 7;
	if (isFullHouse(hand) == 1)
		return 6;
	if (isFlush(hand) == 1)
		return 5;
	if (isStraight(hand) == 1)
		return 4;
	if (isThreeOfAKind(hand) == 1)
		return 3;
	if (isTwoPairs(hand) == 1)
		return 2;
	if (isPair(hand) == 1)
		return 1;
	return 0;
}

int* NEW_rankingHands(int*** hands, int n, int player_cards, int dealer_cards, string check)
{
	int* RankofThePlayer = new int[n];
	int* ScoreofThePlayer = new int[n];

	for (int i = 0; i < n; i++)
	{
		ScoreofThePlayer[i] = getStatusOfHand(*(hands + i));
		RankofThePlayer[i] = i;
	}
	if (check == "Easy Game") 
		ScoreofThePlayer[1] = ScoreofThePlayer[1] - (3 - player_cards);

	if (check == "Hard Game")
		ScoreofThePlayer[0] = ScoreofThePlayer[0] - (3 - dealer_cards);

	cout << "Player's score after the change is " << ScoreofThePlayer[0] << endl;
	cout << "Dealer's score after the change is " << ScoreofThePlayer[1] << endl;
	
	////		SORT RANK		////
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (ScoreofThePlayer[i] < ScoreofThePlayer[j])
			{
				swap(ScoreofThePlayer[i], ScoreofThePlayer[j]);
				swap(RankofThePlayer[i], RankofThePlayer[j]);
			}
		}
	}


	delete[] ScoreofThePlayer;
	ScoreofThePlayer = nullptr;


	return RankofThePlayer;
}





