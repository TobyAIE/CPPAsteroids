#pragma once
#include "GameObject.h"
class Asteroid : public GameObject
{
public:
	Asteroid();
	~Asteroid();

	bool destroyed;

	void Update();

	void Draw();

	int asteroidLevel;

	void SpawnAsteroid(int level);

	float size;

private:

};

