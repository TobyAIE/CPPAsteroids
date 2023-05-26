#include "Game.h"
#include<raymath.h>
#include "raylib.h"
#include <iostream>

Player player;

GameObject spawnCheck;

//-------------------------------------------------------------------------------
//Creates a menu screen with blinking text
//-------------------------------------------------------------------------------
void Game::Menu()
{
	startGame = false;
	while (!startGame)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		frameTimer++;		

		if ((frameTimer/20) % 2 == 0)
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
//-------------------------------------------------------------------------------



//-------------------------------------------------------------------------------
// Destroys arrays
//-------------------------------------------------------------------------------
void Game::DeInit()
{
	delete[] asteroids;
	delete[] bullets;
}
//-------------------------------------------------------------------------------



//-------------------------------------------------------------------------------
//Initialies the game and all objects in game
//-------------------------------------------------------------------------------
void Game::Init()
{
	alive = true;
	isShooting = false;
	lives = 3;
	spawnCheck.position.x = 400;
	spawnCheck.position.y = 400;
	player.PlayerSpawn();
	player.playerHeight = 20.0f;
	player.shipThrust = 0.0f;
	score = 0;
	spawnTimer = 0;
	respawnTimer = 0;
	canSpawn = true;

	maxAsteroids = 56;

	asteroidCount = 8;
	bulletCount = 16;

	asteroids = new Asteroid[maxAsteroids];
	bullets = new Bullet[bulletCount];

	for (size_t i = 0; i < maxAsteroids; i++)
	{
		asteroids[i].destroyed = true;
	}

	for (size_t i = 0; i < asteroidCount; i++)
	{
		asteroids[i].SpawnAsteroid(1);
	}

	for (size_t i = 0; i < bulletCount; i++)
	{
		Bullet bullet;

		bullets[i].isShooting = false;
	}

}
//-------------------------------------------------------------------------------

void Game::Update()
{
	//-------------------------------------------------------------------------------
	//This will spawn in a new big asteroid once enough small ones have been destroyed
	//-------------------------------------------------------------------------------
	if (spawnTimer >= 4)
	{
		for (size_t i = 0; i < maxAsteroids; i++)
		{
			if (asteroids[i].destroyed)
			{
				asteroids[i].SpawnAsteroid(1);
				spawnTimer = 0;
				std::cout << "Spawn new asteroid" << std::endl;
				break;
			}
		}
	}
	//-------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------
	//Updates all active asteroids
	//-------------------------------------------------------------------------------
	for (size_t i = 0; i < maxAsteroids; i++)
	{
		asteroids[i].Update();
	}
	//-------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------
	//Updates the player if they are alives
	//-------------------------------------------------------------------------------
	if (alive)
	{
		player.Update();
	}
	//-------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------
	//If the player is alive, when they press the space bar the ship will shoot
	//-------------------------------------------------------------------------------
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
	//-------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------
	//Updates all active bullets
	//-------------------------------------------------------------------------------
	for (size_t i = 0; i < bulletCount; i++)
	{
		if (bullets[i].isShooting == true)
		{
			//std::cout << "bullet " << i << " is moving" << std::endl;
			bullets[i].Update();
		}
	}
	//-------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------
	//The code here constantly updates the players movement depending on how much thrust the ship has.
	//Allows for Asteroids momentum movement.
	//-------------------------------------------------------------------------------
	player.position.x += cos(player.rotation * DEG2RAD) * player.shipThrust;
	player.position.y += sin(player.rotation * DEG2RAD) * player.shipThrust;
	//-------------------------------------------------------------------------------



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

	for (size_t i = 0; i < maxAsteroids; i++)
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
	for (size_t i = 0; i < maxAsteroids; i++)
	{
		if (!asteroids[i].destroyed && alive)
		{
			if (CheckCollisionCircles(player.position, 10, asteroids[i].position, asteroids[i].size))
			{
				alive = false;
				lives--;
				//canSpawn = false;
			}
			//else 
			//{
			//	canSpawn = true;
			//}
		}
	}
	//-------------------------------------------------------------------------------

	

	//-------------------------------------------------------------------------------
	//Collistion between asteroid and spawn checker
	//-------------------------------------------------------------------------------
	for (size_t i = 0; i < maxAsteroids; i++)
	{
		if (!asteroids[i].destroyed)
		{
			if (CheckCollisionCircles(spawnCheck.position, 65, asteroids[i].position, asteroids[i].size))
			{
				//std::cout << "Asteroid too close!!" << std::endl;
				canSpawn = false;
				break;
			}
			else if (!CheckCollisionCircles(spawnCheck.position, 65, asteroids[i].position, asteroids[i].size))
			{
				//std::cout << "Safe to Spawn" << std::endl;
				canSpawn = true;
			}
		}
	}
	//-------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------
	//Respawn player if they are dead
	//-------------------------------------------------------------------------------
	if (!alive)
	{
		PlayerRespawn();
	}
	//-------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------
	//Collistion between asteroid and bullet
	//-------------------------------------------------------------------------------
	for (size_t i = 0; i < maxAsteroids; i++)
	{
		for (size_t j = 0; j < bulletCount; j++)
		{
			if (!asteroids[i].destroyed && bullets[j].isShooting)
			{
				if (CheckCollisionCircles(bullets[j].position, 2, asteroids[i].position, asteroids[i].size))
				{
					bullets[j].isShooting = false;

					for (size_t l = 0; l < 2; l++)
					{

						for (size_t k = 0; k < maxAsteroids; k++)
						{
							if (asteroids[k].destroyed && asteroids[i].asteroidLevel < 3)
							{
								asteroids[k].SpawnAsteroid(asteroids[i].asteroidLevel + 1);
								asteroids[k].position.x = asteroids[i].position.x;
								asteroids[k].position.y = asteroids[i].position.y;
								break;
							}
						}
					}

					if (asteroids[i].asteroidLevel == 3)
					{
						spawnTimer++;
					}

					asteroids[i].destroyed = true;

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
	}
	//-------------------------------------------------------------------------------

}

void Game::Draw()
{
	//-------------------------------------------------------------------------------
	//Sets the verticies of the triangle based of players position and rotation
	//-------------------------------------------------------------------------------
	float angle = player.rotation * DEG2RAD;
	angle += (PI / 2);
	Vector2 v1 = { player.position.x + sinf(angle) * (player.playerHeight), player.position.y - cosf(angle) * (player.playerHeight) };
	Vector2 v2 = { player.position.x - cosf(angle) * (player.playerHeight / 2), player.position.y - sinf(angle) * (player.playerHeight / 2) };
	Vector2 v3 = { player.position.x + cosf(angle) * (player.playerHeight / 2), player.position.y + sinf(angle) * (player.playerHeight / 2) };
	//-------------------------------------------------------------------------------

	ClearBackground(BLACK);

	//-------------------------------------------------------------------------------
	// Draws a circle showing the spawn area. For Debugging.
	//-------------------------------------------------------------------------------
	//DrawCircleLines(spawnCheck.position.x, spawnCheck.position.y, 65, DARKGRAY);
	//-------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------
	//Displays the players avaliable lives as ships in the top left corner
	//-------------------------------------------------------------------------------
	int livesOffset = 0;
	
	for (int i = 0; i < lives; i++)
	{
		Vector2 vl1 = { 30 + livesOffset, 50 };
		Vector2 vl2 = { 20 + livesOffset, 80 };
		Vector2 vl3 = { 40 + livesOffset, 80 };
	
		DrawTriangleLines(vl1, vl2, vl3, WHITE);
		livesOffset += 25;
	}
	//-------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------
	//This will check the state of the player and draw.
	// - if the player has died and has no lives left: "You Died..." will be displayed
	// instead of the player
	// 
	// - if the player is alive: draws the player
	// 
	// - any other conditions: Draws nothing
	//-------------------------------------------------------------------------------
	if (!alive && lives < 0)
	{
		DrawText("You Died...", 325, 400, 30, WHITE);
		frameTimer++;
	}
	else if (alive)
	{
		DrawTriangleLines(v1, v2, v3, WHITE);
	}
	else
	{
	}
	//-------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------
	//This function goes through every active asteroid and draws them using the
	// asteroid's 'Draw' function.
	//-------------------------------------------------------------------------------
	for (size_t i = 0; i < maxAsteroids; i++)
	{
		if (!asteroids[i].destroyed)
		{
			asteroids[i].Draw();
			//std::cout << "Drawing asteroid " << i << std::endl;
		}
	}
	//-------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------
	//This function goes through every active bullet and draws them using the
	// bullet's 'Draw' function.
	//-------------------------------------------------------------------------------
	for (size_t i = 0; i < bulletCount; i++)
	{
		if (bullets[i].isShooting == true)
		{
			//std::cout << "bullet " << i << " is drawing" << std::endl;
			bullets[i].Draw();
		}
	}
	//-------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------
	//When the game is running this displays the players current score in the top
	// left corner.
	//-------------------------------------------------------------------------------
	if (lives > -1)
	{
		DrawText(to_string(score).c_str(), 10, 10, 40, WHITE);
	}	
	//-------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------
	//Debug text to check different variables
	// Variables: lives, shipThrust, spawnTimer, canSpawn, alive
	//-------------------------------------------------------------------------------
	//DrawText("Lives: ", 10, 30, 20, WHITE);
	//DrawText(to_string(lives).c_str(), 80, 30, 20, WHITE);
	//
	//DrawText("Thrust: ", 600, 10, 20, WHITE);
	//DrawText(to_string(player.shipThrust).c_str(), 700, 10, 20, WHITE);
	//
	//DrawText("Spawn Timer: ", 570, 30, 20, WHITE);
	//DrawText(to_string(spawnTimer).c_str(), 750, 30, 20, WHITE);
	//
	//DrawText("Can Spawn: ", 600, 10, 20, WHITE);
	//DrawText(to_string(canSpawn).c_str(), 750, 10, 20, WHITE);
	//
	//DrawText("Alive: ", 600, 30, 20, WHITE);
	//DrawText(to_string(alive).c_str(), 750, 30, 20, WHITE);
	//-------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------
	//When you lose all your lives the fianl score is displayed in blinking text
	//-------------------------------------------------------------------------------
	if (!alive && lives < 0)
	{
		if ((frameTimer/20) % 2 == 0)
		{
			DrawText("FINAL SCORE: ", 200, 500, 30, WHITE);

			DrawText(to_string(score).c_str(), 435, 500, 30, WHITE);
		}
		else
		{
			ClearBackground(BLACK);
		}
	}
	//-------------------------------------------------------------------------------
}


//-------------------------------------------------------------------------------
//PlayerRespawn: Checks if the player can respawn and if yes, respawns the player
//-------------------------------------------------------------------------------
void Game::PlayerRespawn()
{
	if (lives >= 0 && canSpawn)
	{
		alive = true;
		player.PlayerSpawn();
		player.shipThrust = 0;
	}
}
//-------------------------------------------------------------------------------
