#ifndef BLAST_APPEAR_H
#define BLAST_APPEAR_H
#include "BlastHornetState.h"

class BlastAppear :
	public BlastHornetState
{
	float m_timeAppear;
public:
	BlastAppear(BlastHornetData* b);
	~BlastAppear();

	void Update(float dt) override;
	BlastHornet::eBlastState GetState() override;
};

#endif // !BLAST_APPEAR_H
