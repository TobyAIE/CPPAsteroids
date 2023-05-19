#include "Game.h"
#include<raymath.h>
#include "raylib.h"
#include "GameObject.h"
#include <iostream>

GameObject player;
//GameObject asteroid;

void Game::Menu()
{
	startGame = false;

	while (!startGame)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		frameTimer++;		

		if ((frameTimer/2) % 20)
		{
			DrawText("METEORITES", 200, 300, 60, WHITE);

			DrawText("PRESS ENTER", 300, 500, 30, WHITE);
		}
		else
		{
			DrawText("METEORITES", 200, 300, 60, BLACK);

			DrawText("PRESS ENTER", 300, 500, 30, BLACK);
		}

		if (IsKeyPressed(KEY_ENTER)) startGame = true;

		EndDrawing();
	}	
}

void Game::Init()
{	
	player.position.x = 400;
	player.position.y = 400;
	player.rotation = -90;
	player.playerHeight = 20.0f;
	player.shipThrust = 0.0f;

	asteroidCount = 8;

	asteroids = new GameObject[asteroidCount];

	for (size_t i = 0; i < asteroidCount; i++)
	{
		GameObject asteroid;

		asteroid.position.x = rand() % 800;
		asteroid.position.y = rand() % 800;
		asteroid.rotation = rand() % 360;

		asteroids[i] = asteroid;

	}

}

void Game::Update()
{

	for (size_t i = 0; i < asteroidCount; i++)
	{
		asteroids[i].position.x += cos(asteroids[i].rotation * DEG2RAD) * 1.5f;
		asteroids[i].position.y += sin(asteroids[i].rotation * DEG2RAD) * 1.5f;
	}

	if (IsKeyDown(KEY_W))
	{
		player.shipThrust += 0.04f;
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
		player.rotation -= 2.0f;
	}

	if (IsKeyDown(KEY_D))
	{
		player.rotation += 2.0f;
	}

	//The code here constantly updates the players movement depending on how much thrust the ship has.
	//Allows for Asteroids momentum movement.
	player.position.x += cos(player.rotation * DEG2RAD) * player.shipThrust;
	player.position.y += sin(player.rotation * DEG2RAD) * player.shipThrust;

	//This code does asteroids looping feature
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

	DrawTriangleLines(v1, v2, v3, WHITE);

	for (size_t i = 0; i < asteroidCount; i++)
	{
		DrawCircleLines(asteroids[i].position.x, asteroids[i].position.y, 40, WHITE);
	}
	

	DrawText("Thrust: ", 10, 10, 20, WHITE);
	DrawText(to_string(player.shipThrust).c_str(), 110, 10, 20, WHITE);
}