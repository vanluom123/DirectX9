#ifndef __HEAD_GUNNER_H__
#define __HEAD_GUNNER_H__

#include "../../Entity/BaseObject.h"
#include "GunnerBullet/GunnerBullet.h"
#include "../../../GameDefines/GameDefine.h"
using namespace Enumerator;

class GunnerState;

class Gunner : public BaseObject
{
private:
	Animation* _pAnim;
	Animation* _pAnimDie;
	Gunner_State _curState;
	GunnerState* m_pState;

public:

	Gunner();	
	~Gunner();

	void newObject() override;
	RECT getBound() override;
	void update(float dt) override;
	void onCollision(Side_Collision side) override;
	void onCollision(BaseObject* obj) override;
	void onNoCollisionWithBottom() override;
	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(100, 100, 100)) override;
	void changeAnimation(Gunner_State stateName);
	void setState(GunnerState *state);

};

#endif
