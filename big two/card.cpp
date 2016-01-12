#include "card.h"
#include <iostream>

Card::Card()
{
	suit = 0;
	value = 1;
	selected = false;
}

Card::Card(int suit, int value)
{
	this->suit = suit;
	this->value = value;
	selected = false;
}

Card::Card(const Card &C)
{
	this->suit = C.suit;
	this->value = C.value;
	this->selected = C.selected;
}

Card& Card::operator=(const Card &C)
{
	this->suit = C.suit;
	this->value = C.value;
	this->selected = C.selected;

	return *this;
}

bool Card::operator==(const Card &C)
{
	return (this->suit == C.suit && this->value == C.value);
}

bool Card::operator!=(const Card &C)
{
	return (this->suit != C.suit && this->value != C.value);
}

bool Card::operator<(const Card &C)
{
	return (((this->value + 13) % 16 < (C.value + 13) % 16) || (this->suit < C.suit && this->value == C.value));
}

bool Card::operator>(const Card &C)
{
	return (((this->value + 13) % 16 > (C.value + 13) % 16) || (this->suit > C.suit && this->value == C.value));
}

/* //probably never will be used because cards are unique
bool Card::operator<=(const Card &C)
{
	return (((this->value + 13) % 15 < (C.value + 13) % 15) || (this->suit <= C.suit && this->value == C.value));
}

bool Card::operator>=(const Card &C)
{
	return (((this->value + 13) % 15 > (C.value + 13) % 15) || (this->suit >= C.suit && this->value == C.value));
}
*/

int Card::get_suit()
{
	return suit;
}

int Card::get_value()
{
	return value;
}

bool Card::is_selected()
{
	return selected;
}

void Card::set_selected(bool sel)
{
	selected = sel;
}

void Card::print_card()
{
	if (value >= 2 && value <= 10)
	{
		std::cout << "(" << value << "," << suit << ")";
	}
	else
	{
		char c = 'x';
		switch (value)
		{
		case 1:
			c = 'A';
			break;
		case 11:
			c = 'J';
			break;
		case 12:
			c = 'Q';
			break;
		case 13:
			c = 'K';
			break;
		}
		std::cout << "(" << c << "," << suit << ")";
	}
}