#ifndef HPBAR_H
#define HPBAR_H
#include "../../GameComponents/Sprite.h"
#include "../../GameObjects/Entity/BaseObject.h"

class HPBar
{
protected:
	Sprite* Hpbar;
	Sprite* noblood;
	Sprite* blood;
	Sprite* Top;
	GVec3 position;
public:
	HPBar(Object_Type tag);
	~HPBar();

	void draw(int Hp, int MaxHp);
};


#endif // !HPBAR_H
