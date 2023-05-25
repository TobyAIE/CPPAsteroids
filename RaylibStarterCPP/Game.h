#pragma once

#include "GameObject.h"
#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"

class Game
{
public:
	
	void Init();
	void DeInit();
	void Update();
	void Draw();

	void Menu();

private:
	int asteroidCount;

	int maxAsteroids;

	int score;

	int bulletCount;

	Bullet* bullets;

	Asteroid* asteroids;

	int lives;

	bool startGame;
	int frameTimer;

	bool alive;
	bool canSpawn;
	bool isShooting;

	int spawnTimer;

	int respawnTimer;
};

