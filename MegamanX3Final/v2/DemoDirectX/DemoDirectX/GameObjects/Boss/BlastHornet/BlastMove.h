#ifndef _MOVE_TEST_H
#define _MOVE_TEST_H

#include "BlastHornetState.h"

class MoveTest :
	public BlastHornetState
{

public:
	MoveTest(BlastHornet* b, bool moveUp);
	~MoveTest();

	enum class MovementType
	{
		MOVE_TO_SIN,
		MOVE_TO_INFINITY,
		MOVE_UP,
		MOVE_DOWN
	};

	void update(float dt) override;
	void onCollision(Side_Collision side) override;
	void shoot();
	void GPS();
	virtual Hornet_State getState() override;

private:
	float m_timeMove;
	int m_count;
	MovementType m_moveType;
	float m_gocSin;
};

#endif // !MOVE_H
