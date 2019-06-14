#pragma once
#include "BlastState.h"

class SinWaveMovement :public BlastState
{
public:
	SinWaveMovement(BlastData* b);
	~SinWaveMovement();

	void update(float dt) override;
	eBlastState getState() override;
	void shoot() override;
	void GPS();

private:
	void MoveRight();
	void MoveLeft();

	double newPosY(int amplitude, int frequency, int milliSecs);
	double newPosX(int milliSecs, int speed);

private:
	float _timeMove;
	int _count;
};

