#ifndef BLAST_SHOOT
#define BLAST_SHOOT
#include "BlastHornetState.h"

class BlastShoot
	: public BlastHornetState
{

public:
	BlastShoot(BlastHornet* b);
	~BlastShoot();

	void update(float dt) override;
	void shoot();
	virtual Hornet_State getState() override;

private:
	float m_timeShoot;
	int m_count;
};

#endif

