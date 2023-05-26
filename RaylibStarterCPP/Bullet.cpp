#include "Bullet.h"
Bullet::Bullet()
{

}
Bullet::~Bullet()
{

}



//-------------------------------------------------------------------------------
//Updates the position of the bullet
//-------------------------------------------------------------------------------
void Bullet::Update()
{
	float dt = GetFrameTime();
	lifeTimer += 0.05f;

	if (lifeTimer > 9.0f)
	{
		isShooting = false;
	}	
	position.x += bulletAngleX * 500 * dt;
	position.y += bulletAngleY * 500 * dt;

	if (!isShooting)
	{
		position.x = -400;
		position.y = -400;
	}
}
//-------------------------------------------------------------------------------



//-------------------------------------------------------------------------------
//Draws the bullet based on its position
//-------------------------------------------------------------------------------
void Bullet::Draw()
{
	DrawCircle(position.x, position.y, 2, WHITE);
}
//-------------------------------------------------------------------------------



//-------------------------------------------------------------------------------
//Initialises a bullet by setting the position of it to be at the top of the players
// ship and sets the rotation to the players current rotation
//-------------------------------------------------------------------------------
void Bullet::BulletInit(GameObject player, Vector2 shipTop)
{
	bulletAngleX = cos(player.rotation * DEG2RAD);
	bulletAngleY = sin(player.rotation * DEG2RAD);

	position = shipTop;

	lifeTimer = 0;
}
//-------------------------------------------------------------------------------