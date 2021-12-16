#pragma once
#include "Play.h"

const int DISPLAY_WIDTH = 640;
const int DISPLAY_HEIGHT = 360;
const int DISPLAY_SCALE = 2;
static int scoreCount = 0,highScore=0, j;

class Rigidbody
{
protected:

	float rotation;
	Vector2D velocity, acceleration;

public:

	float radius;
	Point2D position;

	virtual void simulate(float timeStep);
	virtual bool collision(Rigidbody* asteroid);
	virtual void draw() = 0;

	Rigidbody();
};

class Asteroid : public Rigidbody
{
private:
	int det, rotSpeed;
	float scale;

public:

	void simulate(float timeStep);
	void draw();

	Asteroid();
};

class Ship : public Rigidbody
{
private:
	int det, shipSize;
	float shipThrust;
public:

	void simulate(float timeStep);
	bool collision(Rigidbody* asteroid);
	void draw();

	Ship();

};