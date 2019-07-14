#ifndef _MOVE_TEST_H
#define _MOVE_TEST_H

#include "BlastHornetState.h"

class BlastMove :
	public BlastHornetState
{

public:
	BlastMove(BlastHornet* b, bool moveUp = false);
	BlastMove(BlastHornet* b, bool moveUp = false, bool moveLeftUp = false);
	~BlastMove() = default;

	enum MoveType
	{
		eMoveType_None,
		eMoveType_Up,
		eMoveType_Down
	};

	void update(float dt) override;
	void onCollision(Side_Collision side) override;
	void shoot();
	// Hornet child will confirm the position of player that it attack
	void gps();
	virtual Hornet_State getState() override;

private:
	float m_timeMove;
	int m_count;
	MoveType m_currentMove;
	bool m_moveLeftUp;
};

#endif // !MOVE_H
