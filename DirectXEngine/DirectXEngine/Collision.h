#pragma once

struct Box {
	//position of top-left corner
	float x, y;

	//demensions
	float w, h;

	//veloctiy
	float vx, vy;
};

class Collision
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;
	float xEntry, yEntry;
	float xExit, yExit;

public:
	Collision();
	~Collision();

	int SweptAABB(Box b1, Box b2, float& normalx, float& normaly);
	Box GetSweptBroadphaseBox(Box b);
	bool AABBCheck(Box b1, Box b2);
};

