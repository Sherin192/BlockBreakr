#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include <iostream>
class GameObject
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	bool isLoaded;
	std::string fileName;
public:
	GameObject();
	virtual ~GameObject();

	void virtual load(std::string fileName);
	void virtual update();
	void virtual draw(sf::RenderWindow &window);

	sf::Sprite & getSprite();
	virtual sf::Rect<float> getBoundingRect() const;
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f);
};




#endif

