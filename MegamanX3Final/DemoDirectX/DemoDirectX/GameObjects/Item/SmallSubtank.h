#ifndef SMALL_SUBTANK_H
#define SMALL_SUBTANK_H
#include "Items.h"

class SmallSubtank : public Items
{
public:
	SmallSubtank();
	~SmallSubtank();

	RECT GetBound() override;

	void Update(float dt) override;

	void Draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

	void OnCollision(Entity* obj) override;

	Items::ItemsType GetItemsType() override;

};

#endif
