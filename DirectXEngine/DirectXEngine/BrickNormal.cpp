#include "BrickNormal.h"



BrickNormal::BrickNormal()
{}


BrickNormal::BrickNormal(D3DXVECTOR3 pos)
{
	Init(pos);
}

BrickNormal::~BrickNormal()
{}

const char* BrickNormal::FileName()
{
	return "Resources/normalbrick.png";
}

int BrickNormal::TotalFrame()
{
	return 1;
}

int BrickNormal::Row()
{
	return 1;
}

int BrickNormal::Columns()
{
	return 1;
}

float BrickNormal::SecondsPerFrame()
{
	return 1.0f;
}
