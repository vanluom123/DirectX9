#ifndef BANGER_H
#define BANGER_H

#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameDefines/GameDefine.h"
using namespace Enumerator;

class BangerState;

class Banger :
	public BaseObject
{

public:

	Banger();
	~Banger();

	void newObject() override;
	void changeAnimation(Banger_State state);
	void setState(BangerState* new_state);
	RECT getBound() override;
	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0.0f, GVec2 rotationCenter = GVec2(), D3DCOLOR transColor = D3DCOLOR_XRGB(255, 255, 255))override;
	void update(float gameTime) override;
	void onCollision(Side_Collision side) override;
	void onCollision(BaseObject* obj) override;
	void onNoCollisionWithBottom() override;
	Animation* getAnimation() const;

private:
	Animation* _current_anim;
	Animation* _anim_die;
	BangerState* m_pState;
	Banger_State m_state;
};
#endif // !BANGER_H
