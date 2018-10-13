#include "Collision.h"
#include <iostream>
using namespace std;


Collision::Collision()
{}


Collision::~Collision()
{}

float max(float x, float y) {
	return (x + y + abs(x - y)) / 2;
}

float min(float x, float y) {
	return (x + y - abs(x - y)) / 2;
}

int Collision::SweptAABB(Box b1, Box b2, float & normalx, float & normaly)
{
	if (b1.vx > 0.0f) {
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else {
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}

	if (b1.vy > 0.0f) {
		yInvEntry = b2.y - (b1.y + b1.h);
		yInvExit = (b2.y + b2.h) - b1.y;
	}
	else {
		yInvEntry = (b2.y + b2.h) - b1.y;
		yInvExit = b2.y - (b1.y + b1.h);

	}

	if (b1.vx == 0.0f) {
		xEntry = std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else {
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}

	if (b1.vy == 0.0f) {
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else {
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	if (entryTime > exitTime || xEntry<0.0f&&yEntry<0.0f || xEntry>1.0f || yEntry>1.0f) {
		normalx = 0.0f;
		normaly = 0.0f;

		return 1.0f;
	}
	else {
		//calculate normal of collided surface
		if (xEntry > yEntry) {
			if (xInvEntry < 0.0f) {
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else {
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else {
			if (yEntry < 0.0f) {
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else {
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		return entryTime;
	}

	return 0;
}

//Broad-phasing
Box Collision::GetSweptBroadphaseBox(Box b)
{
	Box broadphaseBox;
	broadphaseBox.x = b.vx > 0 ? b.x : b.x + b.vx;
	broadphaseBox.y = b.vy > 0 ? b.y : b.y + b.vy;
	broadphaseBox.w = b.vx > 0 ? b.vx + b.w : b.w - b.vx;
	broadphaseBox.h = b.vy > 0 ? b.vy + b.h : b.h - b.vy;

	return broadphaseBox;
}

bool Collision::AABBCheck(Box b1, Box b2)
{
	return !(b1.x + b1.w<b2.x || b1.x>b2.x + b2.w || b1.y + b1.h<b2.y || b1.y>b2.y + b2.h);
}
