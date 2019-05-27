#ifndef PIXTON_H
#define PIXTON_H

#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"

class Pixton : public BaseObject
{

public:
	Pixton();
	~Pixton();
	
	void Draw(Camera *camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotate = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void OnCollision(eSideCollision side) override;
	void Update(float gameTime) override;

	// SUB-FUNCTION
public:
	RECT GetBound() override;
	bool MoveDown(float gameTime, float x, float y);
	bool MoveUp(float gameTime, float x, float y);

private:
	Animation* m_anim;
	bool m_isBottom;
	float m_pixtonPosY;
};

#endif