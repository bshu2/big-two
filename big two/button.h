#pragma once
#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <iostream>
#include <string>

class Button
{
public:
	Button();
	Button(int x, int y, int width, int height);

	bool handle_event(sf::Event *e);

	void set_trigger_box(int x, int y, int width, int height);


private:
	sf::IntRect trigger_box;
};

#endif
