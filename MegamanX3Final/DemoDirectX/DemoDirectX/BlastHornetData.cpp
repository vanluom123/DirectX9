#include "BlastHornetData.h"

BlastHornetData::BlastHornetData()
{
	blastHornet = nullptr;
	blastHornetState = nullptr;
}


BlastHornetData::~BlastHornetData()
{}

BlastHornet* BlastHornetData::GetHornet() const
{
	return blastHornet;
}

void BlastHornetData::SetHornet(BlastHornet* val)
{
	blastHornet = val;
}

BlastHornetState* BlastHornetData::GetHornetState() const
{
	return blastHornetState;
}

void BlastHornetData::SetHornetState(BlastHornetState* val)
{
	blastHornetState = val;
}
