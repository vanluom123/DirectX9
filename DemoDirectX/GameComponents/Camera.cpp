#include "Camera.h"
#include "GameGlobal.h"
#include "GameCollision.h"
#include "QuadTree.h"
#include "../GameObjects/Entity/BaseObject.h"
#include "../GameObjects/Player/Player.h"
#include "GameMap.h"
#include "../GameObjects/Player/GameState/DieState/DieState.h"
#include "../GameObjects/Entity/BaseObject.h"

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
	_width = width;
	_height = height;
	_posWorld = Gvec3Zero;
}

void Camera::setPosition(float x, float y)
{
	setPosition(GVec3(int(x), int(y), 0));
}

void Camera::setPosition(GVec3 pos)
{
	_posWorld.x = int(pos.x);
	_posWorld.y = int(pos.y);
}

GVec2 Camera::getTrans() const
{
	int xT = (GameGlobal::getInstance()->getWidth() / 2.0f) - _posWorld.x;
	int yT = (GameGlobal::getInstance()->getHeight() / 2.0f) - _posWorld.y;

	GVec2 vec2Translation = GVec2(float(xT), float(yT));

	return vec2Translation;
}

GVec3 Camera::getPosition() const
{
	return _posWorld;
}

RECT Camera::getBound() const
{
	RECT bound;
	bound.left = _posWorld.x - (_width / 2.0f);
	bound.right = bound.left + _width;
	bound.top = _posWorld.y - (_height / 2.0f);
	bound.bottom = bound.top + _height;
	return bound;
}

void Camera::checkViewportWithMapWorld(bool isBoss, RECT & currentRoom, RECT & nextRoom, int & direction, float dt)
{
	if (isBoss)
	{
		if (Player::getInstance()->getBound().left < this->getBound().left)
		{
			if (Player::getInstance()->getVx() < 0)
				Player::getInstance()->setVx(0.0f);
		}
		else
		{
			if (Player::getInstance()->getBound().right > currentRoom.right)
			{
				if (Player::getInstance()->getVx() > 0)
					Player::getInstance()->setVx(0.0f);
			}
		}
	}

	if (GameCollision::getInstance()->pointCollision(Player::getInstance()->getPosition().x, Player::getInstance()->getPosition().y, currentRoom) == false)
	{
		bool is_room = true;
		for (auto room : GameMap::getInstance()->getListRoom())
		{
			if (GameCollision::getInstance()->pointCollision(Player::getInstance()->getPosition().x, Player::getInstance()->getPosition().y, room) == true)
			{
				is_room = false;
				nextRoom = room;
				currentRoom = room;

				auto centerX = currentRoom.left + (currentRoom.right - currentRoom.left) / 2;

				if (Player::getInstance()->getPosition().x < centerX)
				{
					if (this->getBound().left < currentRoom.left)
					{
						direction = 1;
						currentRoom.left = this->getBound().left;
					}
				}
				else
				{
					if (this->getBound().right > currentRoom.right)
					{
						direction = -1;
						currentRoom.right = this->getBound().right;
					}
				}
				break;
			}
		}
		if (is_room)
			Player::getInstance()->setState(new DieState());
	}

	if (direction == 1)
	{
		currentRoom.left += 300 * dt;
		if (currentRoom.left >= nextRoom.left)
		{
			currentRoom.left = nextRoom.left;
			direction = 0;
		}
	}
	else if (direction == -1)
	{
		currentRoom.right -= 300 * dt;
		if (currentRoom.right <= nextRoom.right)
		{
			currentRoom.right = nextRoom.right;
			direction = 0;
		}
	}
	else
	{
		// Setting the position of Camera to the position of Player
		// When Player moved, Camera moved to Player
		this->setPosition(Player::getInstance()->getPosition());
	}

	if (this->getBound().left < currentRoom.left)
		this->setPosition(currentRoom.left + this->getWidth() / 2, this->getPosition().y);
	else if (this->getBound().right > currentRoom.right)
		this->setPosition(currentRoom.right - this->getWidth() / 2, this->getPosition().y);

	if (this->getBound().top < currentRoom.top)
		this->setPosition(this->getPosition().x, currentRoom.top + this->getHeight() / 2);
	else if (this->getBound().bottom > currentRoom.bottom)
		this->setPosition(this->getPosition().x, currentRoom.bottom - this->getHeight() / 2);
}

void Camera::checkViewportWithEnemies(std::vector<BaseObject *> listEntityOut)
{
	for (int i = 0; i < listEntityOut.size(); i++)
	{
		if (listEntityOut.at(i)->getObjectType() != Enumerator::Object_Type::ENEMY)
			continue;

		bool isReverse = (Player::getInstance()->getPosition().x > listEntityOut.at(i)->getPosition().x) ? true : false;
		listEntityOut.at(i)->setReverse(isReverse);

		if (!GameCollision::getInstance()->isNested(Camera::getInstance()->getBound(), listEntityOut.at(i)->getBound())
			&& !GameCollision::getInstance()->pointCollision(listEntityOut.at(i)->getPositionStart().x, listEntityOut.at(i)->getPositionStart().y, Camera::getInstance()->getBound()))
			listEntityOut.at(i)->newObject();
	}
}

Camera::Camera()
{ 
	_width = GameGlobal::getInstance()->getWidth();
	_height = GameGlobal::getInstance()->getHeight();
	_posWorld = Gvec3Zero;
}
