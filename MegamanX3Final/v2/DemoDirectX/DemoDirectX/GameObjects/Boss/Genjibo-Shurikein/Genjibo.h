#ifndef GENJIBO_H
#define GENJIBO_H
#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"

class Genjibo :
	public BaseObject
{
protected:
	Animation* anim;
	Animation* animGenjinbo;
	Animation* animDie;
	Genjibo_State currentState;
	Shurikein_State shurikeinState;
	Side_Collision sideGen;
	float timeStand;
	bool change;
	float posY;
	float transY;
	int count;
	float timeMove;

public:
	Genjibo();
	~Genjibo();

	RECT getBound() override;
	void update(float dt) override;
	void onCollision(BaseObject* obj) override;
	void onCollision(Side_Collision side) override;
	void draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotate = GVec2(), D3DCOLOR color = NULL) override;
	void setState(Shurikein_State keinState);
	void updateState(float dt);
};

#endif // !GENJIBO_H
