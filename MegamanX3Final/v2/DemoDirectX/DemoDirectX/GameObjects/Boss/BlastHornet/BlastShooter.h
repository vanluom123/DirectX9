#ifndef BLAST_SHOOTER
#define BLAST_SHOOTER
#include "BlastHornetState.h"

class BlastShooter : public BlastHornetState
{
	float _timeShooter;
	int _count;
public:
	BlastShooter(BlastHornetData *b);
	~BlastShooter();

	void Update(float dt) override;
	eBlastState GetState() override;
	void Shoot() override;
};

#endif

