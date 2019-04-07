#ifndef CONVEYOR_H
#define CONVEYOR_H
#include "../Entity/Entity.h"
#include "../../GameComponents/Animation.h"

class Camera;

class Conveyor :
	public Entity
{
public:
	Conveyor(bool direction);
	~Conveyor();

	void Update(float dt) override;
	void OnCollision(SideCollisions side) override;
	void OnCollision(Entity* obj) override;

	void Draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

protected:
	Animation* pAnimation;
	Animation* pAnimation1;
	int VelocityX;
};


#endif // !CONVEYOR_H
