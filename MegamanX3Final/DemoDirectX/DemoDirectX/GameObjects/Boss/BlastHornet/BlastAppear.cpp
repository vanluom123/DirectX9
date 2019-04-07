#include "BlastAppear.h"
#include "BlastStand.h"


BlastAppear::BlastAppear(BlastHornetData* b) :BlastHornetState(b)
{
	b->GetHornet()->SetVx(0);
	b->GetHornet()->SetVy(0);
	timeAppear = 0;
}

BlastAppear::~BlastAppear()
{}

void BlastAppear::Update(float dt)
{
	timeAppear += dt;
	if (timeAppear > 3.0f)
	{
		b->GetHornet()->allowMove = true;
		b->GetHornet()->SetState(new BlastStand(b));
	}
}

BlastState BlastAppear::GetState()
{
	return BlastState::Appear;
}
