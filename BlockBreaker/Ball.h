#ifndef BALL_H
#define BALL_H
#include <cstdlib>
#include <math.h> 
#include "GameObject.h"
#include "Block.h"
#include "Paddle.h"

//#include "Game.h"

class Ball : public GameObject
{
	sf::SoundBuffer buffer;
	sf::SoundBuffer losebuffer;
	sf::Sound sound;
	sf::Sound loseLive;

	float radius;
	float velocity;
	const float maxVelocity;
	const float minVelocity;

	float angle;
	float moveX;
	float moveY;

	bool collision = false;
	bool start = false;

	
	bool collisionAABB(sf::FloatRect bb1, sf::FloatRect bb2, sf::FloatRect &overlap);
	void collisionManager(sf::FloatRect overlap, GameObject box);
	//bool AABBtoCircleCollision(GameObject block, sf::Vector2f pos, sf::Vector2f &closest);
	//float clamp(float value, float min, float max);
	void rangeAngle() {
		if (angle < 0.0f) angle += 360.0f;
		if (angle > 360.0f) angle -= 360.0f;
	}
	void bounceOffX() { angle = 360.0f - (angle - 180.0f); }
	void bounceOffY() { angle = 360.0f - angle; }
public:
	Ball();
	~Ball();

	float linearVelocityX(float angle);
	float linearVelocityY(float angle);
	void update(float deltaTime, Paddle *paddle, Block * block, const int arSize, int &socre, int &lives);
	void setStart(bool st) { start = st; };
	float getVelocity() { return velocity; }
	float getAngle() { return angle; }
	float getMoveX() { return moveX; }
	float getMoveY() { return moveY; }
	void setMoveX(const float mx) { moveX = mx; }
	void setMoveY(const float my) { moveY = my; }
};



#endif
