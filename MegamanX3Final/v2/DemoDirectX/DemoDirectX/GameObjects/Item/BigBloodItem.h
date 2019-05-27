#ifndef BIG_BLOOD_ITEM
#define BIG_BLOOD_ITEM
#include "Items.h"

class BigBloodItem : public Items
{
public:
	BigBloodItem();
	~BigBloodItem();

	RECT GetBound() override;

	void Update(float dt) override;

	void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) override;

	void OnCollision(BaseObject* obj) override;

	Items::eItemType GetItemsType() override;
};

#endif // !BIG_BLOOD_ITEM
