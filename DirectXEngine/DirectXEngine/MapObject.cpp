#include "MapObject.h"



MapObject::MapObject()
{}


MapObject::~MapObject()
{}

void MapObject::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DCOLOR colorKey)
{}

void MapObject::Draw(D3DXVECTOR2 transform)
{
	Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), transform);
}

void MapObject::Update(float dt)
{}
