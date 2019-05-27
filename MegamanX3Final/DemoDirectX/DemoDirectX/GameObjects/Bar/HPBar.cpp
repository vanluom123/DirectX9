#include "HPBar.h"

HPBar::HPBar(BaseObject::eObjectType tag)
{
	if (tag == BaseObject::ROCK_MAN)
	{
		Hpbar = new Sprite("Resources/Bar/0.png", RECT(), 14, 16);
		position.x = 26;
		position.y = 88;
	}
	else
	{
		Hpbar = new Sprite("Resources/Bar/1.png", RECT(), 14, 16);
		position.x = 230;
		position.y = 88;
	}

	noblood = new Sprite("Resources/Bar/2.png", RECT(), 14, 2);
	blood = new Sprite("Resources/Bar/3.png", RECT(), 14, 2);
	Top = new Sprite("Resources/Bar/4.png", RECT(), 14, 4);
}


HPBar::~HPBar()
{
	delete Hpbar;
	delete noblood;
	delete blood;
	delete Top;
}

void HPBar::draw(int Hp, int MaxHp)
{
	int HP = Hp;
	int MaxHP = MaxHp;
	GVec3 pos = position;

	Hpbar->Draw(pos);
	pos.y -= 9;
	while (MaxHP > 0)
	{
		if (HP > 0)
			blood->Draw(pos);
		else
			noblood->Draw(pos);

		pos.y -= 2;
		HP--;
		MaxHP--;
	}
	Top->Draw(pos);
}