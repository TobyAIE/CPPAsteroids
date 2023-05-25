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

private:	


public:

	GameObject();
	~GameObject();

	void Load(const char* filename);

};

