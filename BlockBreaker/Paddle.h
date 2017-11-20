#ifndef PADDLE_H
#define PADDLE_H

#include "GameObject.h"
//#include "Game.h"
class Paddle : public GameObject
{
	float velocity;
	float maxVelocity;
public:
	Paddle();
	~Paddle();
	void update(float deltaTime);
	float getVelocity();
};





#endif