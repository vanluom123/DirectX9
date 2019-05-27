#ifndef MOVE_H
#define MOVE_H

#include "BlastHornetState.h"

class SineMovement :public BlastHornetState
{
public:
	SineMovement(BlastHornetData* b);
	~SineMovement();

	void Update(float dt) override;
	eBlastState GetState() override;
	void Shoot() override;
	void GPS();

private:
	void MoveRight();
	void MoveLeft();

	double newPosX(int amplitude, int frequency, int milliSecs);
	double newPosY(int milliSecs, int speed);

private:
	float _timeMove;
	int _count;
};

#endif // !MOVE_H
