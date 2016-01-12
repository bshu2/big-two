#pragma once

#ifndef CARD_H
#define CARD_H

class Card
{
public:
	Card();
	Card(int suit, int value);
	Card(const Card &C);

	Card& operator=(const Card &C);
	bool operator==(const Card &C);
	bool operator!=(const Card &C);
	bool operator<(const Card &C);
	bool operator>(const Card &C);
	//bool operator<=(const Card &C);
	//bool operator>=(const Card &C);

	int get_suit();
	int get_value();
	bool is_selected();

	void set_selected(bool sel);
	void print_card();

private:
	int suit;
	int value;
	bool selected;
};

#endif

