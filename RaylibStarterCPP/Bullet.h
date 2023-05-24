#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	void Update();
	void Draw();

	void BulletInit(GameObject player, Vector2 shipTop);

	bool isShooting;

private:		
	double bulletAngleX;
	double bulletAngleY;

	float lifeTimer;

};

