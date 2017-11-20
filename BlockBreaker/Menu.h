#ifndef MENU_H
#define MENU_H

#include "Game.h"
#include <list>
#include <fstream>
class Menu
{
public:
	enum Action { Nothing, Play, HScores, Options, Exit };
	Menu();
	~Menu();
	Action manageMenu(sf::RenderWindow &window);
	Action handleClick(int x, int y);
	void draw(sf::RenderWindow & window);
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Font font;
	sf::Text text[20];
	sf::Text tips;
	void showHscores(sf::RenderWindow &window);
	struct Item
	{
		sf::Texture texture;
		sf::Sprite sprite;
		Action action;
	};
	Item background;
	Item play;
	Item hScores;
	Item options;
	Item exit;
	std::list<Item> menuObjects;
};


#endif