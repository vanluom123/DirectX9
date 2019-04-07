#ifndef ITEMS_H
#define ITEMS_H
#include "../Entity/Entity.h"
#include "../../GameComponents/Animation.h"

class Items : public Entity
{
public:
	Items();
	~Items();

	enum ItemsType
	{
		BIG_BLOOD,
		SMALL_BLOOD,
		ENERGY,
		SUBTANKS,
		SMALL_SUBTANKS
	};

	RECT GetBound() override;

	void Update(float dt) override;

	void Draw(Camera* camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

	void OnCollision(SideCollisions side) override;

	void OnCollision(Entity* obj) override;

	virtual Items::ItemsType GetItemsType() = 0;

	void SetItemsType(Items::ItemsType val) { itemsType = val; }

protected:
	Animation* bigItem;
	Animation* small_item;

private:
	ItemsType		itemsType;
};


#endif // !ITEMS_H
