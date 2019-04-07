#ifndef MOVE_H
#define MOVE_H

#include "BlastHornetState.h"

class MoveTest :public BlastHornetState
{
	float timeMove;
	int count;
public:
	MoveTest(BlastHornetData* b);
	~MoveTest();

	void Update(float dt) override;
	BlastState GetState() override;
	void Shoot() override;
	void GPS();
};

#endif // !MOVE_H
