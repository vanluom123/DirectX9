#ifndef BLAST_STAND_H
#define BLAST_STAND_H

#include "BlastHornetState.h"

class BlastStand :
	public BlastHornetState
{
	float timeStand;
public:
	BlastStand(BlastHornetData *b);
	~BlastStand();

	void Update(float dt) override;
	BlastState GetState() override;
	void OnCollision(Entity::SideCollisions side) override;

};
#endif
