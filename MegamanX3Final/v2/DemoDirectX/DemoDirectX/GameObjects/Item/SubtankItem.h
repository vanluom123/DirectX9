#ifndef SUBTANK_ITEM_H
#define SUBTANK_ITEM_H
#include "Items.h"

class SubtankItem : public Items
{

public:
	SubtankItem();
	~SubtankItem();

	RECT GetBound() override;

	void Update(float dt) override;

	void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

	void OnCollision(BaseObject* obj) override;

	Items::eItemType GetItemsType() override;

};

#endif // !SUBTANK_ITEM_H
