﻿#include "BlastDie.h"

BlastDie::BlastDie(BlastHornetData* b) :BlastHornetState(b)
{
	timeDie = 0;
}

BlastDie::~BlastDie()
{}

void BlastDie::Update(float dt)
{
	timeDie += dt;
	if (timeDie > 1)
		b->GetHornet()->SetDraw(false);
}

BlastState BlastDie::GetState()
{
	return BlastState::Die;
}
