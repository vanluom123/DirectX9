#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "../Entity/BaseObject.h"
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/Camera.h"

class Elevator :
	public BaseObject
{
public:
	Elevator();
	~Elevator();

	void Update(float dt) override;
	void OnCollision(eSideCollision side) override;
	void OnCollision(BaseObject* obj) override;

	 void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

protected:
	Animation* pAnimation;
	bool isRun;
};
#endif // !ELEVATOR_H

