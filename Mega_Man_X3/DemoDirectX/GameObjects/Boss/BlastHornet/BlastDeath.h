#ifndef BLAST_DEATH_H
#define BLAST_DEATH_H
#include "BlastHornetState.h"

class BlastDeath :
	public BlastHornetState
{

public:
	BlastDeath(BlastHornet* b);
	~BlastDeath() = default;

	void update(float dt) override;
	virtual Hornet_State getState() override;

private:
	float m_timeDeath;

};

#endif // !BLAST_DIE_H
