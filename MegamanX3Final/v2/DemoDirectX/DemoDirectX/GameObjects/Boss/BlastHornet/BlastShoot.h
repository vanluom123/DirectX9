#ifndef BLAST_SHOOTER
#define BLAST_SHOOTER
#include "BlastState.h"

class BlastShoot : public BlastState
{
public:
	BlastShoot(BlastData *b);
	~BlastShoot();

	void update(float dt) override;
	eBlastState getState() override;
	void shoot() override;

private:
	float _timeShoot;
	int _count;
};

#endif

