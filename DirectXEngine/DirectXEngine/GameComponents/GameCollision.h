#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "../GameObjects/Entity.h"

class GameCollision
{
public:
    
    GameCollision();

	//Rect and Rect
    static Entity::CollisionReturn isCollideBetweenRectAndRect(RECT rect1, RECT rect2);

    static bool isCollide(RECT rect1, RECT rect2);

    static Entity::SideCollisions GetSideCollision(Entity *e1, Entity *e2);

	// Entity and Entity
    static Entity::SideCollisions GetSideCollision(Entity *e1, Entity::CollisionReturn data);

	// Point and Rect
    static bool PointAndRectangle(float x, float y, RECT rect);

    //Rect and Circle
    static bool RectangleAndCircle(RECT rect, int circleX, int circleY, int circleRadius);
    ~GameCollision();
};