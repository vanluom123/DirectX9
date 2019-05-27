#ifndef BLAST_HORNET_STATE_H
#define BLAST_HORNET_STATE_H
#include "BlastHornet.h"

class BlastHornetState
{
protected:
	BlastHornetData* _pBlastHornetData;

	float accelerateX; //gia toc x
	float accelerateY; //gia toc y
public:
	BlastHornetState(BlastHornetData* b);
	virtual ~BlastHornetState();

	virtual void Update(float dt);
	virtual void OnCollision(BaseObject::eSideCollision side);
	virtual BlastState GetState() = 0;
	virtual void Shoot();
};
#endif // !BLAST_HORNET_STATE_H
