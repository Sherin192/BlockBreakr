#include "Ball.h"

Ball::Ball(): minVelocity(300.0f), maxVelocity(320.0f), velocity(300.0f), moveX(0.0f), moveY(0.0f), collision(false)
{
	buffer.loadFromFile("Sounds/sound.wav");
	sound.setBuffer(buffer);
	losebuffer.loadFromFile("Sounds/losepoint.wav");
	loseLive.setBuffer(losebuffer);
	load("images/ballBlue.png");
	getSprite().setOrigin(11, 11);
	getSprite().setPosition(400, 527);
	srand(time(NULL));

	do
	{
		angle = float(rand() % 360 + 1);
	}
	while (angle < 240 || angle > 300);
}

void Ball::update(float deltaTime, Paddle *paddle, Block * block, int arSize, int &score, int &lives)
{
	if (!start)
	{
		setPosition(sf::Vector2f(paddle->getPosition().x, paddle->getPosition().y - 23));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			start = true;
		else
			return;
	}

	//moveAmount is the hypotenuse of our triangle the amount that we want to move. We need 
	//to find the lenght of the olther sides of the triangle to know how much to move if each direction
	float moveAmount = velocity * deltaTime;

	/*linearVelocityX is the cos(angle) which is equal to the ratio of adjacent/hypotenuse. By multiplying it to 
	moveAmount we get the adjacent side of the triangle with it equal to the amount of space we want to move in x 
	direction */
	moveX = linearVelocityX(angle) * moveAmount;
	// same logic works for y coordinate but this time we have to use sin(angle) 
	moveY = linearVelocityY(angle) * moveAmount;
	
	//-----------------------------------------------------------------------------------------------------------------
	//--------------------------------- Collision with upper and lower wall -------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------
	if (getPosition().y + moveY <= 0 + 11)
	{
		angle = 360.0f - angle;

		if (angle < 0.0f) angle += 360.0f;
		if (angle > 360.0f) angle -= 360.0f;

		if (angle > 260.0f && angle < 270.0f) angle -= 5.0f + float(rand() % 5 + 1);
		if (angle > 270.0f && angle < 280.0f) angle += 5.0f + float(rand() % 5 + 1);
		if (angle == 90 || angle == 270) angle += 1;
		if (angle > 80.0f && angle < 90.0f) angle -= 5.0f + float(rand() % 5 + 1);
		if (angle > 90.0f && angle < 100.0f) angle += 5.0f + float(rand() % 5 + 1);

		moveY = -moveY;
	}
	if (getPosition().y + moveY >= 600 - 11)
	{
		if (lives > 1)
		{
			velocity = minVelocity;

			do
			{
				angle = float(rand() % 360 + 1);
			} while (angle < 240 || angle > 300);

			setPosition(sf::Vector2f(paddle->getPosition().x, paddle->getPosition().y - 23));
			setStart(false);
		}
		loseLive.play();
		lives--;
	}
	if (getPosition().x + moveX < 0 + 11 || getPosition().x + moveX > 800 - 11)
	{
		angle = 360.0f - (angle - 180);

		if (angle < 0.0f) angle += 360.0f;
		if (angle > 360.0f) angle -= 360.0f;

		if (angle > 170.0f && angle < 180.0f) angle -= 5.0f + float(rand() % 5 + 1);
		if (angle > 180.0f && angle < 190.0f) angle += 5.0f + float(rand() % 5 + 1);
		if (angle == 180 || angle == 360) angle += 1;
		if (angle > 350.0f && angle < 360.0f) angle -= 5.0f + float(rand() % 5 + 1);
		if (angle > 0.0f && angle < 10.0f) angle += 5.0f + float(rand() % 5 + 1);

		moveX = -moveX;
	}

	sf::FloatRect overlap;
	sf::FloatRect temp;
	int count = 0;
	int blockNumber = 0;

	
	if(collisionAABB(paddle->getBoundingRect(), getBoundingRect(), overlap))
	{
		sound.play();
		collisionManager(overlap, *paddle);
		if (paddle->getVelocity() > 0 && angle < 320 && angle > 30)
			angle += float(rand() % 2 + 1);
		else if (paddle->getVelocity() < 0 && angle < 320 && angle > 30)
			angle -= float(rand() % 2 + 1);
	}
	
	for (int n = 0; n < BLOCK_NUMBER; n++)
	{
		if (block[n].getBlockState() == INVISIBLE)
			continue;
		if (collisionAABB(block[n].getBoundingRect(), getBoundingRect(), temp))
		{
			sound.play();
				count++;				//number of collision

				switch (block[n].getBlockState())
				{
				case RED:
					score += RED;
					block[n].setBlockState(PURPLE);
					block[n].update();
					break;
				case PURPLE:
					score += PURPLE;
					block[n].setBlockState(YELLOW);
					block[n].update();
					break;
				case YELLOW:
					score += YELLOW;
					block[n].setBlockState(GREEN);
					block[n].update();
					break;
				case GREEN:
					score += GREEN;
					block[n].setBlockState(BLUE);
					block[n].update();
					break;
				case BLUE:
					score += BLUE;
					block[n].setBlockState(GREY);
					block[n].update();
					break;
				case GREY:
					score += GREY;
					block[n].setBlockState(INVISIBLE);
					block[n].update();
					break;
				}
			if (count == 1)
			{
				blockNumber = n;
				overlap = temp;
			}
			else if(count > 1)
			{
				if (temp.height > overlap.height)
				{
					overlap = temp;
					blockNumber = n;
				}
				else if (temp.width > overlap.width)
				{
					overlap = temp;
					blockNumber = n;
				}
				if (count == 2)
					break;
			}
		}
	}

	if(count > 0)
		collisionManager(overlap, block[blockNumber]);
	if(lives)				// moves only if we are alive
		getSprite().move(moveX, moveY);
}

float Ball::linearVelocityX(float angle)
{
	if (angle < 0) angle = 360 + angle;
	//radians = degrees * PI / 180
	float radians = angle * (3.1415926 / 180);
	//cos(angle in radians) = the x coordinate
	return (float)std::cos(radians);
}
// returns a value between -1 and 1 
float Ball::linearVelocityY(float angle)
{
	if (angle < 0) angle = 360 + angle;
	//radians = degrees * PI / 180
	float radians = angle * (3.1415926 / 180);
	//sin(angle) = the y coordinate
	return (float)std::sin(radians);
}
bool Ball::collisionAABB(sf::FloatRect bb1, sf::FloatRect bb2,sf::FloatRect &overlap)
{
	if (bb1.intersects(bb2, overlap))						//checks for intersection
	{
		return true;
	}
	return false;
}

void Ball::collisionManager(sf::FloatRect overlap, GameObject box)
{	
	sf::Vector2f pos1 = box.getPosition();
	sf::Vector2f pos2 = getPosition();
	if (overlap.height > overlap.width)					//collision on x axis 
	{
			if (pos1.x > pos2.x)
			{
				if (angle > 270 || angle < 90)
				{
					bounceOffX();
					rangeAngle();
					getSprite().move(-overlap.width, 0);
					moveX = -moveX;
				}
				else if (angle >= 90 || angle <= 270)
				{
					bounceOffY();
					rangeAngle();
					if (pos1.y > pos2.y)
						getSprite().move(0, -overlap.height);
					else
						getSprite().move(0, overlap.height);
					moveY = -moveY;
				}
			}
			else if (pos1.x < pos2.x)
			{
				if (angle > 90 && angle < 270)
				{
					bounceOffX();
					rangeAngle();
						getSprite().move(overlap.width, 0);
					moveX = -moveX;
				}
				else if (angle <= 90 || angle >= 270)
				{
					bounceOffY();
					rangeAngle();
					if (pos1.y > pos2.y)
						getSprite().move(0, -overlap.height);
					else
						getSprite().move(0, overlap.height);
					moveY = -moveY;
				}
			}
	}
	else 
	{
		if (pos1.y > pos2.y)
		{
			if (pos2.x > pos1.x - box.getBoundingRect().width/2 && pos2.x < pos1.x + box.getBoundingRect().width / 2)
			{
				bounceOffY();
				rangeAngle();
				getSprite().move(0, -overlap.height);
				moveY = -moveY;
			}
			else
			{
				if (pos1.x > pos2.x && (angle > 270 || angle < 90))
				{
						bounceOffX();
						rangeAngle();
						getSprite().move(-overlap.width, 0);
						moveX = -moveX;
				}
				else if (pos1.x < pos2.x && (angle > 90 && angle < 270))
				{
						bounceOffX();
						rangeAngle();
						getSprite().move(overlap.width, 0);
						moveX = -moveX;
				}
				else
				{
					bounceOffY();
					rangeAngle();
					getSprite().move(0, -overlap.height);
					moveY = -moveY;
				}
			}
		}
		else if (pos1.y < pos2.y)
		{
			if (pos2.x > pos1.x - box.getBoundingRect().width / 2 && pos2.x < pos1.x + box.getBoundingRect().width / 2)
			{
				bounceOffY();
				rangeAngle();
				getSprite().move(0, overlap.height);
				moveY = -moveY;
			}
			else
			{
				if (pos1.x > pos2.x && (angle > 270 || angle < 90))
				{
					
						bounceOffX();
						rangeAngle();
						getSprite().move(-overlap.width, 0);
						moveX = -moveX;
				}
				else if (pos1.x < pos2.x && (angle > 90 && angle < 270))
				{
						bounceOffX();
						rangeAngle();
						getSprite().move(overlap.width, 0);
						moveX = -moveX;
				}
				else
				{
					bounceOffY();
					rangeAngle();
					getSprite().move(0, -overlap.height);
					moveY = -moveY;
				}
			}
		}
	}
}