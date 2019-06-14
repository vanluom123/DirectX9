#ifndef BLAST_APPEAR_H
#define BLAST_APPEAR_H
#include "BlastState.h"

class BlastAppear :
	public BlastState
{
public:
	BlastAppear(BlastData* b);
	~BlastAppear();

	void update(float dt) override;
	eBlastState getState() override;

private:
	float _time_appear;

};

#endif // !BLAST_APPEAR_H
