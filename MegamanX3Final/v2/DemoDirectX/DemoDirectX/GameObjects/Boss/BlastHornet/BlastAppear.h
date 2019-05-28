#ifndef BLAST_APPEAR_H
#define BLAST_APPEAR_H
#include "BlastHornetState.h"

class BlastAppear :
	public BlastHornetState
{
	float timeAppear;
public:
	BlastAppear(BlastHornetData* b);
	~BlastAppear();

	void Update(float dt) override;
	eBlastState GetState() override;
};

#endif // !BLAST_APPEAR_H
