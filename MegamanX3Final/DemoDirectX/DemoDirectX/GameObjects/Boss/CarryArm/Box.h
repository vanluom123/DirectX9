#ifndef BOX_H
#define BOX_H
#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"

class Box :
	public Entity
{
	Animation* anim;
	Animation* pAnimationDie;
	bool isBottom;
	bool isR;
public:
	Box(bool isr = false);
	~Box();

	void NewEntity() override;
	void Draw(Camera* camera, RECT r = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotateCenter = D3DXVECTOR2(), D3DCOLOR color = NULL) override;
	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(SideCollisions side) override;
	void OnCollision(Entity* obj) override;
	bool GetBottom() const { return isBottom; }
	void SetBottom(bool val) { isBottom = val; }
};

#endif // !BOX_H
