#ifndef __HEAD_GUNNER_H__
#define __HEAD_GUNNER_H__

#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"
#include "GunnerBullet/GunnerBullet.h"
#include "../../../GunnerData.h"

class Gunner :public BaseObject
{
public:
	enum eGunnerState
	{
		GUNNER_STAND,
		GUNNER_ATTACK,
		GUNNER_ATTACK_ROCKET,
		GUNNER_ATTACK_BULLET,
		GUNNER_FALL,
		GUNNER_DIE,
		GUNNER_NONE
	};

	Gunner();	
	~Gunner();

	void NewEntity() override;
	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(eSideCollision side) override;
	void OnCollision(BaseObject* obj) override;
	void OnNoCollisionWithBottom() override;

	void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(100, 100, 100)) override;
	void ChangeAnimation(eGunnerState stateName);
	void SetState(GunnerState *state);

private:
	Animation* _pAnim;
	Animation* _pAnimDie;
	GunnerData* _pGunnerData;
	eGunnerState _curState;
};

#endif
