#ifndef HELIT_H
#define HELIT_H

#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "HelitBullet/HelitBullet.h"
#include "../../../GameComponents/Camera.h"
#include "../../../HelitData.h"


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

	void NewEntity() override;

	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(BaseObject* obj) override;
	void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = NULL) override;

	void SetState(HelitState* newState);
	void ChangeAnimation(eHelitState state);

private:
	Animation* m_anim;
	Animation* m_animDie;
	HelitData* m_helitData;
	eHelitState m_currentState;
};

#endif