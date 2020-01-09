#ifndef ITEMS_H
#define ITEMS_H
#include "../Entity/BaseObject.h"
#include "../../GameComponents/Animation.h"

class Item : public BaseObject
{
protected:
	Animation* _animationItem;

private:
	Item_Type _itemsType;

public:
	Item();
	~Item();

	RECT getBound() override;
	void update(float dt) override;
	void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;
	void onCollision(Side_Collision side) override;
	void onCollision(BaseObject* obj) override;
	virtual Item_Type getItemType() = 0;
	void setItemType(Item_Type val);

};


#endif // !ITEMS_H
