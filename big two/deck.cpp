#include "deck.h"
#include <time.h>
#include <iostream>

Deck::Deck()
{
	/*
	//create 52 unique cards
	for (int s = 0; s < 4; s++)
	{
		for (int v = 1; v <= 13; v++)
		{
			Card card(s, v);
			deck_cards.push_back(card);
		}
	}
	*/
}


void Deck::init_deck()
{
	//create 52 unique cards
	for (int s = 0; s < 4; s++)
	{
		for (int v = 1; v <= 13; v++)
		{
			Card card(s, v);
			deck_cards.push_back(card);
		}
	}
}


std::vector<Card> *Deck::get_deck_cards()
{
	return &deck_cards;
}


void Deck::shuffle_deck()
{
	srand((int)time(NULL));
	std::vector<Card> temp;
	int index;

	while (deck_cards.size() > 0)
	{
		// move a random element in deck_cards to temp
		index = rand() % deck_cards.size();
		//std::cout << index << " ";
		temp.push_back(deck_cards.at(index));
		deck_cards.erase(deck_cards.begin() + index);

	}
	/*
	std::cout << "\ndeck:" << deck_cards.size();
	std::cout << "\ntemp:" << temp.size() << "\n";
	for (int i = 0; i < temp.size(); i++)
	{
		temp[i].print_card();
	}
	*/
	//move elements of temp (shuffled deck) into deck_cards
	while (temp.size() > 0)
	{
		deck_cards.push_back(temp.back());
		temp.pop_back();
	}
	//print_deck();
}

void Deck::print_deck()
{
	std::cout << "Printing deck: ";
	for (int i = 0; i < (int)deck_cards.size(); i++)
	{
		deck_cards[i].print_card();
	}
	std::cout << "\n";
}

/*
Modifies deck_cards and all player hands
*/
/*
void Deck::deal_hands(std::vector<Card> &hand1, std::vector<Card> &hand2, std::vector<Card> &hand3, std::vector<Card> &hand4)
{
	for (int i = 0; i < 13; i++)
	{
		hand1.push_back(deck_cards.back());
		deck_cards.pop_back();
	}
	for (int i = 13; i < 26; i++)
	{
		hand2.push_back(deck_cards.back());
		deck_cards.pop_back();
	}
	for (int i = 26; i < 39; i++)
	{
		hand3.push_back(deck_cards.back());
		deck_cards.pop_back();
	}
	for (int i = 39; i < 52; i++)
	{
		hand4.push_back(deck_cards.back());
		deck_cards.pop_back();
	}
}
*/

int Deck::close_deck()
{
	while (deck_cards.size() > 0)
	{
		deck_cards.pop_back();
	}
	return 0;
}