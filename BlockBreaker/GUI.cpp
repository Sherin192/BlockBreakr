#include "GUI.h"

GUI::GUI(): lives(3), score(0), level(1)
{
	font.loadFromFile("Fonts/battlev2.ttf");

	textLives.setFont(font);
	textLives.setCharacterSize(20);
	textLives.setString("Lives:");
	textLives.setColor(sf::Color::Cyan);
	textLives.setPosition(sf::Vector2f(10, 10));

	valueLives.setFont(font);
	valueLives.setString(std::to_string(lives));
	valueLives.setCharacterSize(20);
	valueLives.setColor(sf::Color::Cyan);
	valueLives.setPosition(sf::Vector2f(110, 10));

	textScore.setFont(font);
	textScore.setString("Score:");
	textScore.setCharacterSize(20);
	textScore.setColor(sf::Color::Cyan);
	textScore.setPosition(sf::Vector2f(330, 10));

	valueScore.setFont(font);
	valueScore.setString(std::to_string(score));
	valueScore.setCharacterSize(20);
	valueScore.setColor(sf::Color::Cyan);
	valueScore.setPosition(sf::Vector2f(450, 10));

	textLevel.setFont(font);
	textLevel.setString("Level:");
	textLevel.setCharacterSize(20);
	textLevel.setColor(sf::Color::Cyan);
	textLevel.setPosition(sf::Vector2f(660, 10));

	valueLevel.setFont(font);
	valueLevel.setString(std::to_string(level));
	valueLevel.setCharacterSize(20);
	valueLevel.setColor(sf::Color::Cyan);
	valueLevel.setPosition(sf::Vector2f(770, 10));

	textMessage.setFont(font);
	textMessage.setCharacterSize(50);
	textMessage.setColor(sf::Color::Cyan);
	textMessage.setPosition(250, 300);
	textMessage.setString("Pause");

}
GUI::~GUI()
{}

void GUI::update()
{
	valueLives.setString(std::to_string(lives));
	valueScore.setString(std::to_string(score));
	valueLevel.setString(std::to_string(level));
}
void GUI::draw(sf::RenderWindow &window)
{
	window.draw(textLives);
	window.draw(textScore);
	window.draw(textLevel);
	window.draw(valueLives);
	window.draw(valueScore);
	window.draw(valueLevel);
	if (go)
	{
		window.draw(textGameOver);
		window.draw(textName);
	}
	if(pause)
		window.draw(textMessage);
}

void GUI::setLives(const int lives)
{
	this->lives = lives;
}
void GUI::setScore(const int score)
{
	this->score = score;
}
void GUI::setLevel(const int level)
{
	this->level = level + 1;
}

std::string GUI::getKeyboardInput(sf::RenderWindow &window)
{
	sf::Event event;
	bool done = false;
	std::string name;
	while(name.size() < 15 && !done)  
	{ 
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode == 13)
			{
				done = true;
			}
			else
			{
				name += event.text.unicode;
				showNameOnScreen(window, name);
			}	
		}
	}
	draw(window);
	window.display();
	}
	return name;
}

void GUI::loadScoreFromFile()
{
	std::ifstream file;
	file.open("scores.txt");
	for (int i = 0; i < ar_size; i++)
	{
		file >> names[i];
		file >> scores[i];
	}
	file.close();
}

void GUI::updateScore(sf::RenderWindow &window)
{
	int i_scores[ar_size];
	int place;
	for (int i = 0; i < ar_size; i++)
	{
		i_scores[i] = atoi(scores[i].c_str());
	}

	if (score >= i_scores[ar_size - 1])
	{
		for (int i = ar_size - 1; i >= 0; i--)
		{
			if (score >= i_scores[i])
			{
				place = i;
			}
		}
		for (int i = ar_size - 1; i >= place; i--)
		{
			i_scores[i] = i_scores[i - 1];
			names[i] = names[i - 1];
		}
		names[place] = getKeyboardInput(window);
		i_scores[place] = score;

		for (int i = 0; i < ar_size; i++)
		{
			scores[i] = std::to_string(i_scores[i]);
		}
	}
}
void GUI::saveScoreToFile()
{
	std::ofstream file;
	file.open("scores.txt", std::fstream::out | std::fstream::trunc);

	for (int i = 0; i < ar_size; i++)
	{
		file << names[i] << " " << scores[i];
		if (i < ar_size - 1)
			file << std::endl;
	}
	file.close();
}
void GUI::gameOver(sf::RenderWindow &window)
{
	go = true;
	textGameOver.setFont(font);
	textGameOver.setCharacterSize(30);
	textGameOver.setColor(sf::Color::Cyan);
	textGameOver.setPosition(250, 300);
	textGameOver.setString("Game Over");

	textName.setFont(font);
	textName.setCharacterSize(25);
	textName.setColor(sf::Color::Cyan);
	textName.setPosition(320, 330);

	loadScoreFromFile();
	updateScore(window);
	saveScoreToFile();
}

void GUI::showNameOnScreen(sf::RenderWindow &window, std::string name)
{
	textName.setString(name);
}