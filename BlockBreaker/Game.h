#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Menu.h"
#include "GUI.h"
#include "Block.h"
#include "Ball.h"
#include "Paddle.h"
#include <iostream>
#include <fstream>
const sf::Vector2u SCREEN_SIZE(800, 600);
const int levels[3][80] =
{
	{1,1,1,1,1,1,1,1,1,1,
	 1,1,1,1,1,1,1,1,1,1,
	 1,1,1,1,1,1,1,1,1,1, 
	 1,1,1,1,1,1,1,1,1,1, 
	 1,1,1,1,1,1,1,1,1,1, 
	 1,1,1,1,1,1,1,1,1,1, 
	 1,1,1,1,1,1,1,1,1,1, 
	 1,1,1,1,1,1,1,1,1,1 
	},
	{2,1,1,1,1,1,1,1,1,2,
	 2,2,1,1,1,1,1,1,2,1,
	 1,1,2,1,1,1,1,2,1,1,
	 2,1,1,2,3,3,2,1,1,1,
	 1,1,1,2,3,3,2,1,1,1,
	 1,1,2,1,1,1,1,2,1,2,
	 1,2,1,1,1,1,1,1,2,1,
	 2,1,1,1,1,1,1,1,1,2
	},
	{2,1,2,1,2,2,1,2,1,2,
	2,2,1,2,1,1,2,1,2,1,
	1,1,2,1,2,2,1,2,1,1,
	2,1,1,2,3,3,2,1,1,1,
	1,1,1,2,3,3,2,1,1,1,
	1,1,2,1,2,2,1,2,1,2,
	1,2,1,2,1,1,2,1,2,1,
	2,1,2,1,2,2,1,2,1,2
	}

};
enum STATE { UNINIT, MENU, PLAY, PAUSE, HIGHTSCORES, ENDSCREEEN };
enum LEVEL {ONE = 0, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN};
class Game
{
	sf::Texture textureBg;
	sf::Sprite bg;
	bool pause;
	bool exit;
	sf::Clock ElapsedTime;
	sf::RenderWindow window;
	Paddle *paddle;
	Block *blocks;
	Ball *ball;
	STATE gameState;
	LEVEL level;
	GUI gui;
	sf::Music music;

	void init();
	void menuManager(sf::RenderWindow &window);
	void gameLoop();
	void loadBlocks();
	void loadLevelFromFile(const int level);
	void setBlocks();
	void setlevel();					
	void setScore();		
	void updateBlocks();
	bool drawBlocks();
public:
	Game();
};
#endif
