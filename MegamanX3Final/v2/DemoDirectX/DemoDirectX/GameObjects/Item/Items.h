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
		BIG_BLOOD = 0,
		SMALL_BLOOD = 1,
		ENERGY = 2,
		SUBTANK = 3,
		SMALL_SUBTANK = 4
	};

	RECT getBound() override;

	void update(float dt) override;

	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

	void onCollision(eSideCollision side) override;

	void onCollision(BaseObject* obj) override;

	virtual Items::eItemType getItemType() = 0;

	void setItemType(Items::eItemType val) { _itemsType = val; }

protected:
	Animation* _animationItem;

private:
	eItemType _itemsType;
};


#endif // !ITEMS_H
