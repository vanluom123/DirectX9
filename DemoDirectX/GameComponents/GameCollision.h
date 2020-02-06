#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "../GameObjects/Entity/BaseObject.h"


class GameCollision
{
public:
	~GameCollision() = default;
	static void release();
	static GameCollision* getInstance();

	// Axis-Aligned Bounding Box
	bool AABBCheck(RECT object, RECT other);
	bool isNested(RECT object, RECT other);

	//Check collision between Point and Rectangle
	bool pointCollision(float x, float y, const RECT& box);

	//Check collision between Rectangle and Circle
	bool circleCollision(RECT bound, int circle_x, int circle_y, int circleRadius);

	GVec2 Distance(BaseObject* e1, BaseObject* e2, float dt);

	RECT getBroadphase(RECT object, GVec2 distance);

	//Axis-Aligned Bounding box collision
	float sweptAABB(RECT obj, RECT other, GVec2 distance, Side_Collision& sideCollision);

private:
	GameCollision() = default;
	static GameCollision* s_instance;
};