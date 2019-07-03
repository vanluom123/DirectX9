#ifndef BANGER_DIE_H
#define BANGER_DIE_H
#include "../BangerState.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../../../../../GameComponents/Sound.h"

class BangerDie :
	public BangerState
{
public:

	BangerDie(Banger* banger);
	~BangerDie();
	void Update(float dt) override;
	virtual Banger_State getState() override;

private:
	float _timeDie;
};
#endif
