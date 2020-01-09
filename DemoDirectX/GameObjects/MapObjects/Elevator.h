#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "../Entity/BaseObject.h"
#include "../../GameComponents/Animation.h"

class Elevator :
	public BaseObject
{
protected:
	Animation* _pAnim;
	bool _isRun;

public:
	Elevator();
	~Elevator();

	void update(float dt) override;
	void onCollision(Side_Collision side) override;
	void onCollision(BaseObject* obj) override;

	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

};
#endif // !ELEVATOR_H

