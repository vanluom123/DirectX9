#ifndef BLAST_ATTACK_H
#define BLAST_ATTACK_H
#include "BlastState.h"

class BlastAttack : public BlastState
{
public:
	BlastAttack(BlastData* b);
	~BlastAttack();

	enum eAttackType
	{
		MOVE_UP,
		MOVE_DOWN,
		DONT_MOVE
	};

	void update(float dt) override;
	void onCollision(BaseObject::eSideCollision side) override;
	eBlastState getState() override;

private:
	eAttackType _attackType;
	float _speedX;
	float _speedY;
};
#endif // !BLAST_ATTACK_H

