#ifndef BLAST_STAND_H
#define BLAST_STAND_H

#include "BlastHornetState.h"

class BlastStand :
	public BlastHornetState
{
	float m_timeStand;
public:
	BlastStand(BlastHornetData *b);
	~BlastStand();

	void Update(float dt) override;
	BlastHornet::eBlastState GetState() override;
	void OnCollision(BaseObject::eSideCollision side) override;

};
#endif
