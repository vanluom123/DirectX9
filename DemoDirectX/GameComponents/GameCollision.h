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

	//Check collision Rectangle and Rectangle
	BaseObject::CollisionReturn rectCollision(const RECT& box1, const RECT& box2);

	bool AABBCheck(const RECT& box1, const RECT& box2);

	bool isCollide(const RECT& box1, const RECT& box2);

	void bounce(GVec2& collisionVector, BaseObject& obj, BaseObject& other);

	bool collideBox(GVec2& collisionVector, const RECT& box1, const RECT& box2);

	//if Rectangle is big, it will be error
	Side_Collision getSideCollision(BaseObject* e1, BaseObject* e2);

	//Side of collision of Entity
	Side_Collision getSideCollision(BaseObject* e1, BaseObject::CollisionReturn data);

	//Check collision between Point and Rectangle
	bool pointCollision(float x, float y, const RECT& box);

	//Check collision between Rectangle and Circle
	bool circleCollision(const RECT& bound, int circle_x, int circle_y, int circleRadius);

	GVec2 Distance(BaseObject* e1, BaseObject* e2, float dt);

	RECT getBroadphase(const RECT& object, const GVec2& distance);

	//Axis-Aligned Bounding box collision
	float sweptAABB(const RECT& obj, const RECT& other, const GVec2& distance, Side_Collision& sideCollision);

private:
	GameCollision() = default;
	static GameCollision* s_instance;
};