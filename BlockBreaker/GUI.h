#ifndef H_GUI
#define H_GUI

#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>
class GUI
{
	sf::Font font;

	sf::Text textLives;
	sf::Text valueLives;
	sf::Text textScore;
	sf::Text valueScore;
	sf::Text textLevel;
	sf::Text valueLevel;

	sf::Text textMessage;
	sf::Text textGameOver;
	sf::Text textName;
	int lives;
	int score;
	int level;
	
	static const int ar_size = 10;
	bool go = false;
	bool pause = false;
	std::string names[10];
	std::string scores[10];

	std::string getKeyboardInput(sf::RenderWindow &window);

public:
	GUI();
	~GUI();
	void gameOver(sf::RenderWindow &window);
	void showNameOnScreen(sf::RenderWindow &window, std::string name);
	void loadScoreFromFile();
	void updateScore(sf::RenderWindow &window);
	void saveScoreToFile();

	int& getLives() { return lives; }
	void setLives(const int lives);

	int& getScore() { return score; }
	void setScore(const int score);

	int& getLevel() { return level; }
	void setLevel(const int level);

	
	void setPause(bool p) { pause = p; }

	void update();
	void draw(sf::RenderWindow &window);
};


#endif