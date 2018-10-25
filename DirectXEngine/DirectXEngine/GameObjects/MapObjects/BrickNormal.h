#pragma once
#include "Brick.h"
class BrickNormal : public Brick
{
public:
    ~BrickNormal();

    BrickNormal(D3DXVECTOR3 position);

	const char* FileName() override;
	int TotalFrame() override;
	int Row() override;
	int Column() override;
	float SecondPerFrame() override;
};

