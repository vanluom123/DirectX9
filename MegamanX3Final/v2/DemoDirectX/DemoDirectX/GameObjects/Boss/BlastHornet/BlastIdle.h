#ifndef __BLAST_IDLE_H__
#define __BLAST_IDLE_H__

#include "BlastHornetState.h"

class BlastIdle :
	public BlastHornetState
{
public:
	BlastIdle(BlastHornet* b);
	~BlastIdle();

	void update(float dt) override;
	virtual Hornet_State getState() override;

private:
	float m_timeIdle;
};
#endif
