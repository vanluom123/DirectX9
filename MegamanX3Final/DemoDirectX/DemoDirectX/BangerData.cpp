#include "BangerData.h"



BangerData::BangerData()
{
	banger = nullptr;
	bangerState = nullptr;
}


BangerData::~BangerData()
{}

Banger* BangerData::GetBanger() const
{
	return banger;
}

void BangerData::SetBanger(Banger* val)
{
	banger = val;
}

BangerState* BangerData::GetBangerState() const
{
	return bangerState;
}

void BangerData::SetBangerState(BangerState* val)
{
	bangerState = val;
}
