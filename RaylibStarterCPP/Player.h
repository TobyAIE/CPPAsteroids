#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player();
	~Player();

	float shipThrust;
	float playerHeight;

	void PlayerSpawn();

	void Update();

private:

};

