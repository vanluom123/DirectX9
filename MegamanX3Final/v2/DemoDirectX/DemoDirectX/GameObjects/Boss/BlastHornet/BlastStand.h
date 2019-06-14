#ifndef _BLAST_STAND_H
#define _BLAST_STAND_H

#include "BlastState.h"

class BlastStand : public BlastState
{
public:
	BlastStand(BlastData *b);
	~BlastStand();

	void update(float dt) override;
	eBlastState getState() override;

private:
	float _timeStand;
};
#endif // _BLAST_STAND_H