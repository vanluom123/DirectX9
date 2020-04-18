#ifndef CAMERA_H
#define CAMERA_H
#include "../GameDefines/GameDefine.h"

class BaseObject;

class Camera
{
public:
	~Camera() = default;

	static Camera* getInstance();
	static void release();

	void initialize(int width, int height);

	//center of camera
	GVec3 getPosition() const;
	void setPosition(float x, float y);
	void setPosition(GVec3 pos);

	GVec2 getTrans() const;

	RECT getBound() const;

	int getWidth() const { return m_nWidth; }
	void setWidth(int val) { m_nWidth = val; }

	int getHeight() const { return m_nHeight; }
	void setHeight(int val) { m_nHeight = val; }

	void checkMapWorld(bool bIsBoss, RECT& rcCurrentRoom, RECT& rcNextRoom,
					   int& nDirection, float fDeltaTime);

	void checkEnemies(std::vector<BaseObject*> l_vObjectOut);

private:
	Camera();
	static Camera* s_instance;

	int m_nWidth;
	int m_nHeight;
	GVec3 m_fPosWorld;
};

#endif // !CAMERA_H
