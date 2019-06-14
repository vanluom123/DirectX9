#ifndef BANGER_H
#define BANGER_H
#include <vector>
#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "BangerBullet/BangerBullet.h"
#include "../../../GameComponents/Camera.h"
#include "BangerData.h"

class Banger :
	public BaseObject
{

public:

	Banger();
	~Banger();

	void newObject() override;

	enum eBangerState
	{
		BANGER_STAND,
		BANGER_JUMP,
		BANGER_FALL,
		BANGER_ATTACK,
		BANGER_DIE,
		BANGER_NONE
	};

	void changeAnimation(eBangerState state);

	Animation* getAnimation() const { return _current_anim; }

	void setState(BangerState* newState);
	RECT getBound() override;

	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0.0f, GVec2 rotationCenter = GVec2(), D3DCOLOR transColor = D3DCOLOR_XRGB(255, 255, 255))override;

	void update(float gameTime) override;
	void onCollision(eSideCollision side) override;
	void onCollision(BaseObject* obj) override;
	void onNoCollisionWithBottom() override;

private:
	BangerData* _pBangerData;
	Animation* _current_anim;
	Animation* _anim_die;

	eBangerState _currentState;
};
#endif // !BANGER_H
