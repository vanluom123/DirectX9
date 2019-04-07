#include "Camera.h"
#include "GameGlobal.h"

Camera::Camera(int width, int height)
{
	setWidth(width);
	setHeight(height);

	mPositionWorld = D3DXVECTOR3(0, 0, 0);
}

void Camera::setPosition(float x, float y)
{
	setPosition(D3DXVECTOR3((int)x, (int)y, 0));
}

void Camera::setPosition(D3DXVECTOR3 pos)
{
	mPositionWorld.x = (int)pos.x;
	mPositionWorld.y = (int)pos.y;
}

D3DXVECTOR2 Camera::getTrans() const
{
	int xT = GameGlobal::getWidth() / 2.0f - mPositionWorld.x;
	int yT = GameGlobal::getHeight() / 2.0f - mPositionWorld.y;
	return { (float)xT, (float)yT};
}

D3DXVECTOR3 Camera::getPosition() const
{
	return mPositionWorld;
}

RECT Camera::getBound() const
{
	RECT r;

	r.left = mPositionWorld.x - getWidth() / 2.0f;
	r.right = r.left + getWidth();
	r.top = mPositionWorld.y - getHeight() / 2.0f;
	r.bottom = r.top + getHeight();

	return r;
}