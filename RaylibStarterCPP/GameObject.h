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
	float playerHeight;
	

private:	


public:
	void Load(const char* filename);

};

