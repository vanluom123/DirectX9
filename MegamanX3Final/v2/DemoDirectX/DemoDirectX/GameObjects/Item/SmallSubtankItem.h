#ifndef SMALL_SUBTANK_H
#define SMALL_SUBTANK_H
#include "Items.h"

class SmallSubtankItem : public Items
{
public:
	SmallSubtankItem();
	~SmallSubtankItem();

	RECT getBound() override;

	void update(float dt) override;

	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

	void onCollision(BaseObject* obj) override;

	Items::eItemType getItemType() override;

};

#endif
