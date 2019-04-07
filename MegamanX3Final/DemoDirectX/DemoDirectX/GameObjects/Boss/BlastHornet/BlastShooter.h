#ifndef BLAST_SHOOTER
#define BLAST_SHOOTER
#include "BlastHornetState.h"

class BlastShooter : public BlastHornetState
{
	float timeShooter;
	int count;
public:
	BlastShooter(BlastHornetData *b);
	~BlastShooter();

	void Update(float dt) override;
	BlastState GetState() override;
	void Shoot() override;
};

#endif

