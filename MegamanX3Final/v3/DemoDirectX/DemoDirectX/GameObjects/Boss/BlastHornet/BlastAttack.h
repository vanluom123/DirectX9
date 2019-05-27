#ifndef BLAST_ATTACK_H
#define BLAST_ATTACK_H
#include "BlastHornetState.h"

class BlastAttack : public BlastHornetState
{
public:
	BlastAttack(BlastHornetData* b);
	~BlastAttack();

	void Update(float dt) override;
	void OnCollision(BaseObject::eSideCollision side) override;
	BlastHornet::eBlastState GetState() override;
};
#endif // !BLAST_ATTACK_H

