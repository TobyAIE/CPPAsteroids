#include "Game.h"
#include<raymath.h>
#include "raylib.h"
#include "GameObject.h"
#include <iostream>

GameObject player;

//Stopwatch stopwatch = new Stopwatch();
//
//long currentTime = 0;
//long lastTime = 0;

float deltatime = 0.005f;

void Game::Init()
{	
	player.position.x = 400;
	player.position.y = 225;
	player.playerHeight = 20.0f;
}

void Game::Update()
{
	//lastTime = currentTime;
	//currentTime = stopwatch.ElapsedMilliseconds;
	//deltaTime = (currentTime - lastTime) / 1000.0f;
	
	if (IsKeyDown(KEY_W))
	{
		;
	}

	if (IsKeyDown(KEY_A))
	{
		player.rotation -= 1;
	}

	if (IsKeyDown(KEY_D))
	{
		player.rotation += 1;
	}

}

void Game::Draw()
{

	//player.Load("..\\Sprites\\Ship.png");

	Vector2 v1 = {player.position.x + sinf(player.rotation * DEG2RAD) * (player.playerHeight), player.position.y - cosf(player.rotation * DEG2RAD) * (player.playerHeight)};
	Vector2 v2 = {player.position.x - cosf(player.rotation * DEG2RAD) * (player.playerHeight/2), player.position.y - sinf(player.rotation * DEG2RAD) * (player.playerHeight/2)};
	Vector2 v3 = {player.position.x + cosf(player.rotation * DEG2RAD) * (player.playerHeight/2), player.position.y - sinf(player.rotation * DEG2RAD) * (player.playerHeight/2)};

	ClearBackground(BLACK);

	//DrawTexture(player.objectTexture, 400, 225, WHITE);

	DrawTriangleLines(v1, v2, v3, WHITE);

	//DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

	//EndDrawing();
}