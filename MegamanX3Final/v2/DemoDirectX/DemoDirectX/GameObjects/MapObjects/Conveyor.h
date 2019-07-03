#ifndef CONVEYOR_H
#define CONVEYOR_H
#include "../Entity/BaseObject.h"
#include "../../GameComponents/Animation.h"

class Camera;

class Conveyor :
	public BaseObject
{
public:
	Conveyor(bool direction);
	~Conveyor();

	void update(float dt) override;
	void onCollision(Side_Collision side) override;
	void onCollision(BaseObject* obj) override;

	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

protected:
	Animation* _pAnim;
	Animation* _pAnim2;
	int _velocityX;
};


#endif // !CONVEYOR_H
