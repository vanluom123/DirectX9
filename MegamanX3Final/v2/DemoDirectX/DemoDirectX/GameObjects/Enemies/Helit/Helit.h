#ifndef HELIT_H
#define HELIT_H

#include "../../Entity/BaseObject.h"
#include "HelitBullet/HelitBullet.h"
#include "../../../GameDefines/GameDefine.h"
using namespace Enumerator;


class HelitState;

class Helit :public BaseObject
{
public:

	Helit();
	~Helit();

	void newObject() override;
	RECT getBound() override;
	void update(float dt) override;
	void onCollision(BaseObject* obj) override;
	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = NULL) override;
	void setState(HelitState* newState);
	void changeAnimation(Helit_State state);

private:
	Animation* _pAnim;
	Animation* _pAnimDie;
	Helit_State m_state;
	HelitState* m_pState;
};

#endif