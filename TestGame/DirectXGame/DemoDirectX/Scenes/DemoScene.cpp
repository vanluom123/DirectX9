#include "DemoScene.h"
#include "../GameDefines/GameDefine.h"
#include "../GameComponents/GameGlobal.h"
#include "../GameComponents/GameCollision.h"

DemoScene::DemoScene()
{
	pMap = nullptr;
	pCamera = nullptr;
	pPlayer = nullptr;

	DemoScene::LoadContent();
}

void DemoScene::LoadContent()
{
	//Set color for scene. Here is blue scene color 
	mBackColor = 0x54acd2;

	pMap = new GameMap(Define::WORLD_MAP);

	pCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	pCamera->SetPosition(GameGlobal::GetWidth() / 2.0f,
		pMap->GetHeight() - pCamera->GetHeight());

	pMap->SetCamera(pCamera);

	pPlayer = new Player();

	pPlayer->SetPosition(GameGlobal::GetWidth() / 2.0f, GameGlobal::GetHeight() / 2.0f);
	pPlayer->SetCamera(pCamera);
}

void DemoScene::Update(float dt)
{
	_IsCheckCollision();

	pMap->Update(dt);

	pPlayer->HandleKeyboard(keys);

	pPlayer->Update(dt);

	_CheckCameraAndWorldMap();
}

void DemoScene::Draw()
{
	pMap->Draw();

	pPlayer->Draw();
}

void DemoScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;

	pPlayer->OnKeyPressed(keyCode);
}

void DemoScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;

	pPlayer->OnKeyUp(keyCode);
}

void DemoScene::OnMouseDown(float x, float y)
{
}

void DemoScene::_CheckCameraAndWorldMap() const
{
	pCamera->SetPosition(pPlayer->GetPosition());

	if (pCamera->GetBound().left < 0)
	{
		//The position of camera is now in the center
		//The position of camera hits the left of the real world
		pCamera->SetPosition(pCamera->GetWidth() / 2.0f, pCamera->GetPosition().y);
		if (pPlayer->GetBound().left < 0)
		{
			pPlayer->SetPosition(pPlayer->GetWidth() / 2.0f, pPlayer->GetPosition().y);
		}
	}

	if (pCamera->GetBound().right > pMap->GetWidth())
	{
		//The position of camera hits the right side of the real world
		pCamera->SetPosition(pMap->GetWidth() - pCamera->GetWidth() / 2.0f, pCamera->GetPosition().y);
		if (pPlayer->GetBound().right > pMap->GetWidth())
		{
			pPlayer->SetPosition(pMap->GetWidth() - pPlayer->GetWidth() / 2.0f, pPlayer->GetPosition().y);
		}
	}

	if (pCamera->GetBound().top < 0)
	{
		//Now. The position of camera hits the top of the real world
		pCamera->SetPosition(pCamera->GetPosition().x, pCamera->GetHeight() / 2.0f);
		if(pPlayer->GetBound().top < 0)
		{
			pPlayer->SetPosition(pPlayer->GetPosition().x, pPlayer->GetHeight() / 2.0f);
		}
	}

	if (pCamera->GetBound().bottom > pMap->GetHeight())
	{
		//Now. the position of camera hits the bottom of the real world
		pCamera->SetPosition(pCamera->GetPosition().x, pMap->GetHeight() - pCamera->GetHeight() / 2.0f);
		if(pPlayer->GetBound().bottom > pMap->GetHeight())
		{
			//Layer has a die state
		}
	}
}

void DemoScene::_IsCheckCollision() const
{
	/*Used to check when mario does not stand on an object or stand over the left or right edge of the object that will translate FallingState.*/
	auto widthBottom = 0;

	vector<Entity*> listEntitiesCollision;

	pMap->GetQuadTree()->getEntitiesCollideAble(listEntitiesCollision, pPlayer);

	for (auto& i : listEntitiesCollision)
	{
		const auto r = GameCollision::RectAndRect(pPlayer->GetBound(), i->GetBound());

		if (r.IsCollided)
		{
			//Get the Entity's collision side over the Player
			const auto entity_with_player = GameCollision::getSideCollision(pPlayer, r);

			//Get the Player's collision side over the Entity
			const auto player_with_entity = GameCollision::getSideCollision(i, r);

			//Call to collision-handling function of Player and Entity
			pPlayer->OnCollision(r, entity_with_player);
			i->OnCollision(r, player_with_entity);

			//Does Player check out touch at the bottom???
			if (entity_with_player == Entity::Bottom || entity_with_player == Entity::BottomLeft
				|| entity_with_player == Entity::BottomRight)
			{
				//Check out the length that mario is touching at the bottom
				const int bot = r.RegionCollision.right - r.RegionCollision.left;

				if (bot > widthBottom)
					widthBottom = bot;
			}
		}
	}

	//If mario stands out from the edge then this will drop mario to the ground   
	if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
		pPlayer->OnNoCollisionWithBottom();
}
