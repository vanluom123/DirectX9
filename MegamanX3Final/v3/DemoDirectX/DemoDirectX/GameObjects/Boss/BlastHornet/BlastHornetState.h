#ifndef BLAST_HORNET_STATE_H
#define BLAST_HORNET_STATE_H
#include "BlastHornet.h"

class BlastHornetState
{
protected:
	BlastHornetData* m_blastHornetData;

	float m_accelerateX; //gia toc x
	float m_accelerateY; //gia toc y
public:
	BlastHornetState(BlastHornetData* b);
	virtual ~BlastHornetState();

	virtual void Update(float dt);
	virtual void OnCollision(BaseObject::eSideCollision side);
	virtual BlastHornet::eBlastState GetState() = 0;
	virtual void Shoot();
};
#endif // !BLAST_HORNET_STATE_H
