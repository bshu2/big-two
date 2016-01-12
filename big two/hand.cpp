#include "hand.h"

Hand::Hand()
{
	//hand_cards = NULL;
}

Hand::Hand(std::vector<Card> cards)
{
	hand_cards = cards;
}

int Hand::get_hand_size()
{
	return hand_cards.size();
}

std::vector<Card> Hand::get_hand_cards()
{
	return hand_cards;
}

Card* Hand::get_card_from_index(int index)
{
	Card* ret_card = &hand_cards[index];
	return ret_card;
}

