#ifndef BLAST_HORNET_STATE_H
#define BLAST_HORNET_STATE_H
#include "BlastHornet.h"

class BlastHornetState
{
protected:
	BlastHornetData* b;

	float accelerateX; //gia toc x
	float accelerateY; //gia toc y
public:
	BlastHornetState(BlastHornetData* b);
	virtual ~BlastHornetState();

	virtual void Update(float dt);
	virtual void OnCollision(Entity::SideCollisions side);
	virtual BlastState GetState() = 0;
	virtual void Shoot();
};
#endif // !BLAST_HORNET_STATE_H
