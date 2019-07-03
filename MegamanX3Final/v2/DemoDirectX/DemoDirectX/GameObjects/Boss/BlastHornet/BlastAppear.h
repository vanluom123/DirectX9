#ifndef BLAST_APPEAR_H
#define BLAST_APPEAR_H
#include "BlastHornetState.h"

class BlastAppear :
	public BlastHornetState
{
public:
	BlastAppear(BlastHornet * b);
	~BlastAppear();

	void update(float dt) override;
	virtual Hornet_State getState() override;

private:
	float m_timeAppear;

};

#endif // !BLAST_APPEAR_H
