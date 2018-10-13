#ifndef _BRICK_GOLD_H
#define _BRICK_GOLD_H
#include "Brick.h"

class BrickGold :public Brick
{
protected:
	const char* FileName() override;

	int TotalFrame() override;

	int Row() override;

	int Columns() override;

	float SecondsPerFrame() override;

public:
	BrickGold();

	explicit BrickGold(D3DXVECTOR3 pos);

	~BrickGold();
};

#endif
