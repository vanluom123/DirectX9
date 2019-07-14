#include "GameDebugDraw.h"
#include "GameGlobal.h"

GameDebugDraw::GameDebugDraw()
{
    _DXSprite = GameGlobal::getDXSprite();
    _DXSprite->GetDevice(&_d3ddev);
    D3DXCreateLine(_d3ddev, &_lineDraw);
    
    //set size for line
    _lineDraw->SetWidth(1);

    //set color for line
    _color = D3DCOLOR_XRGB(255, 0, 0);
    
}

GameDebugDraw::~GameDebugDraw()
{
	// Do nothing
}

void GameDebugDraw::draw()
{
	// Do nothing
}

void GameDebugDraw::setLineSize(float width)
{
    _lineDraw->SetWidth(width);
}

void GameDebugDraw::drawLine(GVec2 lines[], int count)
{
    _lineDraw->Begin();
    _lineDraw->Draw(lines, count, _color);
    _lineDraw->End();
}

void GameDebugDraw::drawRect(RECT bound, Camera *camera)
 {
    GVec3 trans = Gvec3Zero;

    if (camera)
		trans = GVec3(GameGlobal::getWidth() / 2, GameGlobal::getHeight() / 2, 0) - camera->getPosition();

    GVec2 lines[] = { GVec2(bound.left + trans.x, bound.top + trans.y),
                            GVec2(bound.right + trans.x, bound.top + trans.y), 
                            GVec2(bound.right + trans.x, bound.bottom + trans.y), 
                            GVec2(bound.left + trans.x, bound.bottom + trans.y), 
                            GVec2(bound.left + trans.x, bound.top + trans.y) };

    drawLine(lines, 5);
}

void GameDebugDraw::setColor(D3DCOLOR color)
{
    _color = color;
}