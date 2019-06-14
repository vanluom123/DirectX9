#ifndef BLAST_DIE_H
#define BLAST_DIE_H
#include "BlastState.h"

class BlastDeath :public BlastState
{
	float _timeDie;

public:
	BlastDeath(BlastData* b);
	~BlastDeath();

	void update(float dt) override;
	eBlastState getState() override;
};

#endif // !BLAST_DIE_H
