#pragma once

#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

class Deck
{
public:
	Deck();

	void init_deck();

	std::vector<Card>* get_deck_cards();
	void shuffle_deck();
	void print_deck();
	//void deal_hands(std::vector<Card> &hand1, std::vector<Card> &hand2, std::vector<Card> &hand3, std::vector<Card> &hand4);
	
	int close_deck();

private:
	std::vector<Card> deck_cards;
};

#endif

