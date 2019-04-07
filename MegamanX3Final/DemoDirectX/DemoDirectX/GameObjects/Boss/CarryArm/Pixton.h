#ifndef PIXTON_H
#define PIXTON_H

#include "../../Entity/Entity.h"
#include "../../../GameComponents/Animation.h"

class Pixton : public Entity
{
private:
	Animation *anim;
	bool isBottom;
	float		posY;
public:
	Pixton();
	~Pixton();

	RECT GetBound() override;
	void Draw(Camera *camera, RECT r = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotate = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void OnCollision(SideCollisions side) override;
	void Update(float gameTime) override;
	bool MoveDown(float gameTime, float x, float y);
	bool MoveUp(float gameTime, float x, float y);
};

#endif