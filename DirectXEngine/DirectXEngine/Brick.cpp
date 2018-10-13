#include "Brick.h"



Brick::Brick()
{}


Brick::~Brick()
{}

void Brick::Update(float dt)
{
	mAnimation->Update(dt);
}

void Brick::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle,
	D3DXVECTOR2 rotationCenter, D3DCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Brick::Draw(D3DXVECTOR2 trans)
{
	mAnimation->Draw(D3DXVECTOR2(trans));
}

void Brick::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
}

bool Brick::Init(D3DXVECTOR3 position)
{
	mAnimation = new Animation(FileName(), TotalFrame(), Row(), Columns(), SecondsPerFrame());

	mAnimation->SetPosition(position);

	Entity::SetWidth(mAnimation->GetWidth());
	Entity::SetHeight(mAnimation->GetHeight());

	return true;
}
