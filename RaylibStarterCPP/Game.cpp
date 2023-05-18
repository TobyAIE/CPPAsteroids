#include "Game.h"
#include<raymath.h>
#include "raylib.h"
#include "GameObject.h"

GameObject player;

void Game::Init()
{	
	player.position.x = 400;
	player.position.y = 225;
	player.playerHeight = 20.0f;
}

void Game::Update()
{
	
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