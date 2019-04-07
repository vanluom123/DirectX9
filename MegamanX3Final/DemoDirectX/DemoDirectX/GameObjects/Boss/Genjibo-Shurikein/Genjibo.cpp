#include "Genjibo.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/BigBloodItem.h"

Genjibo::Genjibo()
{
	tag = Tag::BOSS;
	allowDraw = false;
	timeStand = 0;
	timeMove = 0;
	posY = y;
	transY = 15;
	count = 0;
	MaxHP = 30;
	HP = MaxHP;
	Damage = 4;
	anim = new Animation(Define::GENJIBO_SHURIKEIN, 8, 17, 49, 49, 0.01f);
	animGenjinbo = new Animation(Define::SHURIKEN, 2, 2, 32, 68, 0.01f);
	animDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.05);
	sideGen = NONE;
	change = false;
	shurikeinState = Shurikein::STAND;
	SetState(Shurikein::APPEAR);
}


Genjibo::~Genjibo()
{
	delete anim;
	delete animGenjinbo;
	delete animDie;
}

RECT Genjibo::GetBound()
{
	RECT r;
	r.left = x - width / 2.0f;
	r.right = r.left + width;
	r.top = y - height / 2.0f;
	r.bottom = r.top + height;
	return r;
}

void Genjibo::Update(float dt)
{
	for (auto& bullet : listBullet)
		bullet->Update(dt);

	if (isDie == true)
	{
		if (animDie->getPause() == true)
			return;
		animDie->update(dt);
	}
	else
		anim->update(dt);

	animGenjinbo->update(dt);
	ManageState(dt);
	Entity::Update(dt);
}

void Genjibo::OnCollision(Entity * obj)
{
	if (obj->GetTag() == Tag::ROCK_MAN_BULLET)
	{
		HP -= 2;
		if (HP < 0)
		{
			isDie = true;
			SetState(Shurikein::DIE);

			auto* item = new BigBloodItem();
			listBullet.push_back(item);
			item->SetPosition(x, y);
			item->SetTag(Entity::ITEM);
			return;
		}

		if (shurikeinState == Shurikein::ATTACK_2 && currentState == GenjiboState::MOVE)
		{
			currentState = GenjiboState::JUMP;
			vy = Define::ENEMY_MIN_JUMP_VELOCITY;
		}
	}
}

void Genjibo::OnCollision(SideCollisions side)
{
	switch (shurikeinState)
	{
	case Shurikein::STAND:
		break;
	case Shurikein::ATTACK_1:
	{
		//Attack Around
		if (sideX == Entity::NONE && sideY != Entity::NONE)
		{
			change = true;
			if (vy > 0)
				sideGen = Entity::BOTTOM;
			else
				sideGen = Entity::TOP;
		}
		else if (sideX != Entity::NONE && sideY == Entity::NONE)
		{
			change = true;
			if (vx > 0)
				sideGen = Entity::RIGHT;
			else
				sideGen = Entity::LEFT;
		}
		else if (sideX != Entity::NONE && sideY != Entity::NONE && change)
		{
			change = false;
			if (sideGen == TOP || sideGen == BOTTOM)
				vy *= -1;
			else
				vx *= -1;
		}
		else if (sideX == Entity::NONE && sideY == Entity::NONE && change)
		{
			change = false;
			if (sideGen == TOP || sideGen == BOTTOM)
				vx *= -1;
			else
				vy *= -1;
		}
		break;
	}

	case Shurikein::ATTACK_2:
	case Shurikein::ATTACK_3:
	{
		if (side == Entity::BOTTOM)
			currentState = GenjiboState::MOVE;
		else
			if (side == Entity::LEFT || side == Entity::RIGHT)
				vx = -vx;
		break;
	}

	default:
		break;
	}
}

void Genjibo::Draw(Camera * camera, RECT r, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotate, D3DCOLOR color)
{
	if (shurikeinState == Shurikein::APPEAR)
	{
		animGenjinbo->setPosition(x, posY);
		animGenjinbo->draw(animGenjinbo->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
	}

	for (auto& bullet : listBullet)
		bullet->Draw(camera);

	if (allowDraw == false) return;

	if (isDie == true)
	{
		if (animDie->getPause() == true)
			return;
		animDie->setPosition(GetPosition());
		animDie->draw(animDie->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
	}
	else
	{
		anim->setPosition(GetPosition());
		anim->draw(anim->getPosition(), r, scale, camera->getTrans(), angle, rotate, color);
	}
}

void Genjibo::SetState(Shurikein keinState)
{
	if (shurikeinState == keinState)
		return;

	shurikeinState = keinState;

	switch (shurikeinState)
	{
	case Shurikein::APPEAR:
	{
		vx = 0;
		vy = 150;
		anim->setAnimation(1, 10, 0.05);
		animGenjinbo->setAnimation(0, 2, 0.05);
		posY = 920;
		break;
	}
	case Shurikein::STAND:
	{
		vx = 0;
		vy = 150;
		anim->setAnimation(7, 17, 0.005);
		break;
	}
	case Shurikein::ATTACK_1:
	{
		vx = -150;
		vy = 150;
		sideGen = Entity::BOTTOM;
		currentState = GenjiboState::NONE;
		anim->setAnimation(5, 10, 0.03);
		break;
	}
	case Shurikein::ATTACK_2:
	{
		currentState = GenjiboState::MOVE;
		anim->setAnimation(6, 10, 0.03);
		vx = -150;
		vy = 150;
		break;
	}
	case Shurikein::ATTACK_3:
	{
		currentState = GenjiboState::MOVE;
		anim->setAnimation(7, 17, 0.01);
		vx = -80;
		vy = 150;
		break;
	}
	case Shurikein::DIE:
		animDie->setAnimation(0, 8, 0.05, false);
		vx = 0;
		vy = 0;
		break;
	default:
		break;
	}

	width = anim->getWidth();
	height = anim->getHeight();
}

void Genjibo::ManageState(float dt)
{
	switch (shurikeinState)
	{
	case Shurikein::APPEAR:
	{
		if (posY >= y - 8)
		{
			posY = y - 8;
			if (animGenjinbo->getCurrentRow() != 1)
			{
				animGenjinbo->setAnimation(1, 2, 0.05);
				allowDraw = true;
			}
			timeMove += dt;
			if (timeMove > 2)
			{
				timeMove = 0;
				SetState(Shurikein::STAND);
				return;
			}
		}
		else
			posY += 100 * dt;

		break;
	}
	case Shurikein::STAND:
	{
		vx = 0;
		vy = 150;
		timeStand += dt;
		if (timeStand > 2.0f)
		{
			timeStand = 0.0f;
			int Num = count % 3;
			count++;
			if (Num == 0)
				SetState(Shurikein::ATTACK_1);
			else if (Num == 1)
				SetState(Shurikein::ATTACK_2);
			else
				SetState(Shurikein::ATTACK_3);
		}
		break;
	}
	case Shurikein::ATTACK_1:
	{
		timeMove += dt;
		if (timeMove > 6)
		{
			timeMove = 0;
			SetState(Shurikein::STAND);
			return;
		}
		break;
	}
	case Shurikein::ATTACK_2:
	case Shurikein::ATTACK_3:
	{
		timeMove += dt;
		if (timeMove > 6)
		{
			timeMove = 0;
			SetState(Shurikein::STAND);
			return;
		}
		switch (currentState)
		{
		case GenjiboState::MOVE:
			vy = 150;
			if (shurikeinState == Shurikein::ATTACK_3)
			{
				currentState = GenjiboState::JUMP;
				vy = Define::ENEMY_MIN_JUMP_VELOCITY;
				return;
			}
			break;
		case GenjiboState::JUMP:
		{
			AddVy(transY);
			if (vy > Define::ENEMY_MAX_JUMP_VELOCITY)
				vy = Define::ENEMY_MAX_JUMP_VELOCITY;
		}
		default:
			break;
		}
		break;
	}
	default:
		break;
	}

}
