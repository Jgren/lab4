#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Declarations.h"

void Rigidbody::simulate(float timeStep)
{
}
bool Rigidbody::collision(Rigidbody* asteroid)
{
	return true;
}

Rigidbody::Rigidbody()
{
	rotation = 0;
	radius = 0;
	velocity = { 0,0 };
	acceleration = { 0,0 };
	position = { 0,0 };
}

//rotates the asteroid and also gives it a new position once it exit the screen
void Asteroid::simulate(float timeStep)
{
	rotation += rotSpeed * timeStep;
	position += velocity * timeStep;

	if (position.x > DISPLAY_WIDTH or position.x < 0)
	{
		det = Play::RandomRollRange(0, 3);
		scale = Play::RandomRollRange(10, 30);
		rotSpeed = Play::RandomRollRange(1, 8);

		if (det == 0)
		{
			position = { Play::RandomRollRange(0,DISPLAY_WIDTH),0};
			velocity.x = Play::RandomRollRange(-70, 70);
			velocity.y = Play::RandomRollRange(10, 100);
		}
		else if (det == 1)
		{
			position = { Play::RandomRollRange(0,DISPLAY_WIDTH),DISPLAY_HEIGHT};
			velocity.x = Play::RandomRollRange(-70, 70);
			velocity.y = Play::RandomRollRange(-10, -100);
		}
		else if (det == 2)
		{
			position = { 0 ,Play::RandomRollRange(0,DISPLAY_HEIGHT) };
			velocity.x = Play::RandomRollRange(10, 100);
			velocity.y = Play::RandomRollRange(-70, 70);
		}
		else if (det == 3)
		{
			position = { DISPLAY_WIDTH ,Play::RandomRollRange(0,DISPLAY_HEIGHT) };
			velocity.x = Play::RandomRollRange(-10, -100);
			velocity.y = Play::RandomRollRange(-70, 70);
		}
	}
}

//draw the asteroid and determine its radius
void Asteroid::draw()
{
	Play::DrawSpriteRotated("asteroid", position, 0, rotation, scale / 10, 1.0);
	radius = Play::GetSpriteHeight("asteroid") * scale / 10;
}

//randomizes spawnpoint, scale and rotation speed
Asteroid::Asteroid()
{
	det = Play::RandomRollRange(0, 6);
	scale = Play::RandomRollRange(10, 30);
	rotSpeed = Play::RandomRollRange(1, 8);

	if (det == 0)
	{
		position = { Play::RandomRollRange(0,DISPLAY_WIDTH),0 };
		velocity.x = Play::RandomRollRange(-70, 70);
		velocity.y = Play::RandomRollRange(10, 150);
	}
	else if (det == 1)
	{
		position = { Play::RandomRollRange(0,DISPLAY_WIDTH),DISPLAY_HEIGHT };
		velocity.x = Play::RandomRollRange(-70, 70);
		velocity.y = Play::RandomRollRange(-10, -150);
	}
	else if (det == 2)
	{
		position = { 0 ,Play::RandomRollRange(0,DISPLAY_HEIGHT) };
		velocity.x = Play::RandomRollRange(10, 150);
		velocity.y = Play::RandomRollRange(-70, 70);
	}
	else if (det == 3)
	{
		position = { DISPLAY_WIDTH ,Play::RandomRollRange(0,DISPLAY_HEIGHT) };
		velocity.x = Play::RandomRollRange(-10, -150);
		velocity.y = Play::RandomRollRange(-70, 70);
	}
	else if (det > 3)
	{
		position = { DISPLAY_WIDTH ,1000 };
		velocity.x = Play::RandomRollRange(-10, -150);
		velocity.y = Play::RandomRollRange(-70, 70);
	}

}

//lets ship rotate, add velocity and gives it new position if it tries to leave screen
void Ship::simulate(float timeStep)
{
	position += velocity * timeStep;
	velocity += acceleration * timeStep;
	acceleration.x = 0;
	acceleration.y = 0;

	if (velocity.x > 100)velocity.x = 100;
	if (velocity.x < -100)velocity.x = -100;
	if (velocity.y > 100)velocity.y = 100;
	if (velocity.y < -100)velocity.y = -100;

	if (position.x > DISPLAY_WIDTH)position.x = 0;
	if (position.x < 0)position.x = DISPLAY_WIDTH;
	if (position.y > DISPLAY_HEIGHT)position.y = 0;
	if (position.y < 0)position.y = DISPLAY_HEIGHT;

	det = Play::KeyDown(VK_RIGHT) - Play::KeyDown(VK_LEFT);
	rotation += 5 * det * timeStep;
	if (Play::KeyDown(VK_SPACE))
	{
		acceleration.x += shipThrust * sin(rotation) * timeStep;
		acceleration.y -= shipThrust * cos(rotation) * timeStep;
	}
}

//checks collision between asteroid radius and ship radius
bool Ship::collision(Rigidbody* asteroid)
{
	if (((position.x - asteroid->position.x) * (position.x - asteroid->position.x) + (position.y - asteroid->position.y) * (position.y - asteroid->position.y)) < asteroid->radius * radius)
	{
		position = { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT / 2 };
		velocity = { 0,0 };
		rotation = 0;
		return true;
	}
	return false;
}

//draws ship and determines its radius
void Ship::draw()
{
	radius = Play::GetSpriteHeight("ship") - 15;
	Play::DrawSpriteRotated("ship", position, 0, rotation, 0.5, 1.0);
}

//sets thrust and start position
Ship::Ship()
{
	shipThrust = 8000;
	position = { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT / 2 };
}

/*
class Rigidbody
{
public:
	float rotation, radius;
	Vector2D velocity, acceleration;
	Point2D position;

	virtual void simulate(float timeStep)
	{

	}

	virtual bool collision()
	{
		return false;
	}

	virtual void draw() = 0;
};



class Asteroid : Rigidbody
{
public:
	int det, rotSpeed;
	float scale, radius;
	Point2D position;

	void simulate(float timeStep)
	{
		rotation += rotSpeed * timeStep;
		position += velocity * timeStep;

		if (position.x > DISPLAY_WIDTH or position.x<0)
		{
			det = Play::RandomRollRange(0, 3);
			scale = Play::RandomRollRange(10, 30);
			rotSpeed = Play::RandomRollRange(1, 8);

			if (det == 0)
			{
				position = { Play::RandomRollRange(0,DISPLAY_WIDTH),0 };
				velocity.x = Play::RandomRollRange(-70, 70);
				velocity.y = Play::RandomRollRange(10, 100);
			}
			else if (det == 1)
			{
				position = { Play::RandomRollRange(0,DISPLAY_WIDTH),DISPLAY_HEIGHT };
				velocity.x = Play::RandomRollRange(-70, 70);
				velocity.y = Play::RandomRollRange(-10, -100);
			}
			else if (det == 2)
			{
				position = { 0 ,Play::RandomRollRange(0,DISPLAY_HEIGHT) };
				velocity.x = Play::RandomRollRange(10, 100);
				velocity.y = Play::RandomRollRange(-70, 70);
			}
			else if (det == 3)
			{
				position = { DISPLAY_WIDTH ,Play::RandomRollRange(0,DISPLAY_HEIGHT) };
				velocity.x = Play::RandomRollRange(-10, -100);
				velocity.y = Play::RandomRollRange(-70, 70);
			}
		}
	}

	void draw()
	{
		Play::DrawSpriteRotated("asteroid", position, 0, rotation, scale/10, 1.0);
		radius = Play::GetSpriteHeight("asteroid") * scale/10;
	}

	Asteroid()
	{
		det = Play::RandomRollRange(0, 6);
		scale = Play::RandomRollRange(10,30);
		rotSpeed = Play::RandomRollRange(1,8);

		if (det == 0)
		{
			position = { Play::RandomRollRange(0,DISPLAY_WIDTH),0 };
			velocity.x = Play::RandomRollRange(-70,70);
			velocity.y = Play::RandomRollRange(10, 150);
		}
		else if (det == 1)
		{
			position = { Play::RandomRollRange(0,DISPLAY_WIDTH),DISPLAY_HEIGHT };
			velocity.x = Play::RandomRollRange(-70, 70);
			velocity.y = Play::RandomRollRange(-10, -150);
		}
		else if (det == 2)
		{
			position = { 0 ,Play::RandomRollRange(0,DISPLAY_HEIGHT) };
			velocity.x = Play::RandomRollRange(10, 150);
			velocity.y = Play::RandomRollRange(-70, 70);
		}
		else if (det == 3)
		{
			position = { DISPLAY_WIDTH ,Play::RandomRollRange(0,DISPLAY_HEIGHT) };
			velocity.x = Play::RandomRollRange(-10, -150);
			velocity.y = Play::RandomRollRange(-70, 70);
		}
		else if (det >3)
		{
			position = { DISPLAY_WIDTH ,1000};
			velocity.x = Play::RandomRollRange(-10, -150);
			velocity.y = Play::RandomRollRange(-70, 70);
		}

	}

};


class Ship : Rigidbody
{
public:
	int det, shipSize;
	float shipThrust;

	void simulate(float timeStep)
	{

		det = Play::KeyDown(VK_RIGHT) - Play::KeyDown(VK_LEFT);
		rotation += 5*det * timeStep;

		if (Play::KeyDown(VK_SPACE))
		{
			acceleration.x += shipThrust * sin(rotation) * timeStep;
			acceleration.y -= shipThrust * cos(rotation) * timeStep;
		}
		position += velocity * timeStep;
		velocity += acceleration * timeStep;
		acceleration.x = 0;
		acceleration.y = 0;

		if (velocity.x > 100)velocity.x = 100;
		if (velocity.x < -100)velocity.x = -100;
		if (velocity.y > 100)velocity.y = 100;
		if (velocity.y < -100)velocity.y = -100;

		if (position.x > DISPLAY_WIDTH)position.x = 0;
		if (position.x < 0)position.x = DISPLAY_WIDTH;
		if (position.y > DISPLAY_HEIGHT)position.y = 0;
		if (position.y < 0)position.y = DISPLAY_HEIGHT;
	}

	bool collision(Point2D pos,float astroidradius)
	{
		if (((position.x - pos.x) * (position.x - pos.x) + (position.y - pos.y) * (position.y - pos.y)) < astroidradius * radius)
		{
			position = { DISPLAY_WIDTH / 2,DISPLAY_HEIGHT / 2 };
			velocity = { 0,0 };
			rotation = 0;
			return true;
		}
		return false;
	}

	void draw()
	{
		radius = Play::GetSpriteHeight("ship")-15;
		Play::DrawSpriteRotated("ship", position, 0, rotation, 0.5, 1.0);
	}

	Ship()
	{
		shipThrust = 8000;
		position = { DISPLAY_WIDTH/2,DISPLAY_HEIGHT/2 };
	}
};

*/