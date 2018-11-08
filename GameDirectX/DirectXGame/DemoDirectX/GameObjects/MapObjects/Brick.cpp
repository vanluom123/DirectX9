#include "Brick.h"
#include "../../GameComponents/GameGlobal.h"


bool Brick::_Init(D3DXVECTOR3 position)
{
	_BrickAnimation = new GameAnimation(FileName(), Row(), Column(), 32, 32, TimePerFrame());

    setPosition(position);

	Entity::setWidth(_BrickAnimation->GetWidth());
	Entity::setHeight(_BrickAnimation->GetHeight());

    return true;
}

void Brick::onSetPosition(D3DXVECTOR3 pos)
{
	_BrickAnimation->SetPosition(pos);
}

void Brick::Update(float dt)
{
	_BrickAnimation->Update(dt);
}

void Brick::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey) const
{
	_BrickAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);

}

void Brick::Draw(D3DXVECTOR2 transform) const
{
	_BrickAnimation->Draw(D3DXVECTOR2(transform));
}
