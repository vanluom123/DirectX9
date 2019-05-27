#ifndef PORT_H
#define PORT_H
#include "../Entity/BaseObject.h"
#include "../../GameComponents/Animation.h"
#include "../../GameComponents/Camera.h"

class Port :
	public BaseObject
{
public:
	Port();
	~Port();

	RECT GetBound() override;
	void Update(float dt) override;
	void OnCollision(eSideCollision side) override;
	void OnCollision(BaseObject* obj) override;
	void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

protected:
	Animation* pAnimation;
	bool isOpen;
	bool isClose;
	bool isMove;
	RECT bound;
};
#endif // !PORT_H
