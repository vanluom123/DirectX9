#include "GameCollision.h"
#include <iostream>
using namespace std;

GameCollision* GameCollision::s_instance = nullptr;


void GameCollision::release()
{
	delete s_instance;
	s_instance = nullptr;
}

GameCollision* GameCollision::getInstance()
{
	if (!s_instance) s_instance = new GameCollision;
	return s_instance;
}

BaseObject::CollisionReturn GameCollision::rectCollision(const RECT& box, const RECT& box2)
{
	BaseObject::CollisionReturn result = BaseObject::CollisionReturn();

	if (!AABBCheck(box, box2))
	{
		result.isCollision = false;
		return result;
	}

	result.isCollision = true;

	result.regionCollision.left = max(box.left, box2.left);
	result.regionCollision.right = max(box.right, box2.right);
	result.regionCollision.bottom = min(box.bottom, box2.bottom);
	result.regionCollision.top = max(box.top, box2.top);

	return result;
}

bool GameCollision::pointCollision(float x, float y, const RECT& box)
{
	return (x >= box.left &&
			y <= box.bottom &&
			x <= box.right &&
			y >= box.top);
}

bool GameCollision::circleCollision(const RECT& bound, int circle_x, int circle_y, int circleRadius)
{
	int px = circle_x;
	int py = circle_y;

	if (px < bound.left)
		px = bound.left;
	else if (px > bound.right)
		px = bound.right;

	if (py > bound.bottom)
		py = bound.bottom;
	else if (py < bound.top)
		py = bound.top;

	const int dx = px - circle_x;
	const int dy = py - circle_y;

	return (dx * dx + dy * dy) <= circleRadius * circleRadius;
}

GVec2 GameCollision::Distance(BaseObject* e1, BaseObject* e2, float dt)
{
	GVec2 distance;
	distance.x = (e1->getVx() - e2->getVx()) * dt;
	distance.y = (e1->getVy() - e2->getVy()) * dt;
	return distance;
}

RECT GameCollision::getBroadphase(const RECT& object, const GVec2& distance)
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

float GameCollision::sweptAABB(const RECT& obj, const RECT& other, const GVec2& distance, Side_Collision& sideCollision)
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

bool GameCollision::AABBCheck(const RECT& box1, const RECT& box2)
{
	return (box1.right >= box2.left &&
			box1.left <= box2.right &&
			box1.bottom >= box2.top &&
			box1.top <= box2.bottom);
}

bool GameCollision::isCollide(const RECT& box1, const RECT& box2)
{

	// Case 1: size object 1 < size object 2
	if (box1.left > box2.left&& box1.left < box2.right)
	{
		if (box1.top > box2.top&& box1.top < box2.bottom)
		{
			return true;
		}

		if (box1.bottom > box2.top&& box1.bottom < box2.bottom)
		{
			return true;
		}
	}

	if (box1.right > box2.left&& box1.right < box2.right)
	{
		if (box1.top > box2.top&& box1.top < box2.bottom)
		{
			return true;
		}

		if (box1.bottom > box2.top&& box1.bottom < box2.bottom)
		{
			return true;
		}
	}

	// Case 2: size object 1 < size object 2
	if (box2.left > box1.left&& box2.left < box1.right)
	{
		if (box2.top > box1.top&& box2.top < box1.bottom)
		{
			return true;
		}

		if (box2.bottom > box1.top&& box2.bottom < box1.bottom)
		{
			return true;
		}
	}

	if (box2.right > box1.left&& box2.right < box1.right)
	{
		if (box2.top > box1.top&& box2.top < box1.bottom)
		{
			return true;
		}

		if (box2.bottom > box1.top&& box2.bottom < box1.bottom)
		{
			return true;
		}
	}

	// Case 3: size object 1 = size object 2
	if (box1.top == box2.top &&
		box1.right == box2.right &&
		box1.bottom == box2.bottom)
	{
		return true;
	}

	return false;
}

void GameCollision::bounce(GVec2& collisionVector, BaseObject& obj, BaseObject& other)
{
	GVec2 Vdiff;
	Vdiff.x = other.getVx() - obj.getVx();
	Vdiff.y = other.getVy() - obj.getVy();
	GVec2 cUV = collisionVector; // Collision unit vector
	D3DXVec2Normalize(&cUV, &cUV);
	float cUVdotVdiff = D3DXVec2Dot(&cUV, &Vdiff);
	float massRatio = 2.0f;
	if (obj.getMass() != 0)
		massRatio *= (other.getMass() / (obj.getMass() + other.getMass()));

	// If entities are already moving apart then bounce must
	// have been previously called and they are still colliding.
	// Move entities apart along collisionVector
	if (cUVdotVdiff > 0)
	{
		auto x = obj.getPosition().x - cUV.x * massRatio;
		auto y = obj.getPosition().y - cUV.y * massRatio;
		obj.setPosition(x, y);
	}
	else
	{
		GVec2 deltaV = { 0, 0 };
		deltaV += ((massRatio * cUVdotVdiff) * cUV);
		obj.setDeltaV(deltaV);
	}
}

bool GameCollision::collideBox(GVec2& collisionVector, const RECT& box1, const RECT& box2)
{
	if (isCollide(box1, box2))
	{
		collisionVector.x = (box2.right - box2.left) / 2 - (box1.right - box1.left) / 2;
		collisionVector.y = (box2.bottom - box2.top) / 2 - (box1.bottom - box1.top) / 2;
		return true;
	}

	return false;
}

Side_Collision GameCollision::getSideCollision(BaseObject* e1, BaseObject* e2)
{
	RECT rect1 = e1->getBound();
	RECT rect2 = e2->getBound();
	int w = (e1->getWidth() + e2->getWidth()) / 2;
	int h = (e1->getHeight() + e2->getHeight()) / 2;

	float dx = e1->getPosition().x - e2->getPosition().y;
	float dy = e1->getPosition().x - e2->getPosition().y;

	if (abs(int(dx)) <= w && abs(int(dy)) <= h)
	{
		// Has a collision
		float wy = w * dy;
		float hx = h * dx;

		if (wy > hx)
		{
			if (wy > -hx)
			{
				//Collision Top e1
				return Side_Collision::TOP;
			}
			//Collision Right e1
			return Side_Collision::RIGHT;
		}
		if (wy > -hx)
		{
			//Collision Left e1
			return Side_Collision::LEFT;
		}

		//Collision Bottom e1
		return Side_Collision::BOTTOM;
	}
	//Don't collide
	return Side_Collision::NONE;
}

Side_Collision GameCollision::getSideCollision(BaseObject* e1, BaseObject::CollisionReturn data)
{
	long xCenter = data.regionCollision.left + (data.regionCollision.right - data.regionCollision.left) / 2;
	long yCenter = data.regionCollision.top + (data.regionCollision.bottom - data.regionCollision.top) / 2;

	GVec2 cCenter = GVec2(float(xCenter), float(yCenter));
	GVec2 eCenter;
	eCenter.x = e1->getPosition().x;
	eCenter.y = e1->getPosition().y;

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
			return Side_Collision::TOP;
		}
		if (vec.x > 0.35f && vec.x < 0.8f)
		{
			//The angle is between 35 -> 70 on the top - right side
			return Side_Collision::TOP_RIGHT;
		}
		if (vec.x >= 0.8f)
		{
			return Side_Collision::RIGHT;
		}
		if (vec.x < -0.35f && vec.x >= -0.8f)
		{
			//Top - Left collision
			return Side_Collision::TOP_LEFT;
		}

		return Side_Collision::LEFT;
	}

	/*
	* Bottom collision
	* Get corner cosine if it is in the 70 -> 110 Bottom collision
	*/
	if (vec.x <= 0.35f && vec.x >= -0.35)
	{
		return Side_Collision::BOTTOM;
	}
	if (vec.x > 0.35 && vec.x < 0.8)
	{
		//The angle is between 35 -> 70 on the Bottom - right side
		return Side_Collision::BOTTOM_RIGHT;
	}
	if (vec.x >= 0.8)
	{
		return Side_Collision::RIGHT;
	}
	if (vec.x < -0.35f && vec.x > -0.8f)
	{
		//Bottom - Left collision
		return Side_Collision::BOTTOM_LEFT;
	}

	return Side_Collision::LEFT;
}
