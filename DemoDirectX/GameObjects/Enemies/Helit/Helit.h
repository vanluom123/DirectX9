#ifndef HELIT_H
#define HELIT_H

#include "../../Entity/BaseObject.h"
#include "HelitBullet/HelitBullet.h"
#include "../../../GameDefines/GameDefine.h"
using namespace Enumerator;


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
	void changeAnimation(Helit_State state);

	void updateStatus(float dt);
	void updateStand(float dt);
	void updateAttack(float dt);
	void updateDeath(float dt);

	void initStand();
	void initAttack();
	void initDeath();
	void initStatus(Helit_State status);

	void changeStatus(Helit_State status);

private:
	Animation* _pAnim;
	Animation* _pAnimDie;
	Helit_State m_state;

	float _timeStand;
	float _timeDie;
	float _timeAttack;
	float _accelerateY;
	int _count;
};

#endif