#include "Camera.h"
#include "GameGlobal.h"

Camera::Camera(int width, int height)
{
	_width = width;
	_height = height;
	_positionWorld = Gvec3Zero;
}

void Camera::SetPosition(float x, float y)
{
	SetPosition(GVec3((int)x, (int)y, 0));
}

void Camera::SetPosition(GVec3 pos)
{
	_positionWorld.x = (int)pos.x;
	_positionWorld.y = (int)pos.y;
}

GVec2 Camera::GetTrans() const
{
	int xT = GameGlobal::GetWidth() / 2.0f - _positionWorld.x;
	int yT = GameGlobal::GetHeight() / 2.0f - _positionWorld.y;
	return { (float)xT, (float)yT};
}

GVec3 Camera::GetPosition() const
{
	return _positionWorld;
}

RECT Camera::GetBound() const
{
	RECT r;

	r.left = _positionWorld.x - _width / 2.0f;
	r.right = r.left + _width;
	r.top = _positionWorld.y - _height / 2.0f;
	r.bottom = r.top + _height;

	return r;
}