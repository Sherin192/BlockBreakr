#include "GameObject.h"

GameObject::GameObject(): isLoaded(false)
{
	
}
GameObject::~GameObject()
{

}

void GameObject::load(std::string fileName)
{
	if (texture.loadFromFile(fileName))
	{
		sprite.setTexture(texture);
		isLoaded = true;
	}
		
}
void GameObject::update()
{

}

void GameObject::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

sf::Vector2f GameObject::getPosition()
{
	return sprite.getPosition();
}
sf::Rect<float> GameObject::getBoundingRect() const
{
	return sprite.getGlobalBounds();
}
void GameObject::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

sf::Sprite & GameObject::getSprite()
{
	return sprite;
}


