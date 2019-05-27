#ifndef CAMERA_H
#define CAMERA_H
#include "../GameDefines/GameDefine.h"

class Camera
{
public:
	Camera(int width, int height);

	//center of camera
	GVec3 GetPosition() const;
	void SetPosition(float x, float y);
	void SetPosition(GVec3 pos);

	GVec2 GetTrans() const;

	RECT GetBound() const;

	int GetWidth() const { return m_width; }
	void SetWidth(int val) { m_width = val; }

	int GetHeight() const { return m_height; }
	void SetHeight(int val) { m_height = val; }

private:
	int m_width, m_height;
	GVec3 m_posWord;
};

#endif // !CAMERA_H
