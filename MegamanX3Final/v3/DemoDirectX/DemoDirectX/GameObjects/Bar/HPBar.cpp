#include "HPBar.h"

HPBar::HPBar(BaseObject::eObjectType tag)
{
	if (tag == BaseObject::OBJECT_ROCK_MAN)
	{
		m_Hpbar = new Sprite("Resources/Bar/0.png", RECT(), 14, 16);
		m_position.x = 26;
		m_position.y = 88;
	}
	else
	{
		m_Hpbar = new Sprite("Resources/Bar/1.png", RECT(), 14, 16);
		m_position.x = 230;
		m_position.y = 88;
	}

	m_noBlood = new Sprite("Resources/Bar/2.png", RECT(), 14, 2);
	m_blood = new Sprite("Resources/Bar/3.png", RECT(), 14, 2);
	m_top = new Sprite("Resources/Bar/4.png", RECT(), 14, 4);
}


HPBar::~HPBar()
{
	delete m_Hpbar;
	delete m_noBlood;
	delete m_blood;
	delete m_top;
}

void HPBar::draw(int Hp, int MaxHp)
{
	int HP = Hp;
	int MaxHP = MaxHp;
	GVec3 pos = m_position;

	m_Hpbar->Draw(pos);
	pos.y -= 9;
	while (MaxHP > 0)
	{
		if (HP > 0)
			m_blood->Draw(pos);
		else
			m_noBlood->Draw(pos);

		pos.y -= 2;
		HP--;
		MaxHP--;
	}
	m_top->Draw(pos);
}