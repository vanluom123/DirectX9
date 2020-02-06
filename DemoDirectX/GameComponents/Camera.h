#ifndef CAMERA_H
#define CAMERA_H
#include "../GameDefines/GameDefine.h"

class BaseObject;

class Camera
{
public:
	~Camera() = default;

	static Camera * getInstance();
	static void release();

	void initialize(int width, int height);

	//center of camera
	GVec3 getPosition() const;
	void setPosition(float x, float y);
	void setPosition(GVec3 pos);

	GVec2 getTrans() const;

	RECT getBound() const;

	int getWidth() const { return _width; }
	void setWidth(int val) { _width = val; }

	int getHeight() const { return _height; }
	void setHeight(int val) { _height = val; }

	void checkViewportWithMapWorld(bool isBoss, RECT & currentRoom, RECT & nextRoom,
								   int & direction, float dt);

	void checkViewportWithEnemies(std::vector<BaseObject *> listEntityOut);

private:
	Camera();
	static Camera * s_instance;

	int _width;
	int _height;
	GVec3 _posWorld;
};

#endif // !CAMERA_H
