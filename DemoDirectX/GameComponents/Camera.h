#ifndef CAMERA_H
#define CAMERA_H
#include "../GameDefines/GameDefine.h"

class BaseObject;
class QuadTree;
class GameMap;
class Player;

class Camera
{
public:
	Camera(int width, int height);

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

	void checkViewportWithMapWorld(Player* pPlayer, GameMap* pGameMap, bool isBoss, RECT& currentRoom, RECT& nextRoom,
	                               int& direction, float dt);
	
private:
	int _width;
	int _height;
	GVec3 _posWorld;

	// List objects
	vector<BaseObject*> _listObject;
};

#endif // !CAMERA_H
