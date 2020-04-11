#include "Camera.h"
#include "GameGlobal.h"
#include "GameCollision.h"
#include "QuadTree.h"
#include "../GameObjects/Entity/BaseObject.h"
#include "../GameObjects/Player/Player.h"
#include "GameMap.h"
#include "../GameObjects/Player/GameState/DieState/DieState.h"

Camera * Camera::s_instance = nullptr;

Camera * Camera::getInstance()
{
	if (!s_instance) s_instance = new Camera;
	return s_instance;
}

void Camera::release()
{
	delete s_instance;
	s_instance = nullptr;
}

void Camera::initialize(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;
	m_fPosWorld = Gvec3Zero;
}

void Camera::setPosition(float x, float y)
{
	setPosition(GVec3(int(x), int(y), 0));
}

void Camera::setPosition(GVec3 pos)
{
	m_fPosWorld.x = int(pos.x);
	m_fPosWorld.y = int(pos.y);
}

GVec2 Camera::getTrans() const
{
	int nXT = (GameGlobal::getInstance()->getWidth() / 2.0f) - m_fPosWorld.x;
	int nYT = (GameGlobal::getInstance()->getHeight() / 2.0f) - m_fPosWorld.y;

	GVec2 vec2Translation = GVec2(float(nXT), float(nYT));

	return vec2Translation;
}

GVec3 Camera::getPosition() const
{
	return m_fPosWorld;
}

RECT Camera::getBound() const
{
	RECT bound;
	bound.left = m_fPosWorld.x - (m_nWidth / 2.0f);
	bound.right = bound.left + m_nWidth;
	bound.top = m_fPosWorld.y - (m_nHeight / 2.0f);
	bound.bottom = bound.top + m_nHeight;
	return bound;
}

void Camera::checkViewportWithMapWorld(bool l_bIsBoss, RECT & l_rcCurrentRoom, RECT & l_rcNextRoom, int & l_nDirection, float l_fDeltaTime)
{
	if (l_bIsBoss)
	{
		if (Player::getInstance()->getBound().left < this->getBound().left)
		{
			if (Player::getInstance()->getVx() < 0)
				Player::getInstance()->setVx(0.0f);
		}
		else
		{
			if (Player::getInstance()->getBound().right > l_rcCurrentRoom.right)
			{
				if (Player::getInstance()->getVx() > 0)
					Player::getInstance()->setVx(0.0f);
			}
		}
	}

	if (GameCollision::getInstance()->pointCollision(Player::getInstance()->getPosition().x, Player::getInstance()->getPosition().y, l_rcCurrentRoom) == false)
	{
		bool l_bIsRoom = true;
		auto l_vRoom = GameMap::getInstance()->getListRoom();
		for (auto room : l_vRoom)
		{
			if (GameCollision::getInstance()->pointCollision(Player::getInstance()->getPosition().x, Player::getInstance()->getPosition().y, room) == true)
			{
				l_bIsRoom = false;
				l_rcNextRoom = room;
				l_rcCurrentRoom = room;

				auto l_nCenterX = l_rcCurrentRoom.left + (l_rcCurrentRoom.right - l_rcCurrentRoom.left) / 2;

				if (Player::getInstance()->getPosition().x < l_nCenterX)
				{
					if (this->getBound().left < l_rcCurrentRoom.left)
					{
						l_nDirection = 1;
						l_rcCurrentRoom.left = this->getBound().left;
					}
				}
				else
				{
					if (this->getBound().right > l_rcCurrentRoom.right)
					{
						l_nDirection = -1;
						l_rcCurrentRoom.right = this->getBound().right;
					}
				}
				break;
			}
		}
		if (l_bIsRoom)
			Player::getInstance()->setState(new DieState());
	}

	if (l_nDirection == 1)
	{
		l_rcCurrentRoom.left += 300 * l_fDeltaTime;
		if (l_rcCurrentRoom.left >= l_rcNextRoom.left)
		{
			l_rcCurrentRoom.left = l_rcNextRoom.left;
			l_nDirection = 0;
		}
	}
	else if (l_nDirection == -1)
	{
		l_rcCurrentRoom.right -= 300 * l_fDeltaTime;
		if (l_rcCurrentRoom.right <= l_rcNextRoom.right)
		{
			l_rcCurrentRoom.right = l_rcNextRoom.right;
			l_nDirection = 0;
		}
	}
	else
	{
		// Setting the position of Camera to the position of Player
		// When Player moved, Camera moved to Player
		this->setPosition(Player::getInstance()->getPosition());
	}

	if (this->getBound().left < l_rcCurrentRoom.left)
		this->setPosition(l_rcCurrentRoom.left + this->getWidth() / 2, this->getPosition().y);
	else if (this->getBound().right > l_rcCurrentRoom.right)
		this->setPosition(l_rcCurrentRoom.right - this->getWidth() / 2, this->getPosition().y);

	if (this->getBound().top < l_rcCurrentRoom.top)
		this->setPosition(this->getPosition().x, l_rcCurrentRoom.top + this->getHeight() / 2);
	else if (this->getBound().bottom > l_rcCurrentRoom.bottom)
		this->setPosition(this->getPosition().x, l_rcCurrentRoom.bottom - this->getHeight() / 2);
}

void Camera::checkViewportWithEnemies(std::vector<BaseObject *> l_vObjectOut)
{
	for (int i = 0; i < l_vObjectOut.size(); i++)
	{
		if (l_vObjectOut.at(i)->getObjectType() != Enumerator::Object_Type::ENEMY)
			continue;

		bool l_bIsReverse = (Player::getInstance()->getPosition().x > l_vObjectOut.at(i)->getPosition().x) ? true : false;
		l_vObjectOut.at(i)->setReverse(l_bIsReverse);

		if (!GameCollision::getInstance()->isNested(Camera::getInstance()->getBound(), l_vObjectOut.at(i)->getBound())
			&& !GameCollision::getInstance()->pointCollision(l_vObjectOut.at(i)->getPositionStart().x, l_vObjectOut.at(i)->getPositionStart().y, Camera::getInstance()->getBound()))
			l_vObjectOut.at(i)->newObject();
	}
}

Camera::Camera()
{ 
	m_nWidth = GameGlobal::getInstance()->getWidth();
	m_nHeight = GameGlobal::getInstance()->getHeight();
	m_fPosWorld = Gvec3Zero;
}
