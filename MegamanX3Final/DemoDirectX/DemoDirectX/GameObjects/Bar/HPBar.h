#ifndef HPBAR_H
#define HPBAR_H
#include "../../GameComponents/Sprite.h"
#include "../../GameObjects/Entity/Entity.h"
class HPBar
{
protected:
	Sprite* Hpbar;
	Sprite* noblood;
	Sprite* blood;
	Sprite* Top;
	D3DXVECTOR3 position;
public:
	HPBar(Entity::Tag tag);
	~HPBar();

	void draw(int Hp, int MaxHp);
};


#endif // !HPBAR_H
