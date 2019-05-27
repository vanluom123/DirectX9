#ifndef PIXTON_H
#define PIXTON_H

#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"

class Pixton : public BaseObject
{
private:
	Animation *anim;
	bool isBottom;
	float		posY;
public:
	Pixton();
	~Pixton();

	RECT GetBound() override;
	void Draw(Camera *camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotate = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void OnCollision(eSideCollision side) override;
	void Update(float gameTime) override;
	bool MoveDown(float gameTime, float x, float y);
	bool MoveUp(float gameTime, float x, float y);
};

#endif