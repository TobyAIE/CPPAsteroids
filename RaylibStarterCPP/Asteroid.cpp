#include "Asteroid.h"
#include <iostream>
Asteroid::Asteroid()
{

}
Asteroid::~Asteroid()
{

}

void Asteroid::Update()
{
	position.x += cos(rotation * DEG2RAD) * 1.5f;
	position.y += sin(rotation * DEG2RAD) * 1.5f;
	if (destroyed)
	{
		position.x = -800;
		position.y = -800;
	}
}

void Asteroid::Draw()
{
	DrawCircleLines(position.x, position.y, size, WHITE);
}

void Asteroid::SpawnAsteroid(int level)
{
	position.x = -40;
	position.y = rand() % 800;
	rotation = rand() % 360;
	destroyed = false;
	switch (level)
	{
	case 1:
		size = 40;
		break;
	case 2:
		size = 20;
		break;
	case 3:
		size = 10;
		break;
	default:
		break;
	}
	asteroidLevel = level;
}
