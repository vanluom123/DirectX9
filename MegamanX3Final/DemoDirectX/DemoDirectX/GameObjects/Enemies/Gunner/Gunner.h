#ifndef __HEAD_GUNNER_H__
#define __HEAD_GUNNER_H__

#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"
#include "GunnerBullet/GunnerBullet.h"
#include "../../../GunnerData.h"

class Gunner :public Entity
{
public:
	enum GunnerStateName
	{
		STAND,
		ATTACK,
		ATTACK_ROCKET,
		ATTACK_BULLET,
		FALL,
		DIE,
		NONE
	};

	Gunner();	
	~Gunner();

	void NewEntity() override;
	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(SideCollisions side) override;
	void OnCollision(Entity* obj) override;
	void OnNoCollisionWithBottom() override;

	void Draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(100, 100, 100)) override;
	void ChangeAnimation(GunnerStateName stateName);
	void SetState(GunnerState *state);

protected:

	Animation* anim;
	Animation* animDie;
	GunnerData* pData;
	GunnerStateName curState;
};

#endif
