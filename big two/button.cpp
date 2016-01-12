#include "button.h"

Button::Button()
{
	trigger_box.left = 0;
	trigger_box.top = 0;
	trigger_box.width = 0;
	trigger_box.height = 0;
}

Button::Button(int x, int y, int width, int height)
{
	trigger_box.left = x;
	trigger_box.top = y;
	trigger_box.width = width;
	trigger_box.height = height;
}

bool Button::handle_event(sf::Event *e)
{
	if (e->type == sf::Event::MouseButtonPressed)
	{
		if (e->mouseButton.button == sf::Mouse::Left && trigger_box.contains(e->mouseButton.x, e->mouseButton.y))
		{
			return true;
		}
	}
	return false;

	/*switch (e->type)
	{
	case sf::Event::MouseButtonPressed:
	//perform an action if mouse left clicks inside box
	if (e->mouseButton.button == sf::Mouse::Left && trigger_box.contains(e->mouseButton.x, e->mouseButton.y))
	{
	return true;
	}
	break;
	default:
	break;
	}*/
}

void Button::set_trigger_box(int x, int y, int width, int height)
{
	trigger_box.left = x;
	trigger_box.top = y;
	trigger_box.width = width;
	trigger_box.height = height;
}
