#include "DemoScene.h"
#include "../GameDefines/GameDefine.h"
#include "../GameComponents/GameGlobal.h"
#include "../GameComponents/GameCollision.h"

DemoScene::DemoScene()
{
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

	gp = new GamePlayer();

	gp->SetPosition((float)GameGlobal::GetWidth() / 2, (float)GameGlobal::GetHeight() / 2);
	gp->SetCamera(pCamera);
}

void DemoScene::Update(float dt)
{
	_IsCheckCollision();
	pMap->Update(dt);

	gp->HandleKeyboard(keys);
	gp->Update(dt);

	_CheckCameraAndWorldMap();
}

void DemoScene::Draw()
{
	pMap->Draw();
	gp->Draw();
}

void DemoScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;
	gp->OnKeyPressed(keyCode);
}

void DemoScene::OnKeyUp(int keyCode)
{
	keys[keyCode] = false;
	gp->OnKeyUp(keyCode);
}

void DemoScene::OnMouseDown(float x, float y)
{
}

void DemoScene::_CheckCameraAndWorldMap() const
{
	pCamera->SetPosition(gp->GetPosition());

	if (pCamera->GetBound().left < 0)
	{
		//The position of camera is now in the center
		//The position of camera hits the left of the real world
		pCamera->SetPosition((float)pCamera->GetWidth() / 2, pCamera->GetPosition().y);
		if (gp->GetBound().left < 0)
			gp->SetPosition((float)gp->GetWidth() / 2, gp->GetPosition().y);
	}

	if (pCamera->GetBound().right > pMap->GetWidth())
	{
		//The position of camera hits the right side of the real world
		pCamera->SetPosition(pMap->GetWidth() - (float)pCamera->GetWidth() / 2, pCamera->GetPosition().y);
		if (gp->GetBound().right > pMap->GetWidth())
			gp->SetPosition(pMap->GetWidth() - (float)gp->GetWidth() / 2, gp->GetPosition().y);
	}

	if (pCamera->GetBound().top < 0)
	{
		//Now. The position of camera hits the top of the real world
		pCamera->SetPosition(pCamera->GetPosition().x, pCamera->GetHeight() / 2.0f);
		if (gp->GetBound().top < 0)
			gp->SetPosition(gp->GetPosition().x, (float)gp->GetHeight() / 2);
	}

	if (pCamera->GetBound().bottom > pMap->GetHeight())
	{
		//Now. the position of camera hits the bottom of the real world
		pCamera->SetPosition(pCamera->GetPosition().x, pMap->GetHeight() - pCamera->GetHeight() / 2.0f);
		if (gp->GetBound().bottom > pMap->GetHeight())
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

	pMap->GetQuadTree()->getEntitiesCollideAble(listEntitiesCollision, gp);

	for (auto& i : listEntitiesCollision)
	{
		const auto r = GameCollision::RectAndRect(gp->GetBound(), i->GetBound());

		if (r.IsCollided)
		{
			//Get the Entity's collision side over the Player
			const auto entity_with_player = GameCollision::getSideCollision(gp, r);

			//Get the Player's collision side over the Entity
			const auto player_with_entity = GameCollision::getSideCollision(i, r);

			//Call to collision-handling function of Player and Entity
			gp->OnCollision(r, entity_with_player);
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
		gp->OnNoCollisionWithBottom();
}
