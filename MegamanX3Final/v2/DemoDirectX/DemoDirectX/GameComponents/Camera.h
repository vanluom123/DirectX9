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

	int GetWidth() const { return _width; }
	void SetWidth(int val) { _width = val; }

	int GetHeight() const { return _height; }
	void SetHeight(int val) { _height = val; }

private:
	int _width, _height;
	GVec3 _posWorld;
};

#endif // !CAMERA_H
