#include "Game.h"

Game::Game(): exit(false), pause(false)
{
	gameState = UNINIT;
	level = ONE;
	window.create(sf::VideoMode(800, 600), "Block Breaker");
	window.setFramerateLimit(60);
	init();
}

Game::~Game()
{
}

void Game::init()
{
	music.openFromFile("level2.ogg");
	music.setLoop(true);

	textureBg.loadFromFile("images/bg.jpg");
	bg.setTexture(textureBg);
	ElapsedTime.restart();
	gameState = MENU;
	blocks = new Block[ROWS * COLUMNS];
	ball = new Ball;
	paddle = new Paddle;
	//loadBlocks();
	loadLevelFromFile(level);
	setBlocks();

	while (!exit)
	{
		gameLoop();
	}
}

void Game::gameLoop()
{
	int n = 0;
	float deltaTime = 0.0f;
	sf::Event event;
	window.pollEvent(event);
	
	switch(gameState)
	{
	case MENU:
		menuManager(window);
		break;
	case PLAY:
		if (event.type == sf::Event::Closed)
			gameState = ENDSCREEEN;
			//exit = true;
		deltaTime = ElapsedTime.restart().asSeconds();
		
		ball->update(deltaTime, paddle, &blocks[0], BLOCK_NUMBER, gui.getScore(), gui.getLives());
		paddle->update(deltaTime);
		gui.update();

		if (gui.getLives() == 0)
			gameState = ENDSCREEEN;
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::P)
			{
				pause = true;
				gui.setPause(pause);
				gameState = PAUSE;
			}
		}

		window.draw(bg);
		if (drawBlocks())
		{
			setlevel();
			gui.setLevel(level);
			ball->setPosition(sf::Vector2f(paddle->getPosition().x, paddle->getPosition().y - 23));
			ball->setStart(false);
			//loadBlocks();
			loadLevelFromFile(level);
		}
		ball->draw(window);
		paddle->draw(window);
		gui.draw(window);
		window.display();
		
		break;
	case PAUSE:
		while (pause)
		{
			window.pollEvent(event);
			if (event.type == sf::Event::Closed)
			{
				gameState = ENDSCREEEN;
				pause = false;
			}
			if (event.type == sf::Event::KeyReleased)
			{ 
				if (event.key.code == sf::Keyboard::P)
				{
					gameState = PLAY;
					pause = false;
					gui.setPause(pause);
					ElapsedTime.restart();
				}
			}
		}
		break;
	case HIGHTSCORES:
		break;
	case ENDSCREEEN:
		//gui.gameOver(window);
		delete[] blocks;
		delete ball;
		delete paddle;
		exit = true;
		break;
	}
	//
}


void Game::setBlocks()
{
	int n = 0;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			blocks[n].setPosition(sf::Vector2f(112 + j* BLOCK_WIDTH, 56 + i * BLOCK_HEIGHT));
			n++;
		}
	}
}
void Game::updateBlocks()
{
	for (int i = 0; i < BLOCK_NUMBER; i++)
		blocks[i].update();
}
bool Game::drawBlocks()
{
	int count = 0;
	int n = 0;
	for (int i = 0; i < COLUMNS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (blocks[n].getBlockState() != INVISIBLE)
			{
				count++;
				blocks[n].draw(window);
			}
			n++;
		}
	}
	if (count == 0)
		return true;

	return false;
	
}

void Game::loadBlocks()
{
	for (int i = 0; i < BLOCK_NUMBER; i++)
	{
		if (levels[level][i] == 1)
		{
			blocks[i].setBlockState(GREY);
			blocks[i].update();
		}
		else if (levels[level][i] == 2)
		{
			blocks[i].setBlockState(BLUE);
			blocks[i].update();
		}
		else if (levels[level][i] == 3)
		{
			blocks[i].setBlockState(GREEN);
			blocks[i].update();
		}
		else if (levels[level][i] == 4)
		{
			blocks[i].setBlockState(YELLOW);
			blocks[i].update();
		}
		else if (levels[level][i] == 5)
		{
			blocks[i].setBlockState(PURPLE);
			blocks[i].update();
		}
		else if (levels[level][i] == 6)
		{
			blocks[i].setBlockState(RED);
			blocks[i].update();
		}

	

	}
}

void Game::menuManager(sf::RenderWindow &window)
{
	Menu menu;
	menu.draw(window);
	window.display();
	Menu::Action action;
	action = menu.manageMenu(window);

	switch (action)
	{
	case Menu::Play:
		gameState = PLAY;
		break;
	case Menu::Exit:
		gameState = ENDSCREEEN;
	}
}

void Game::loadLevelFromFile(const int level)
{
	std::string line;
	char block;
	bool read = true;
	std::ifstream file;
	file.open("levels.txt");
	if (file.is_open())
	{
		while (read)
		{
			std::getline(file, line);
			if (line == std::to_string(level))
			{
				for (int i = 0; i < BLOCK_NUMBER; i++)
				{
					do
					{
						file.get(block);
					} while (!isalnum(block));
						
					if (block == '1')
					{
						blocks[i].setBlockState(GREY);
						blocks[i].update();
					}
					else if (block == '2')
					{
						blocks[i].setBlockState(BLUE);
						blocks[i].update();
					}
					else if (block == '3')
					{
						blocks[i].setBlockState(GREEN);
						blocks[i].update();
					}
					else if (block == '4')
					{
						blocks[i].setBlockState(YELLOW);
						blocks[i].update();
					}
					else if (block == '5')
					{
						blocks[i].setBlockState(PURPLE);
						blocks[i].update();
					}
					else if (block == '6')
					{
						blocks[i].setBlockState(RED);
						blocks[i].update();
					}
						
				}
				read = false;
			}
		}
	}
	file.close();
}

void Game::setlevel()
{
	if (level == ONE)
	{
		music.openFromFile("level1.ogg");
		level = TWO;
	}
	else if (level == TWO)
	{
		level = THREE;
	}
	else if (level == THREE)
	{
		level = FOUR;
	}
	else if (level == FOUR)
	{
		level = FIVE;
	}
	else if (level == FIVE)
	{
		level = SIX;
	}
	else if (level == SIX)
	{
		level = SEVEN;
	}
	else if (level == SEVEN)
	{
		level = EIGHT;
	}
	else if (level == EIGHT)
	{
		level = NINE;
	}
	else if (level == NINE)
	{
		level = TEN;
	}
	setScore();
}

void Game::setScore()
{
	if (gui.getLives() == 3)
		gui.setScore(gui.getScore() + 100);
	if (gui.getLives() == 2)
		gui.setScore(gui.getScore() + 50);
	if (gui.getLives() == 1)
		gui.setScore(gui.getScore() + 25);
}

