#include "Menu.h"

Menu::Menu()
{	
	font.loadFromFile("Fonts/battlev2.ttf");

	tips.setFont(font);
	tips.setCharacterSize(20);
	tips.setPosition(250, 300);
	tips.setColor(sf::Color::Cyan);
	tips.setString("P - pause \nSpace - start ball \narrows - move left and right");
	background.action = Nothing;
	background.texture.loadFromFile("images/blockbreaker.png");
	background.sprite.setTexture(background.texture);

	play.action = Play;
	play.texture.loadFromFile("images/play.png");
	play.sprite.setTexture(play.texture);
	play.sprite.setOrigin(95, 25);
	play.sprite.setPosition(120, 350);

	hScores.action = HScores;
	hScores.texture.loadFromFile("images/Hscores.png");
	hScores.sprite.setTexture(hScores.texture);
	hScores.sprite.setOrigin(95, 25);
	hScores.sprite.setPosition(120, 400);
	
	options.action = Options;
	options.texture.loadFromFile("images/options.png");
	options.sprite.setTexture(options.texture);
	options.sprite.setOrigin(95, 25);
	options.sprite.setPosition(120, 450);

	exit.action = Exit;
	exit.texture.loadFromFile("images/exit.png");
	exit.sprite.setTexture(exit.texture);
	exit.sprite.setOrigin(95, 25);
	exit.sprite.setPosition(120, 500);

	menuObjects.push_back(background);
	menuObjects.push_back(play);
	menuObjects.push_back(hScores);
	menuObjects.push_back(options);
	menuObjects.push_back(exit);
}
Menu::~Menu()
{
}

Menu::Action Menu::manageMenu(sf::RenderWindow &window)
{
	sf::Event event;
	Action result = Nothing;
	while (true)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::MouseButtonPressed)
			{
				result = handleClick(event.mouseButton.x, event.mouseButton.y);
			}
			if (event.type == sf::Event::EventType::Closed)
			{
				result = Exit;
			}
			if (result == Play || result == Exit)
				return result;
			else if (result == HScores)
			{
				draw(window);
				showHscores(window);
			}
			else if (result == Options)
			{
				draw(window);
				window.draw(tips);
			}			
			if (result != HScores && result != Options)
				draw(window);
			window.display();
			
		}
	}
}
Menu::Action Menu::handleClick(int x, int y)
{
	std::list<Item>::iterator it;

	for (it = menuObjects.begin(); it != menuObjects.end(); ++it)
	{
		if (it->action == Nothing)
			continue;
		sf::Rect<float> menuItemRect = it->sprite.getGlobalBounds();
		
		if (menuItemRect.top + menuItemRect.height > y &&
			menuItemRect.top < y &&
			menuItemRect.left < x &&
			menuItemRect.width > x)
		{
			return it->action;
		}
	}
	return Nothing;
}
void Menu::draw(sf::RenderWindow &window)
{
	std::list<Item>::iterator it;

	for (it = menuObjects.begin(); it != menuObjects.end(); ++it)
	{
		window.draw(it->sprite);
	}
}
void Menu::showHscores(sf::RenderWindow &window)
{
	int InitXposition = 400;
	int InitYposition = 300;
	int ofsetX = 200;
	int ofsetY = 10;
	std::ifstream scores;
	char score[10];
	char name[15];
	int i = 0;
	scores.open("scores.txt");
	if (scores.is_open())
	{ 
		while (!scores.eof())
		{
			text[i].setFont(font);
			text[i].setColor(sf::Color::Red);
			text[i].setCharacterSize(25);
			if (i % 2 == 0)
			{
				scores >> name;
				text[i].setString(name);
				text[i].setPosition(InitXposition , InitYposition + i * ofsetY);
			}
			else
			{
				scores >> score;
				text[i].setString(score);
				text[i].setPosition(InitXposition + ofsetX, InitYposition + ((i - 1) * ofsetY));
			}		
			window.draw(text[i]);
			i++;
		}
	}
	scores.close();
	
}