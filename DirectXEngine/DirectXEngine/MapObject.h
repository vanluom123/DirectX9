#ifndef _MAP_OBJECT_H
#define _MAP_OBJECT_H

#include <d3d9.h>
#include <d3dx9.h>

class MapObject
{
public:
	MapObject();
	~MapObject();

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	
	void Draw(D3DXVECTOR2 transform);

	void Update(float dt);
};

#endif