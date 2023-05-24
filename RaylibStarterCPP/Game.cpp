#include "Game.h"
#include<raymath.h>
#include "raylib.h"
#include <iostream>

Player player;
GameObject playerSpawner;

void Game::Menu()
{
	startGame = false;

	while (!startGame)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		frameTimer++;		

		if ((frameTimer/2) % 30)
		{
			DrawText("METEORITES", 200, 300, 60, WHITE);

			DrawText("PRESS ENTER", 300, 500, 30, WHITE);
		}
		else
		{
			ClearBackground(BLACK);
		}

		if (IsKeyPressed(KEY_ENTER)) startGame = true;

		EndDrawing();
	}	
}

void Game::DeInit()
{
	delete[] asteroids;
	delete[] bullets;
}

void Game::Init()
{	
	alive = true;
	isShooting = false;
	lives = 3;
	player.position.x = 400;
	player.position.y = 400;
	player.rotation = -90;
	player.playerHeight = 20.0f;
	player.shipThrust = 0.0f;
	score = 0;

	asteroidCount = 8;
	bulletCount = 16;

	asteroids = new Asteroid[asteroidCount];
	bullets = new Bullet[bulletCount];

	for (size_t i = 0; i < asteroidCount; i++)
	{
		Asteroid asteroid;

		asteroid.position.x = -40;		
		asteroid.position.y = rand() % 800;
		asteroid.rotation = rand() % 360;
		asteroid.destroyed = false;
		asteroid.asteroidLevel = 1;

		asteroids[i] = asteroid;
	}

	for (size_t i = 0; i < bulletCount; i++)
	{
		Bullet bullet;

		bullets[i].isShooting = false;
	}

}

void Game::Update()
{

	for (size_t i = 0; i < asteroidCount; i++)
	{
		asteroids[i].Update();
	}

	if (IsKeyDown(KEY_W) && player.shipThrust < 40.0f)
	{
		player.shipThrust += 0.06f;
	}
	else
	{
		if (player.shipThrust <= 0)
		{
			player.shipThrust = 0;
		}
		else
		{
			player.shipThrust -= 0.03;
		}
	}

	if (IsKeyDown(KEY_A))
	{
		player.rotation -= 3.0f;
	}

	if (IsKeyDown(KEY_D))
	{
		player.rotation += 3.0f;
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		//BulletShoot();
		if (alive)
		{
			for (size_t i = 0; i < bulletCount; i++)
			{
				if (bullets[i].isShooting == false)
				{

					float angle = player.rotation * DEG2RAD;
					angle += (PI / 2);
					Vector2 v1 = { player.position.x + sinf(angle) * (player.playerHeight), player.position.y - cosf(angle) * (player.playerHeight) };

					std::cout << "FIRE!!" << std::endl;
					bullets[i].isShooting = true;
					bullets[i].BulletInit(player, v1);
					break;
				}
			}
		}
	}

	for (size_t i = 0; i < bulletCount; i++)
	{
		if (bullets[i].isShooting == true) 
		{
			//std::cout << "bullet " << i << " is moving" << std::endl;
			bullets[i].Update();			
		}
	}

	//The code here constantly updates the players movement depending on how much thrust the ship has.
	//Allows for Asteroids momentum movement.
	player.position.x += cos(player.rotation * DEG2RAD) * player.shipThrust;
	player.position.y += sin(player.rotation * DEG2RAD) * player.shipThrust;



	//-------------------------------------------------------------------------------
	//This code does asteroids looping feature
	//-------------------------------------------------------------------------------
	if (player.position.x >= 825)
	{
		player.position.x = -20;
	}
	else if (player.position.x <= -25)
	{
		player.position.x = 820;
	}

	if (player.position.y >= 825)
	{
		player.position.y = -20;
	}
	else if (player.position.y <= -25)
	{
		player.position.y = 820;
	}

	for (size_t i = 0; i < asteroidCount; i++)
	{
		if (asteroids[i].position.x >= 845)
		{
			asteroids[i].position.x = -40;
		}
		else if (asteroids[i].position.x <= -45)
		{
			asteroids[i].position.x = 840;
		}

		if (asteroids[i].position.y >= 845)
		{
			asteroids[i].position.y = -40;
		}
		else if (asteroids[i].position.y <= -45)
		{
			asteroids[i].position.y = 840;
		}
	}

	for (size_t i = 0; i < bulletCount; i++)
	{
		if (bullets[i].position.x >= 845)
		{
			bullets[i].position.x = -40;
		}
		else if (bullets[i].position.x <= -45)
		{
			bullets[i].position.x = 840;
		}

		if (bullets[i].position.y >= 845)
		{
			bullets[i].position.y = -40;
		}
		else if (bullets[i].position.y <= -45)
		{
			bullets[i].position.y = 840;
		}
	}
	//-------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------
	//Collistion between asteroid and player
	//-------------------------------------------------------------------------------
	for (size_t i = 0; i < asteroidCount; i++)
	{
		if (CheckCollisionCircles(player.position, 10, asteroids[i].position, 40))
		{
			alive = false;
		}
	}
	//-------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------
	//Collistion between asteroid and bullet
	//-------------------------------------------------------------------------------
	for (size_t i = 0; i < asteroidCount; i++)
	{
		for (size_t j = 0; j < bulletCount; j++)
		{
			if (CheckCollisionCircles(bullets[j].position, 2, asteroids[i].position, 40))
			{
				asteroids[i].destroyed = true;
				bullets[j].isShooting = false;

				switch (asteroids[i].asteroidLevel)
				{
				case 1:
					score += 100;
					break;
				case 2:
					score += 150;
					break;
				case 3:
					score += 250;
					break;
				default:
					break;
				}
			}
		}		
	}
	//-------------------------------------------------------------------------------

}

void Game::Draw()
{
	//player.Load("..\\Sprites\\Ship.png");

	float angle = player.rotation * DEG2RAD;
	angle += (PI/2);
	Vector2 v1 = {player.position.x + sinf(angle) * (player.playerHeight), player.position.y - cosf(angle) * (player.playerHeight)};
	Vector2 v2 = {player.position.x - cosf(angle) * (player.playerHeight/2), player.position.y - sinf(angle) * (player.playerHeight/2)};
	Vector2 v3 = {player.position.x + cosf(angle) * (player.playerHeight/2), player.position.y + sinf(angle) * (player.playerHeight/2)};

	ClearBackground(BLACK);

	//DrawTexture(player.objectTexture, 400, 225, WHITE);

	//int livesOffset = 0;
	//
	//for (size_t i = 0; i < lives; i++)
	//{
	//	Vector2 vl1 = { livesOffset += livesOffset/2, 50 };
	//	Vector2 vl2 = { livesOffset, 80 };
	//	Vector2 vl3 = { livesOffset += 10, 80 };
	//
	//	DrawTriangleLines(vl1, vl2, vl3, WHITE);
	//	livesOffset += 40;
	//}

	if (!alive)
	{
		DrawText("You Died...", 325, 400, 30, WHITE);
	}
	else
	{
		DrawTriangleLines(v1, v2, v3, WHITE);
	}	

	for (size_t i = 0; i < asteroidCount; i++)
	{
		if (!asteroids[i].destroyed)
		{
			DrawCircleLines(asteroids[i].position.x, asteroids[i].position.y, 40, WHITE);
		}		
	}
	
	for (size_t i = 0; i < bulletCount; i++)
	{
		if (bullets[i].isShooting == true)
		{
			std::cout << "bullet " << i << " is drawing" << std::endl;
			bullets[i].Draw();
		}
	}

	DrawText(to_string(score).c_str(), 10, 10, 20, WHITE);

	DrawText("Thrust: ", 600, 10, 20, WHITE);
	DrawText(to_string(player.shipThrust).c_str(), 700, 10, 20, WHITE);
}