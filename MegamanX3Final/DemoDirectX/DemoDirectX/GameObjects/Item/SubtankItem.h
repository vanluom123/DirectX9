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

	void Draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

	void OnCollision(Entity* obj) override;

	Items::ItemsType GetItemsType() override;

};

#endif // !SUBTANK_ITEM_H
