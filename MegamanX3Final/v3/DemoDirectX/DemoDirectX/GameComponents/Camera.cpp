#include "Camera.h"
#include "GameGlobal.h"

Camera::Camera(int width, int height)
{
	m_width = width;
	m_height = height;
	m_posWord = Gvec3Zero;
}

void Camera::SetPosition(float x, float y)
{
	SetPosition(GVec3((int)x, (int)y, 0));
}

void Camera::SetPosition(GVec3 pos)
{
	m_posWord.x = (int)pos.x;
	m_posWord.y = (int)pos.y;
}

GVec2 Camera::GetTrans() const
{
	int xT = (GameGlobal::GetWidth() / 2.0f) - m_posWord.x;
	int yT = (GameGlobal::GetHeight() / 2.0f) - m_posWord.y;

	GVec2 vec2Translation = GVec2((float)xT, (float)yT);

	return vec2Translation;
}

GVec3 Camera::GetPosition() const
{
	return m_posWord;
}

RECT Camera::GetBound() const
{
	RECT bound;

	bound.left = m_posWord.x - (m_width / 2.0f);
	bound.right = bound.left + m_width;
	bound.top = m_posWord.y - (m_height / 2.0f);
	bound.bottom = bound.top + m_height;

	return bound;
}