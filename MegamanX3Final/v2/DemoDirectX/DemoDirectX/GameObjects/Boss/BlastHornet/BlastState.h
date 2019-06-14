#ifndef BLAST_HORNET_STATE_H
#define BLAST_HORNET_STATE_H

#include "Blast.h"

class BlastState
{
public:
	BlastState(BlastData* b)
	{
		_data = b;
	}

	virtual ~BlastState() = default;

	virtual void update(float dt) { }
	virtual void onCollision(BaseObject::eSideCollision side) { }
	virtual eBlastState getState() = 0;
	virtual void shoot() { }

protected:
	BlastData* _data;
	Blast* _pBlast;
};

#endif // !BLAST_HORNET_STATE_H
