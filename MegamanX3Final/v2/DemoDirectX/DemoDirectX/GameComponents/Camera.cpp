#include "Camera.h"
#include "GameGlobal.h"

Camera::Camera(int width, int height)
{
	_width = width;
	_height = height;
	_posWorld = Gvec3Zero;
}

void Camera::SetPosition(float x, float y)
{
	SetPosition(GVec3((int)x, (int)y, 0));
}

void Camera::SetPosition(GVec3 pos)
{
	_posWorld.x = (int)pos.x;
	_posWorld.y = (int)pos.y;
}

GVec2 Camera::GetTrans() const
{
	int xT = (GameGlobal::GetWidth() / 2.0f) - _posWorld.x;
	int yT = (GameGlobal::GetHeight() / 2.0f) - _posWorld.y;

	GVec2 vec2Translation = GVec2((float)xT, (float)yT);

	return vec2Translation;
}

GVec3 Camera::GetPosition() const
{
	return _posWorld;
}

RECT Camera::GetBound() const
{
	RECT bound;

	bound.left = _posWorld.x - (_width / 2.0f);
	bound.right = bound.left + _width;
	bound.top = _posWorld.y - (_height / 2.0f);
	bound.bottom = bound.top + _height;

	return bound;
}