#ifndef BLAST_HORNET_STATE_H
#define BLAST_HORNET_STATE_H
#include "BlastHornet.h"

class BlastHornetState
{
public:
	explicit BlastHornetState(BlastHornet* b);
	virtual ~BlastHornetState();

	virtual void update(float dt);
	virtual void onCollision(Side_Collision side);
	virtual Hornet_State getState();

protected:
	BlastHornet* b;

	float m_transX;
	float m_transY;
};
#endif // !BLAST_HORNET_STATE_H
