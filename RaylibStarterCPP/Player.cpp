#include "Player.h"
Player::Player()
{

}
Player::~Player()
{

}

//-------------------------------------------------------------------------------
//Moves the player to the middle of the screen and sets the rotation to be facing
// the top of the screen.
//-------------------------------------------------------------------------------
void Player::PlayerSpawn()
{
	position.x = 400;
	position.y = 400;
	rotation = -90;
}
//-------------------------------------------------------------------------------



//-------------------------------------------------------------------------------
//Checks if the player is pressing the "w", "a", or "d" keys and updates the player
// variables accordingly
//-------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------