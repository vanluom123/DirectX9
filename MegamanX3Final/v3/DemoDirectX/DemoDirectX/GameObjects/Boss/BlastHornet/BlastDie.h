#ifndef BLAST_DIE_H
#define BLAST_DIE_H
#include "BlastHornetState.h"

class BlastDie :public BlastHornetState
{
	float m_timeDie;

public:
	BlastDie(BlastHornetData* b);
	~BlastDie();

	void Update(float dt) override;
	BlastHornet::eBlastState GetState() override;
};

#endif // !BLAST_DIE_H
