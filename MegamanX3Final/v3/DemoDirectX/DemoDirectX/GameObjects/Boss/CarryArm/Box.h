#ifndef BOX_H
#define BOX_H
#include "../../Entity/BaseObject.h"
#include "../../../GameComponents/Animation.h"
#include "../../../GameComponents/Camera.h"

class Box :
	public BaseObject
{
	Animation* m_anim;
	Animation* m_animDie;
	bool m_isBottom;
	bool m_isR;

public:
	Box(bool isr = false);
	~Box();

	void NewEntity() override;
	void Draw(Camera* camera, RECT r = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotateCenter = GVec2(), D3DCOLOR color = NULL) override;
	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(eSideCollision side) override;
	void OnCollision(BaseObject* obj) override;

	bool GetBottom() const { return m_isBottom; }
	void SetBottom(bool val) { m_isBottom = val; }
};

#endif // !BOX_H
