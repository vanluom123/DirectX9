#include "HelitData.h"

HelitData::HelitData()
{
	helit = nullptr;
	helitState = nullptr;
}


HelitData::~HelitData()
{}

HelitState* HelitData::GetHelitState() const
{
	return helitState;
}

void HelitData::SetHelitState(HelitState* val)
{
	helitState = val;
}

Helit* HelitData::GetHelit() const
{
	return helit;
}

void HelitData::SetHelit(Helit* val)
{
	helit = val;
}
