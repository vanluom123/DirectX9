#ifndef BANGER_DIE_H
#define BANGER_DIE_H
#include "../BangerState.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../../../../../GameComponents/Sound.h"

class BangerDie :public BangerState
{
public:

	explicit BangerDie(BangerData* banger);
	~BangerDie() = default;

	Banger::BangerStateName GetStateName() override;
	void Update(float dt) override;

private:
	float timeDie;
};
#endif
