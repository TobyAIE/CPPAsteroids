#include "GameObject.h"
#include "raylib.h"
#include <raymath.h>

using namespace std;

GameObject::GameObject()
{

}
GameObject::~GameObject()
{

}

void GameObject::Load(const char* filename)
{
	//objectSprite = LoadImage(filename);
	//objectTexture = LoadTextureFromImage(objectSprite);
}

//GameObject::SpawnAsteroid()
//{
//	//Asteroid* a = new Asteroid();
//	//
//	//a->asteroidPos.x = rand() % 800;
//	//a->asteroidPos.y = rand() % 800;
//	//a->asteroidRot = rand() % 360;
//	//
//	//a->asteroidSize = 40;
//	//
//	//a->asteroidPos.x += cos(a->asteroidRot * DEG2RAD) * 1.5f;
//	//a->asteroidPos.y += cos(a->asteroidRot * DEG2RAD) * 1.5f;
//	
//	return a;
//}