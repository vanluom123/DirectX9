#ifndef _GAME_COLLISION_H
#define _GAME_COLLISION_H
#include "Entity.h"

#define ValueMax(a, b) ((a + b + abs(a - b))/2)

class GameCollision
{
public:
	GameCollision();
	~GameCollision();

	// Checking collision between two Rectangle
	static Entity::CollisionReturn RectAndRect(RECT rect1, RECT rect2);

	static bool isCollision(RECT rect1, RECT rect2);

	static Entity::SideCollision GetSideCollision(Entity* e1, Entity* e2);

	static Entity::SideCollision GetSideCollision(Entity* e1, Entity::CollisionReturn data);

	// Checking a point that has a collision Rectangle
	static bool PointAndRect(float x, float y, RECT rect);

	// Rect and Circle
	static bool RectAndCircle(RECT rect, int circleX, int circleY, int circleRadius);
};

#endif
