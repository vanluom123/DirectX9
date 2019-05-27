#include "Planet.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Player/GameState/StandState/StandState.h"

Planet::Planet(Player* gp)
{
	m_pixton = new Pixton();
	m_anim = new Animation("Resources/Enemies/CarryArm/x3_subboss_carryarm_01.png", 1, 1, 256, 88);
	m_animAttack = new Animation("Resources/Enemies/CarryArm/attack.png", 2, 10, 32, 32);
	m_animBullet = new Animation("Resources/Enemies/CarryArm/bullet.png", 1, 3, 16, 16);
	m_animAttack->SetAnimation(0, 1);
	m_animAttack->SetPause(1);
	m_animBullet->SetAnimation(0, 3, 0.1);

	m_HP = 1;
	m_Damage = 3;
	m_planetPosY = 0;
	m_planetPosX = 0;
	m_isMove = true;
	m_rockMan = gp;
	m_carryArm = new CarryArm();
	m_box1 = new Box();
	m_box2 = new Box();
	m_box1->SetObjectType(OBJECT_ENEMY);
	m_box2->SetObjectType(OBJECT_ENEMY);
	m_box1->SetDie(true);
	m_box2->SetDie(true);
	m_isAttack = false;
	m_timeAttack = 0;
}

Planet::~Planet()
{
	delete m_anim;
	delete	m_animAttack;
	delete	m_animBullet;
	delete m_pixton;
	delete m_carryArm;
	delete m_box1;
	delete m_box2;
}

void Planet::Draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	if (m_isAllowDraw)
	{
		m_pixton->Draw(camera);

		m_animBullet->Draw(m_animBullet->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);

		m_anim->SetPosition(GetPosition());
		m_anim->Draw(m_anim->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);

		m_animAttack->SetPosition(m_posX - 40, m_posY + 32);
		m_animAttack->Draw(m_animAttack->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);

		m_carryArm->Draw(camera);
		m_box1->Draw(camera);
		m_box2->Draw(camera);
	}
}

RECT Planet::GetBound()
{
	RECT bound;
	bound.left = m_posX + m_width / 4;
	bound.right = m_posX + m_width / 2;
	bound.top = m_posY - m_height / 2;
	bound.bottom = m_posY + m_height / 2;

	return bound;
}
void Planet::Update(float gameTime)
{
	if (m_isAllowDraw)
	{
		m_pixton->Update(gameTime);
		m_anim->Update(gameTime);
		m_animAttack->Update(gameTime);
		m_animBullet->Update(gameTime);

		MoveDown(gameTime);
		///Update
		m_box1->Update(gameTime);
		m_box2->Update(gameTime);
		m_carryArm->Update(gameTime);
	}
}

void Planet::MoveDown(float gameTime)
{
	if (m_isMove)
	{
		m_rockMan->SetState(new StandState(m_rockMan->GetPlayerData()));
		m_rockMan->SetLock(true);
		m_posY += 40 * gameTime;
		if (m_posY > m_starty)
		{
			m_posY = m_starty;
			m_isMove = m_pixton->MoveDown(gameTime, m_posX, m_posY);
			if (m_isMove)
			{
				m_timeplay = 30;
				m_box1->SetPositionStart(m_posX + 32, m_posY - m_height);
				m_box2->SetPositionStart(m_posX + 88, m_posY - m_height);
				m_carryArm->SetPositionStart(m_posX + 160, m_posY + m_height);
			}
		}
	}
	else
	{
		//Check EndGame
		m_timeplay -= gameTime;
		if (m_timeplay < 0 && m_box1->GetDie() && m_box2->GetDie())
		{
			if (!m_pixton->MoveUp(gameTime, m_posX, m_posY))
				m_posY -= 40 * gameTime;

			m_rockMan->SetState(new StandState(m_rockMan->GetPlayerData()));
			m_rockMan->SetLock(true);
			return;
		}

		//Planet attack when have 2 box on the pixton
		if (m_box1->GetBottom() && m_box2->GetBottom())
		{
			if (!m_isAttack && m_animAttack->GetPause())
			{
				m_isAttack = true;
				m_animAttack->SetAnimation(0, 10, 0.15, false);
			}
		}

		if (m_isAttack && m_animAttack->GetPause())
		{
			m_planetPosY += 50 * gameTime;
			if (m_rockMan->GetPosition().x > m_animBullet->GetPosition().x)
				m_planetPosX += 20 * gameTime;
			else
				m_planetPosX -= 20 * gameTime;

			if (m_planetPosY > 76)
			{
				m_planetPosY = 76;
				if (m_rockMan->GetPosition().x > m_animAttack->GetPosition().x)
					m_planetPosX += 150 * gameTime;
				else
					m_planetPosX -= 150 * gameTime;

				m_timeAttack += gameTime;
				if (m_timeAttack > 0.2)
				{
					m_planetPosY = 0;
					m_planetPosX = 0;
					m_isAttack = false;
					m_animAttack->SetAnimation(1, 10, 0.15, false);
					m_animBullet->SetPosition(0, 0);
					m_timeAttack = 0;
				}
			}

			m_animBullet->SetPosition(m_animAttack->GetPosition().x + m_planetPosX, m_posY + 48 + m_planetPosY);

			BaseObject * e = new BaseObject();
			e->SetPosition(m_animBullet->GetPosition());
			e->SetHeight(16);
			e->SetWidth(16);
			e->SetDamage(3);
			e->SetObjectType(BaseObject::OBJECT_ENEMY_BULLET);

			if (GameCollision::IsCollision(e->GetBound(), m_rockMan->GetBound()))
				m_rockMan->OnCollision(e);

			delete e;
		}
		else
			m_animBullet->SetPosition(0, 0);

		//Select Box
		if (m_carryArm->GetState() == CarryArm::CARRY_ARM_STAND)
		{
			if (m_box1->GetDie())
			{
				m_box1->NewEntity();
				m_box1->SetVy(80);
				m_carryArm->SetPosition(m_posX + 32, m_posY - m_height - 48);
				m_carryArm->SetState(CarryArm::CARRY_ARM_MOVE_DOWN);
			}
			else if (m_box2->GetDie())
			{
				m_box2->NewEntity();
				m_box2->SetVy(80);
				m_carryArm->SetPosition(m_posX + 88, m_posY - m_height - 48);
				m_carryArm->SetState(CarryArm::CARRY_ARM_MOVE_DOWN);
			}
		}

		///Box Collision with pixton
		if (GameCollision::IsCollision(m_box1->GetBound(), m_pixton->GetBound()))
		{
			m_box1->SetPosition(m_posX + 32, m_pixton->GetBound().top - 25);
			m_box1->SetVy(0);
			m_box1->SetBottom(true);
			m_carryArm->SetState(CarryArm::CARRY_ARM_EVENT_MOVE_UP_2);
		}
		if (GameCollision::IsCollision(m_box2->GetBound(), m_pixton->GetBound()))
		{
			m_box2->SetPosition(m_posX + 88, m_pixton->GetBound().top - 25);
			m_box2->SetVy(0);
			m_box2->SetBottom(true);
			m_carryArm->SetState(CarryArm::CARRY_ARM_EVENT_MOVE_UP_2);
		}

		///Box Collision with rockman
		if (!m_box1->GetDie())
			if (GameCollision::IsCollision(m_box1->GetBound(), m_rockMan->GetBound()))
				m_rockMan->OnCollision(m_box1);
		if (!m_box2->GetDie())
			if (GameCollision::IsCollision(m_box2->GetBound(), m_rockMan->GetBound()))
				m_rockMan->OnCollision(m_box2);

		///Box Collision with rockmanBullet
		for (auto& rockmanBullet : *m_rockMan->GetPlayerBullet())
		{
			if (rockmanBullet->GetExplosion())
				continue;

			if (!m_box1->GetDie())
			{
				if (GameCollision::IsCollision(m_box1->GetBound(), rockmanBullet->GetBound()))
				{
					m_box1->OnCollision(rockmanBullet);
					rockmanBullet->OnCollision(m_box1);
				}
			}
			if (!m_box2->GetDie())
			{
				if (GameCollision::IsCollision(m_box2->GetBound(), rockmanBullet->GetBound()))
				{
					m_box2->OnCollision(rockmanBullet);
					rockmanBullet->OnCollision(m_box2);
				}
			}
		}
	}
}
