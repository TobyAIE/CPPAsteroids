#pragma once

#include "GameObject.h"

class Game
{
public:
	void Init();
	void Update();
	void Draw();

	void Menu();

private:
	int asteroidCount;

	GameObject* asteroids;

	int lives;

	bool startGame;
	int frameTimer;

	bool alive;
	bool canSpawn;
};

