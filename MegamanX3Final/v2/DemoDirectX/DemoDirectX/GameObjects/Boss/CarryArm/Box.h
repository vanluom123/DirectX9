#ifndef BOX_H
#define BOX_H
#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"

class Box :
	public BaseObject
{
	Animation* anim;
	Animation* pAnimationDie;
	bool isBottom;
	bool isR;
public:
	Box(bool isr = false);
	~Box();

	void newObject() override;
	void draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotateCenter = GVec2(), D3DCOLOR color = NULL) override;
	RECT getBound() override;
	void update(float dt) override;
	void onCollision(Side_Collision side) override;
	void onCollision(BaseObject* obj) override;
	bool getIsBottom() const { return isBottom; }
	void setIsBottom(bool val) { isBottom = val; }
};

#endif // !BOX_H
