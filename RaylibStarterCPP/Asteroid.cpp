#include "Asteroid.h"
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