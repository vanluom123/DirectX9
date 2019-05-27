﻿#include "GameCollision.h"
#include <iostream>
using namespace std;


BaseObject::CollisionReturn GameCollision::rectCollision(RECT rect1, RECT rect2)
{
	BaseObject::CollisionReturn result = BaseObject::CollisionReturn();

	if (!IsCollision(rect1, rect2))
	{
		result.isCollision = false;
		return result;
	}

	result.isCollision = true;

	result.regionCollision.left = max(rect1.left, rect2.left);
	result.regionCollision.right = max(rect1.right, rect2.right);
	result.regionCollision.bottom = max(rect1.bottom, rect2.bottom);
	result.regionCollision.top = max(rect1.top, rect2.top);

	return result;
}

bool GameCollision::pointCollision(float x, float y, RECT rect)
{
	return !(x < rect.left || x > rect.right || y < rect.top || y > rect.bottom);
}

bool GameCollision::circleCollision(RECT rect, int circle_x, int circle_y, int circleRadius)
{
	int px = circle_x;
	int py = circle_y;

	if (px < rect.left)
		px = rect.left;
	else if (px > rect.right)
		px = rect.right;

	if (py > rect.bottom)
		py = rect.bottom;
	else if (py < rect.top)
		py = rect.top;

	const int dx = px - circle_x;
	const int dy = py - circle_y;

	return (dx * dx + dy * dy) <= circleRadius * circleRadius;
}

bool GameCollision::intersectRect(RECT obj, RECT other)
{
	return !(obj.left >= other.right || obj.right <= other.left || obj.top >= other.bottom || obj.bottom <= other.top);
}

GVec2 GameCollision::Distance(BaseObject* e1, BaseObject* e2, float dt)
{
	GVec2 distance;
	distance.x = (e1->GetVx() - e2->GetVx()) * dt;
	distance.y = (e1->GetVy() - e2->GetVy()) * dt;
	return distance;
}

RECT GameCollision::getBroad(RECT object, GVec2 distance)
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

float GameCollision::SweptAABB(RECT obj, RECT other, GVec2 distance, BaseObject::eSideCollision& sideCollision)
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
		txEntry = dxEntry / (distance.x);
		txExit = dxExit / (distance.x);
	}

	if (distance.y == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / (distance.y);
		tyExit = dyExit / (distance.y);
	}

	const float entryTime = max(txEntry, tyEntry);
	const float exitTime = min(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
	{
		sideCollision = BaseObject::NONE;
		return 1.0f;
	}

	if (txEntry < tyEntry)
	{
		if (dyEntry < 0.0f)
		{
			sideCollision = BaseObject::TOP;
		}
		else
		{
			sideCollision = BaseObject::BOTTOM;
		}
	}
	else
	{
		if (dxEntry < 0.0f)
		{
			sideCollision = BaseObject::LEFT;
		}
		else
		{
			sideCollision = BaseObject::RIGHT;
		}
	}

	return entryTime;
}

bool GameCollision::IsCollision(RECT rect1, RECT rect2)
{
	return !(rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top);
}

BaseObject::eSideCollision GameCollision::getSideCollision(BaseObject* e1, BaseObject* e2)
{
	RECT rect1 = e1->GetBound();
	RECT rect2 = e2->GetBound();
	const float w = (e1->GetWidth() + e2->GetWidth()) / 2.0f;
	const float h = (e1->GetHeight() + e2->GetHeight()) / 2.0f;

	const float dx = e1->GetPosition().x - e2->GetPosition().y;
	const float dy = e1->GetPosition().x - e2->GetPosition().y;

	if (abs(int(dx)) <= w && abs(int(dy)) <= h)
	{
		// Has a collision
		const float wy = w * dy;
		const float hx = h * dx;

		if (wy > hx)
		{
			if (wy > -hx)
			{
				//Collision Top e1
				return BaseObject::TOP;
			}
			//Collision Right e1
			return BaseObject::RIGHT;
		}
		if (wy > -hx)
		{
			//Collision Left e1
			return BaseObject::LEFT;
		}

		//Collision Bottom e1
		return BaseObject::BOTTOM;
	}
	//Don't collide
	return BaseObject::NONE;
}

BaseObject::eSideCollision GameCollision::getSideCollision(BaseObject* e1, BaseObject::CollisionReturn data)
{
	const float xCenter = data.regionCollision.left + (data.regionCollision.right - data.regionCollision.left) / 2.0f;
	const float yCenter = data.regionCollision.top + (data.regionCollision.bottom - data.regionCollision.top) / 2.0f;

	const GVec2 cCenter = GVec2(xCenter, yCenter);
	GVec2 eCenter;
	eCenter.x = e1->GetPosition().x;
	eCenter.y = e1->GetPosition().y;

	//Get centered vector between Entity and CollisionRect
	GVec2 vec = cCenter - eCenter;

	//Vector standardization
	D3DXVec2Normalize(&vec, &vec);

	/*
	- if Vector standardization has a y > 0 => Top side of Entity
	- if Vector standardization has a y < 0 => Bottom side of Entity
	- if Vector standardization has a x > 0 => Right side of Entity
	- if Vector standardization has a x < 0 => Left side of Entity
	*/

	if (vec.y < 0)
	{
		/*
		 * Top collision
		 * Get corner cosine if it is in the 70 -> 110 Top collision
		 */
		if (vec.x <= 0.35f && vec.x >= -0.35f)
		{
			return BaseObject::TOP;
		}
		if (vec.x > 0.35f && vec.x < 0.8f)
		{
			//The angle is between 35 -> 70 on the top - right side
			return BaseObject::TOP_RIGHT;
		}
		if (vec.x >= 0.8f)
		{
			return BaseObject::RIGHT;
		}
		if (vec.x < -0.35f && vec.x >= -0.8f)
		{
			//Top - Left collision
			return BaseObject::TOP_LEFT;
		}

		return BaseObject::LEFT;
	}

	/*
	* Bottom collision
	* Get corner cosine if it is in the 70 -> 110 Bottom collision
	*/
	if (vec.x <= 0.35f && vec.x >= -0.35)
	{
		return BaseObject::BOTTOM;
	}
	if (vec.x > 0.35 && vec.x < 0.8)
	{
		//The angle is between 35 -> 70 on the Bottom - right side
		return BaseObject::BOTTOM_RIGHT;
	}
	if (vec.x >= 0.8)
	{
		return BaseObject::RIGHT;
	}
	if (vec.x < -0.35f && vec.x > -0.8f)
	{
		//Bottom - Left collision
		return BaseObject::BOTTOM_LEFT;
	}

	return BaseObject::LEFT;
}
