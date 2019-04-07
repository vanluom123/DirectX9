#include "GunnerData.h"



GunnerData::GunnerData()
{
	gunner = nullptr;
	gunnerState = nullptr;
}


GunnerData::~GunnerData()
{}

Gunner* GunnerData::GetGunner() const
{
	return gunner;
}

void GunnerData::SetGunner(Gunner* val)
{
	gunner = val;
}

GunnerState* GunnerData::GetGunnerState() const
{
	return gunnerState;
}

void GunnerData::SetGunnerState(GunnerState* val)
{
	gunnerState = val;
}
