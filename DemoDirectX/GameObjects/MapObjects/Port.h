#ifndef PORT_H
#define PORT_H
#include "../Entity/BaseObject.h"
#include "../../GameComponents/Animation.h"

class Port :
	public BaseObject
{
protected:
	Animation* _pAnim;
	bool _isOpen;
	bool _isClose;
	bool _isMove;
	RECT _bound{};

public:
	Port();
	~Port();

	RECT getBound() override;
	void update(float dt) override;
	void onCollision(Side_Collision side) override;
	void onCollision(BaseObject* obj) override;
	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0.0f, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

};
#endif // !PORT_H
