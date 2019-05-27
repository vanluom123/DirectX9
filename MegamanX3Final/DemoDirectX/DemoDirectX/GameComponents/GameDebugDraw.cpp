#include "GameDebugDraw.h"
#include "GameGlobal.h"

GameDebugDraw::GameDebugDraw()
{
    _spriteHandler = GameGlobal::GetSpriteHandler();
    _spriteHandler->GetDevice(&_ddv);
    D3DXCreateLine(_ddv, &_lineDraw);
    
    //set size cho line
    _lineDraw->SetWidth(1);

    //set mau cho line
    _color = D3DCOLOR_XRGB(255, 0, 0);
    
}

GameDebugDraw::~GameDebugDraw()
{}

void GameDebugDraw::Draw()
{}

void GameDebugDraw::SetLineSize(float width)
{
    _lineDraw->SetWidth(width);
}

void GameDebugDraw::DrawLine(GVec2 lines[], int count)
{
    _lineDraw->Begin();
    _lineDraw->Draw(lines, count, _color);
    _lineDraw->End();
}

void GameDebugDraw::DrawRect(RECT rect, Camera *camera)
 {

    GVec3 trans = Gvec3Zero;

    if (camera)
    {
        trans = GVec3(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2, 0) - camera->GetPosition();
    }    

    GVec2 lines[] = { GVec2(rect.left + trans.x, rect.top + trans.y),
                            GVec2(rect.right + trans.x, rect.top + trans.y), 
                            GVec2(rect.right + trans.x, rect.bottom + trans.y), 
                            GVec2(rect.left + trans.x, rect.bottom + trans.y), 
                            GVec2(rect.left + trans.x, rect.top + trans.y) };

    DrawLine(lines, 5);
}

void GameDebugDraw::SetColor(D3DCOLOR color)
{
    _color = color;
}