#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Camera.h"

class GameDebugDraw 
{
public:
    GameDebugDraw();
	~GameDebugDraw();

    void draw();
    void drawLine(GVec2 lines[], int count);
    void drawRect(RECT bound, Camera *camera = nullptr);

    //set width for line, default = 10
    void setLineSize(float width);
    void setColor(D3DCOLOR color);

private:
    LPD3DXSPRITE _DXSprite;
    LPDIRECT3DDEVICE9 _d3ddev;
    D3DCOLOR _color;
	LPD3DXLINE _lineDraw;

};


