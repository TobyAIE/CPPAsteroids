#include "Asteroid.h"
#include <iostream>
Asteroid::Asteroid()
{

}
Asteroid::~Asteroid()
{

}

//-------------------------------------------------------------------------------
//Updates the position of the asteroid based on its rotation
//-------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------



//-------------------------------------------------------------------------------
// Draws the Asteroid based on position and size
//-------------------------------------------------------------------------------
void Asteroid::Draw()
{
	DrawCircleLines(position.x, position.y, size, WHITE);
}
//-------------------------------------------------------------------------------



//-------------------------------------------------------------------------------
//Will spawn an asteroid in off-screen at a random y position
// - Requres a 'level' for the asteroid which changes its size
//-------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------