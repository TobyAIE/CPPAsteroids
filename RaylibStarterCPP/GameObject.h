#pragma once

#include <string>
#include "raylib.h"

using namespace std;

class GameObject
{
public:
	Image objectSprite;
	Texture2D objectTexture;
	Vector2 position;
	float rotation;	
	
	struct Asteroid
	{
		Vector2 asteroidPos;
		float asteroidRot;
		float asteroidSize;
	};

private:	


public:

	GameObject();
	~GameObject();

	void Load(const char* filename);

	//GameObject SpawnAsteroid();

};

