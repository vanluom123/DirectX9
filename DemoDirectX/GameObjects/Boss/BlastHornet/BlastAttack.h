#ifndef BLAST_ATTACK_H
#define BLAST_ATTACK_H
#include "BlastHornetState.h"

class BlastAttack : 
	public BlastHornetState
{
public:
	BlastAttack(BlastHornet* b);
	~BlastAttack() = default;

	void update(float dt) override;
	void onCollision(Side_Collision side) override;
	virtual Hornet_State getState() override;

private:
	float m_timeAttack;
	GVec2 m_distance;
};
#endif // !BLAST_ATTACK_H

