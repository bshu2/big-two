#pragma once

#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <vector>

class Hand
{
public:
	Hand();
	Hand(std::vector<Card> cards);

	int get_hand_size();
	std::vector<Card> get_hand_cards();
	Card* get_card_from_index(int index);

private:
	std::vector<Card> hand_cards;
};

#endif

