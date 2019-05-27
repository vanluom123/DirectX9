#ifndef BANGER_DIE_H
#define BANGER_DIE_H
#include "../BangerState.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../../../../../GameComponents/Sound.h"

class BangerDie :public BangerState
{
public:

	 BangerDie(BangerData* banger);

	Banger::eBangerState GetStateName() override;
	void Update(float dt) override;

private:
	float _timeDie;
};
#endif
