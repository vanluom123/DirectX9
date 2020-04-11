#include "GameCollision.h"
#include <iostream>
using namespace std;

GameCollision * GameCollision::s_instance = nullptr;


void GameCollision::release()
{
	delete s_instance;
	s_instance = nullptr;
}

GameCollision * GameCollision::getInstance()
{
	if (!s_instance) s_instance = new GameCollision;
	return s_instance;
}

bool GameCollision::pointCollision(float nPositionX, float nPositionY, const RECT & box)
{
	return (nPositionX >= box.left &&
			nPositionY <= box.bottom &&
			nPositionX <= box.right &&
			nPositionY >= box.top);
}

bool GameCollision::circleCollision(RECT bound, int nCircleX, int nCircleY, int nCircleRadius)
{
	int nPx = nCircleX;
	int nPy = nCircleY;

	if (nPx < bound.left)
		nPx = bound.left;
	else if (nPx > bound.right)
		nPx = bound.right;

	if (nPy > bound.bottom)
		nPy = bound.bottom;
	else if (nPy < bound.top)
		nPy = bound.top;

	const int nDistX = nPx - nCircleX;
	const int nDistY = nPy - nCircleY;

	return (nDistX * nDistX + nDistY * nDistY) <= nCircleRadius * nCircleRadius;
}

GVec2 GameCollision::Distance(BaseObject * e1, BaseObject * e2, float dt)
{
	GVec2 distance;
	distance.x = (e1->getVx() - e2->getVx()) * dt;
	distance.y = (e1->getVy() - e2->getVy()) * dt;
	return distance;
}

RECT GameCollision::getBroadphase(RECT object, GVec2 distance)
{
	RECT broad = object;

	if (distance.x < 0)
		broad.left = object.left + distance.x;
	else if (distance.x > 0)
		broad.right = object.right + distance.x;

	if (distance.y > 0)
		broad.bottom = object.bottom + distance.y;
	else if (distance.y < 0)
		broad.top = object.top + distance.y;

	return broad;
}

float GameCollision::sweptAABB(RECT obj, RECT other, GVec2 distance, Side_Collision & sideCollision)
{
	float dxEntry, dxExit;
	float dyEntry, dyExit;

	if (distance.x > 0.0f)
	{
		dxEntry = other.left - obj.right;
		dxExit = other.right - obj.left;
	}
	else
	{
		dxEntry = other.right - obj.left;
		dxExit = other.left - obj.right;
	}

	if (distance.y > 0.0f)
	{
		dyEntry = other.top - obj.bottom;
		dyExit = other.bottom - obj.top;
	}
	else
	{
		dyEntry = other.bottom - obj.top;
		dyExit = other.top - obj.bottom;
	}

	float txEntry, txExit;
	float tyEntry, tyExit;

	if (distance.x == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / distance.x;
		txExit = dxExit / distance.x;
	}

	if (distance.y == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / distance.y;
		tyExit = dyExit / distance.y;
	}

	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
	{
		sideCollision = Side_Collision::NONE;
		return 1.0f;
	}

	if (txEntry < tyEntry)
	{
		if (dyEntry < 0.0f)
			sideCollision = Side_Collision::TOP;
		else
			sideCollision = Side_Collision::BOTTOM;
	}
	else
	{
		if (dxEntry < 0.0f)
			sideCollision = Side_Collision::LEFT;
		else
			sideCollision = Side_Collision::RIGHT;
	}

	return entryTime;
}

bool GameCollision::AABBCheck(RECT object, RECT other)
{
	return !(object.right < other.left ||
			 object.left > other.right ||
			 object.bottom < other.top ||
			 object.top > other.bottom);
}

bool GameCollision::isNested(RECT object, RECT other)
{
	return !(object.right <= other.left ||
			 object.left >= other.right ||
			 object.bottom <= other.top ||
			 object.top >= other.bottom);
}
