#ifndef HELIT_H
#define HELIT_H

#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "HelitBullet/HelitBullet.h"
#include "../../../GameComponents/Camera.h"
#include "HelitData.h"


class Helit :public BaseObject
{
public:
	enum eHelitState
	{
		HELIT_STAND,
		HELIT_ATTACK,
		HELIT_DIE,
		HELIT_UNKNOWN
	};

	Helit();
	~Helit();

	void newObject() override;

	RECT getBound() override;
	void update(float dt) override;
	void onCollision(BaseObject* obj) override;
	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = NULL) override;

	void setState(HelitState* newState);
	void changeAnimation(eHelitState state);

private:
	Animation* _pAnim;
	Animation* _pAnimDie;
	HelitData* _pHelitData;
	eHelitState _currentState;
};

#endif