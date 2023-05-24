#pragma once
#include "GameObject.h"
class Asteroid : public GameObject
{
public:
	Asteroid();
	~Asteroid();

	bool destroyed;

	void Update();

	int asteroidLevel;

private:

};

