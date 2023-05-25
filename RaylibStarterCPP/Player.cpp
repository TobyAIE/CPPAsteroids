#include "Player.h"
Player::Player()
{

}
Player::~Player()
{

}

void Player::PlayerSpawn()
{
	position.x = 400;
	position.y = 400;
	rotation = -90;
}

void Player::Update()
{
	if (IsKeyDown(KEY_W) && shipThrust < 40.0f)
	{
		shipThrust += 0.06f;
	}
	else
	{
		if (shipThrust <= 0)
		{
			shipThrust = 0;
		}
		else
		{
			shipThrust -= 0.03;
		}
	}

	if (IsKeyDown(KEY_A))
	{
		rotation -= 3.0f;
	}

	if (IsKeyDown(KEY_D))
	{
		rotation += 3.0f;
	}
}