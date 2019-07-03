#ifndef _BASE_OBJECT_H
#define _BASE_OBJECT_H

#include <vector>
#include "../../GameComponents/Camera.h"
#include "../../GameDefines/GameDefine.h"
using namespace std;
using namespace Enumerator;

class BaseObject
{
public:
	BaseObject();
	virtual ~BaseObject();

	struct CollisionReturn
	{
		bool isCollision;
		RECT regionCollision;
	};

	virtual void newObject();
	void checkTimeCollision(float collisionTime, Side_Collision side, BaseObject* other);
	virtual void update(float dt);
	virtual void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0.0f, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	// Control collision
	// When entity collide, this function will be called
	virtual void onCollision(Side_Collision side);
	virtual void onCollision(BaseObject* obj);
	virtual void onNoCollisionWithBottom();

	// SUB-FUNCTION
public:
	virtual RECT getBound();

	GVec3 getPosition() const;
	void setPosition(float x, float y);
	void setPosition(GVec2 pos);
	void setPosition(GVec3 pos);

	GVec3 getPositionStart() const;
	void setPositionStart(float x, float y);
	void setPositionStart(GVec2 pos);
	void setPositionStart(GVec3 pos);

	void addPosition(float x, float y);
	void addPosition(GVec2 pos);
	void addPosition(GVec3 pos);

	void setWidth(int width);
	float getWidth() const;

	void setHeight(int height);
	float getHeight() const;

	virtual void setHP(int hp);
	virtual int getHP() const;

	void setMaxHP(int hp);
	int getMaxHP() const;

	void setDamage(int dame);
	int getDamage() const;

	float getVx() const;
	void setVx(float vx);
	void addVx(float vx);

	float getVy() const;
	void setVy(float vy);
	void addVy(float vy);

	void setDraw(bool isDraw);
	bool getDraw() const;

	void setObjectType(Object_Type objectType);
	Object_Type getObjectType() const;

	void setReverse(bool reverse);
	bool getReverse() const;

	void setDie(bool die);
	bool getDie() const;

	vector<BaseObject*>* getListBullet();

	void setId(int id);
	int getId() const;

protected:
	// setting up the position of object
	virtual void onSetPosition(GVec3 pos);

	// The position of object
	float _posX, _posY, _startx, _starty;

	// The velocity of object
	float _vx, _vy;

	int _HP, _Damage, _MaxHP;

	// size of object
	float _width, _height;

	// allow to draw the sprite when the Camera contain Enemies
	bool _isAllowDraw;

	// Object type
	Object_Type _objectType;

	// List bullet
	vector<BaseObject*> _listBullet;

	// Check out direction face of object
	bool _isReverse;

	// Check out object die
	bool _isDie;

	// setting up identity for object
	int _id;

	// collision minimum time to coordinate x
	float _collision_time_min_x;

	// collision minimum time to coordinate y
	float _collision_time_min_y;

	// collision side to coordinate x
	Side_Collision _side_x;

	// collision side to coordinate x
	Side_Collision _side_y;

	BaseObject* _entity_x;
	BaseObject* _entity_y;
};

#endif // !ENTITIES_H
