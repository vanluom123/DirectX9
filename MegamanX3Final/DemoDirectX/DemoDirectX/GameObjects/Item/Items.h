#ifndef ITEMS_H
#define ITEMS_H
#include "../Entity/BaseObject.h"
#include "../../GameComponents/Animation.h"

class Items : public BaseObject
{
public:
	Items();
	~Items();

	enum eItemType
	{
		BIG_BLOOD,
		SMALL_BLOOD,
		ENERGY,
		SUBTANK,
		SMALL_SUBTANK
	};

	RECT GetBound() override;

	void Update(float dt) override;

	void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

	void OnCollision(eSideCollision side) override;

	void OnCollision(BaseObject* obj) override;

	virtual Items::eItemType GetItemsType() = 0;

	void SetItemsType(Items::eItemType val) { _itemsType = val; }

protected:
	Animation* _bigItem;
	Animation* _small_item;

private:
	eItemType _itemsType;
};


#endif // !ITEMS_H
