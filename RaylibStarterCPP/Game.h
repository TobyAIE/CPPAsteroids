#pragma once

#include "GameObject.h"

class Game
{
public:
	void Init();
	void Update();
	void Draw();

private:
	int asteroidCount;

	GameObject* asteroids;

};

