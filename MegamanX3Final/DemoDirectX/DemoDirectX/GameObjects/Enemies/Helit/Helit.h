#ifndef HELIT_H
#define HELIT_H

#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"
#include "HelitBullet/HelitBullet.h"
#include "../../../GameComponents/Camera.h"
#include "../../../HelitData.h"


class Helit :
	public Entity
{
public:
	enum StateName
	{
		Stand,
		Attack,
		Die,
		None
	};

	Helit();
	~Helit();

	void NewEntity() override;

	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(Entity* obj) override;
	void Draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = NULL) override;

	void setState(HelitState *newState);
	void changeAnimation(StateName state);

protected:

	Animation*					anim;
	Animation*					animDie;
	HelitData*					pData;
	StateName					currentState;
};

#endif