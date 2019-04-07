#ifndef BLAST_DIE_H
#define BLAST_DIE_H
#include "BlastHornetState.h"

class BlastDie :public BlastHornetState
{
	float timeDie;

public:
	BlastDie(BlastHornetData* b);
	~BlastDie();

	void Update(float dt) override;
	BlastState GetState() override;
};

#endif // !BLAST_DIE_H
