#ifndef HPBAR_H
#define HPBAR_H
#include "../../GameComponents/Sprite.h"
#include "../../GameObjects/Entity/BaseObject.h"
class HPBar
{
protected:
	Sprite* m_Hpbar;
	Sprite* m_noBlood;
	Sprite* m_blood;
	Sprite* m_top;
	GVec3 m_position;
public:
	HPBar(BaseObject::eObjectType tag);
	~HPBar();

	void draw(int Hp, int MaxHp);
};


#endif // !HPBAR_H
