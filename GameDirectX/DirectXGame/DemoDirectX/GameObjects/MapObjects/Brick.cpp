#include "Brick.h"
#include "../../GameComponents/GameGlobal.h"


bool Brick::_Init(D3DXVECTOR3 position)
{
    //mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), TimePerFrame());
	_BrickAnimation = new GameAnimation(FileName(), Row(), Column(), 32, 32, TimePerFrame());

    SetPosition(position);

    //Entity::SetWidth(mAnimation->GetWidth());
    //Entity::SetHeight(mAnimation->GetHeight());

	Entity::SetWidth(_BrickAnimation->GetWidth());
	Entity::SetHeight(_BrickAnimation->GetHeight());

    return true;
}

void Brick::_OnSetPosition(D3DXVECTOR3 pos)
{
   /* mAnimation->SetPosition(pos);*/
	_BrickAnimation->SetPosition(pos);
}

void Brick::Update(float dt)
{
   /* mAnimation->Update(dt);*/
	_BrickAnimation->Update(dt);
}

void Brick::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey) const
{
    //mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
	_BrickAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);

}

void Brick::Draw(D3DXVECTOR2 transform) const
{
    //mAnimation->Draw(D3DXVECTOR2(transform));
	_BrickAnimation->Draw(D3DXVECTOR2(transform));
}
