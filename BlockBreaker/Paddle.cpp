#include "Paddle.h"

Paddle::Paddle(): velocity(0.0f), maxVelocity(250.0f)
{
	load("images/paddleBlu.png");
	getSprite().setOrigin(52, 12);
	getSprite().setPosition(400, 550);
}
Paddle::~Paddle()
{

}
void Paddle::update(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		velocity = -maxVelocity;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		velocity = maxVelocity;
	}
	else
	{
		velocity = 0;
	}

	sf::Vector2f pos = this->getPosition();

	if (pos.x <= 52)
	{
		pos.x = 53;
		velocity = maxVelocity;
	}
	else if (pos.x >= (800 - 52))
	{
		pos.x = 800 - 53;
		velocity = -maxVelocity;
	}

	getSprite().move(velocity * deltaTime, 0);
}

float Paddle::getVelocity()
{
	return velocity;
}
