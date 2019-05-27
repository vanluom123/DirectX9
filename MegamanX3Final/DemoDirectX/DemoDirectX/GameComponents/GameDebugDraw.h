#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Camera.h"

class GameDebugDraw 
{
public:
    GameDebugDraw();
	~GameDebugDraw();

    void Draw();
    void DrawLine(GVec2 lines[], int count);
    void DrawRect(RECT rect, Camera *camera = nullptr);
    //set do rong cua duong ve, mac dinh = 10
    void SetLineSize(float width);
    void SetColor(D3DCOLOR color);

private:
    LPD3DXSPRITE _spriteHandler;
    LPDIRECT3DDEVICE9 _ddv;
    D3DCOLOR _color;
	LPD3DXLINE _lineDraw;

};


