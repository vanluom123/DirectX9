#include "BrickGold.h"

const char* BrickGold::FileName()
{
	return "Resources/goldbrick.png";
}

int BrickGold::TotalFrame()
{
	return 4;
}

int BrickGold::Row()
{
	return 1;
}

int BrickGold::Columns()
{
	return 4;
}

float BrickGold::SecondsPerFrame()
{
	return 1.0f;
}

BrickGold::BrickGold()
{}

BrickGold::BrickGold(D3DXVECTOR3 pos)
{
	Init(pos);
}

BrickGold::~BrickGold()
{}
