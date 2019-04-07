#include "BeginScene.h"
#include "../GameDefines/GameDefine.h"
#include "../GameComponents/GameGlobal.h"
#include "../GameComponents/GameCollision.h"
#include "../GameObjects/Player/GameState/DieState/DieState.h"
#include "../GameComponents/Sound.h"

BeginScene::BeginScene()
{
	//BackGround
	mBackColor = 0x000000;
	AniBackGround = new Animation("Resources/Map/BackGround.png", 2, 1, 512, 256);
	AniBackGround->setPosition(128, 128);
	AniBackGround->setAnimation(0, 1);

	//Map
	pMap = new GameMap(Define::WORLD_MAP);
	gp = new GamePlayer();
	pMap->gp = gp;
	pMap->LoadMap();

	//Camera
	pCamera = new Camera(GameGlobal::getWidth(), GameGlobal::getHeight());
	//pCamera->setPosition(128, 800);

	pCamera->setPosition(825, 900);
	//camera->setPosition(1670, 420);
	//camera->setPosition(2245, 1175);
	//camera->setPosition(2900, 1175);
	//camera->setPosition(4735, 1175);
	//camera->setPosition(6000, 1940);
	//pCamera->setPosition(7560, 1940);
	pMap->setCamera(pCamera);

	//Player
	gp->SetPosition(pCamera->getPosition());

	//Other
	isboss = false;
	CurentRoom = { 0, 768, 768, 1024 };

	ListEntityOut.clear();
	List000.clear();
}

BeginScene::~BeginScene()
{
	delete pMap;
	delete pCamera;
	delete gp;
	delete AniBackGround;
}

void BeginScene::update(float dt)
{
	Sound::getInstance()->play("BlastHornet", true, 0);
	Sound::getInstance()->setVolume(90);
	//Get Object in Camera
	ListEntityOut.clear();
	ListEntityOut.swap(List000);
	pMap->getQuadTree()->getObjectsInCamera(ListEntityOut, pCamera->getBound());

	//Run KeyBoard play
	gp->handlerKeyBoard(keys, dt);

	//Check collision all object in camera
	checkCollision(dt);
	checkCameraAndWorldMap(dt);
	checkCameraAndEnemies();

	//Update Object
	pMap->update(dt);
	gp->Update(dt);
	for (auto& entity : ListEntityOut)
	{
		entity->Update(dt);
		if (GameCollision::IsCollision(entity->GetBound(), pCamera->getBound()) == true)
			List000.push_back(entity);
	}

	//Background
	if (gp->GetPosition().x > 2600 && gp->GetPosition().x < 5632)
		AniBackGround->setAnimation(1, 1);
	else
		AniBackGround->setAnimation(0, 1);

	AniBackGround->update(dt);
}

void BeginScene::draw()
{
	AniBackGround->draw();
	pMap->draw();
	gp->Draw(pCamera);
	for (auto& entity : ListEntityOut)
		entity->Draw(pCamera);
	pMap->draw1();
	gp->drawHP();
}

void BeginScene::onKeyDown(int keyCode)
{
	keys[keyCode] = true;
	gp->onKeyDown(keys, keyCode);
}

void BeginScene::onKeyUp(int keyCode)
{
	keys[keyCode] = false;
	gp->onKeyUp(keyCode);
}

void BeginScene::checkCameraAndWorldMap(float dt)
{
	if (isboss == true)
	{
		if (gp->GetBound().left < pCamera->getBound().left)
		{
			if (gp->GetVx() < 0)
				gp->SetVx(0);
		}
		else
		{
			if (gp->GetBound().right > CurentRoom.right)
			{
				if (gp->GetVx() > 0)
					gp->SetVx(0);
			}
		}
	}
	if (!GameCollision::pointCollision(gp->GetPosition().x, gp->GetPosition().y, CurentRoom))
	{
		bool noRoom = true;
		for (auto& Room : pMap->getListRoom())
			if (GameCollision::pointCollision(gp->GetPosition().x, gp->GetPosition().y, Room))
			{
				noRoom = false;
				nextRoom = Room;
				CurentRoom = Room;
				if (gp->GetPosition().x < (CurentRoom.left + (CurentRoom.right - CurentRoom.left) / 2))
				{
					if (pCamera->getBound().left < CurentRoom.left)
					{
						direction = 1;
						CurentRoom.left = pCamera->getBound().left;
					}
				}
				else if (gp->GetPosition().x > (CurentRoom.left + (CurentRoom.right - CurentRoom.left) / 2))
				{
					if (pCamera->getBound().right > CurentRoom.right)
					{
						direction = -1;
						CurentRoom.right = pCamera->getBound().right;
					}
				}
				break;
			}
		if (noRoom)
			gp->SetState(new DieState(gp->GetPlayerData()));
	}

	if (direction == 1)
	{
		CurentRoom.left += 300 * dt;
		if (CurentRoom.left >= nextRoom.left)
		{
			CurentRoom.left = nextRoom.left;
			direction = 0;
		}
	}
	else if (direction == -1)
	{
		CurentRoom.right -= 300 * dt;
		if (CurentRoom.right <= nextRoom.right)
		{
			CurentRoom.right = nextRoom.right;
			direction = 0;
		}
	}
	else
	{
		pCamera->setPosition(gp->GetPosition());
	}

	if (pCamera->getBound().left < CurentRoom.left)
		pCamera->setPosition(CurentRoom.left + pCamera->getWidth() / 2, pCamera->getPosition().y);
	else if (pCamera->getBound().right > CurentRoom.right)
		pCamera->setPosition(CurentRoom.right - pCamera->getWidth() / 2, pCamera->getPosition().y);

	if (pCamera->getBound().top < CurentRoom.top)
		pCamera->setPosition(pCamera->getPosition().x, CurentRoom.top + pCamera->getHeight() / 2);
	else if (pCamera->getBound().bottom > CurentRoom.bottom)
		pCamera->setPosition(pCamera->getPosition().x, CurentRoom.bottom - pCamera->getHeight() / 2);
}

void BeginScene::checkCameraAndEnemies()
{
	for (auto& entity : ListEntityOut)
	{
		if (entity->GetTag() == Entity::ENEMY)
		{
			if (gp->GetPosition().x > entity->GetPosition().x)
				entity->SetReverse(true);
			else
				entity->SetReverse(false);

			if (!GameCollision::IsCollision(pCamera->getBound(), entity->GetBound())
				&& !GameCollision::pointCollision(entity->getPositionStart().x, entity->getPositionStart().y, pCamera->getBound()))
			{
				entity->NewEntity();
			}
		}
	}
}

void BeginScene::checkCollision(float dt)
{
	//check boss and lock port
	isboss = false;
	for (auto& entity : ListEntityOut)
	{
		if (entity->GetTag() == Entity::BOSS)
		{
			if (entity->GetHP() > 0)
			{
				isboss = true;
				for (auto& obj : ListEntityOut)
				{
					if (obj->GetTag() == Entity::PORT)
					{
						if (obj->GetHP() == 0)
						{
							obj->SetHP(1);//HP = 1 Port closed
							break;
						}
					}
				}
			}
			else
			{
				for (auto& obj : ListEntityOut)
				{
					if (obj->GetTag() == Entity::PORT)
					{
						if (obj->GetHP() == 1)
						{
							obj->SetHP(0);//HP = 0 Port is ready
							break;
						}
					}
				}
			}
			break;
		}
	}

	//player with object
	checkCollision(gp, dt);
	for (auto& playerBullet : *gp->getPlayerBullet())
	{
		if (playerBullet->getExplosions())
			continue;
		for (auto& entity : ListEntityOut)
			checkCollision(entity, playerBullet, dt);
	}

	//object with object
	for (auto& entity : ListEntityOut)
	{
		checkCollision(entity, dt);

		//checkCollision Enemy and EnemyBullet
		if (entity->GetTag() == Entity::ENEMY || entity->GetTag() == Entity::BOSS)
		{
			for (auto& bullet : *entity->GetListBullet())
			{
				if (bullet->GetDie())
					continue;

				if (bullet->GetTag() == Entity::ITEM)
				{
					checkCollision(bullet, dt);
					checkCollision(gp, bullet, dt);
					continue;
				}

				checkCollision(gp, bullet, dt);

				std::vector<Entity*> listEntityStatic;
				pMap->getQuadTree()->getObjectsCollideAble(listEntityStatic, bullet->GetBound());

				for (auto& obj : listEntityStatic)
				{
					checkCollision(obj, bullet, dt);
				}
			}
		}
	}
}

void BeginScene::checkCollision(Entity * obj, float dt)
{
	for (auto& entity : ListEntityOut)
	{
		if (obj->id != entity->id)
			checkCollision(obj, entity, dt);
	}

	std::vector<Entity*> listEntityStatic;
	pMap->getQuadTree()->getObjectsCollideAble(listEntityStatic, obj->GetBound());

	for (auto& entity : listEntityStatic)
	{
		if (obj->id != entity->id)
		{
			if (obj->GetDie() || entity->GetDie())
				continue;

			D3DXVECTOR2 distance = GameCollision::Distance(obj, entity, dt);
			RECT broad = GameCollision::getBroad(obj->GetBound(), distance);

			if (GameCollision::IsCollision(broad, entity->GetBound()))
			{
				Entity::SideCollisions other_with_entity;
				float collision_time = GameCollision::SweptAABB(obj->GetBound(), entity->GetBound(), distance, other_with_entity);

				if (collision_time < 1.0f)
					obj->CheckTimeCollision(collision_time, other_with_entity, entity);
			}
		}
	}
}

void BeginScene::checkCollision(Entity * obj, Entity * other, float dt)
{
	if (obj->GetDie() || other->GetDie())
		return;

	D3DXVECTOR2 distance = GameCollision::Distance(obj, other, dt);
	RECT broad = GameCollision::getBroad(obj->GetBound(), distance);

	if (GameCollision::IsCollision(broad, other->GetBound()))
	{
		if (GameCollision::IsCollision(obj->GetBound(), other->GetBound()))
		{
			obj->OnCollision(other);
			other->OnCollision(obj);
			return;
		}
		Entity::SideCollisions other_with_entity;
		float collision_time = GameCollision::SweptAABB(obj->GetBound(), other->GetBound(), distance, other_with_entity);

		if (collision_time < 1.0f)
		{
			obj->OnCollision(other);
			other->OnCollision(obj);
		}
	}
}