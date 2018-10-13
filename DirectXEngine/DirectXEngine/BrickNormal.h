#ifndef _BRICK_NORMAL_H
#define _BRICK_NORMAL_H
#include "Brick.h"


class BrickNormal : public Brick
{
public:
	BrickNormal();

	explicit BrickNormal(D3DXVECTOR3 pos);

	~BrickNormal();

protected:
	const char* FileName() override;

	int TotalFrame() override;

	int Row() override;

	int Columns() override;

	float SecondsPerFrame() override;
};

#endif
