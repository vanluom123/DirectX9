#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "../Entity/Entity.h"
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/Camera.h"

class Elevator :
	public Entity
{
public:
	Elevator();
	~Elevator();

	void Update(float dt) override;
	void OnCollision(SideCollisions side) override;
	void OnCollision(Entity* obj) override;

	 void Draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

protected:
	Animation* pAnimation;
	bool isRun;
};
#endif // !ELEVATOR_H

