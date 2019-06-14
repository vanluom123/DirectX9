#ifndef ENTITIES_H
#define ENTITIES_H

#include <vector>
#include "../../GameComponents/Camera.h"

class BaseObject
{
public:
	BaseObject();

	enum eSideCollision
	{
		LEFT,
		RIGHT,
		TOP,
		BOTTOM,
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		NONE
	};

	enum eObjectType
	{
		ROCK_MAN,
		ROCK_MAN_BULLET,
		ENEMY,
		ENEMY_BULLET,
		BOSS,
		ELEVATOR,
		CONVEYOR,
		STATIC,
		PORT,
		THORN,
		BOX,
		ITEM,
		TAG_NONE
	};

	struct CollisionReturn
	{
		bool isCollision;
		RECT regionCollision;
	};

	virtual void newObject() {	}

	void checkTimeCollision(float collisionTime, eSideCollision side, BaseObject* other);

	virtual void update(float dt);

	virtual void draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0.0f, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) {  }

	// Control collision
	// When entity collide, this function will be called
	virtual void onCollision(eSideCollision side);
	virtual void onCollision(BaseObject* obj) {  }
	virtual void onNoCollisionWithBottom() {  }

	// SUB-FUNCTION
public:
	virtual RECT getBound();

	GVec3 getPosition() {
		return GVec3(_posX, _posY, 0.0f);
	}

	void setPosition(float x, float y) {
		setPosition(GVec2(x, y));
	}

	void setPosition(GVec2 pos) {
		setPosition(GVec3(pos.x, pos.y, 0.0f));
	}

	void setPosition(GVec3 pos) {
		this->_posX = pos.x;
		this->_posY = pos.y;
		onSetPosition(pos);
	}

	GVec3 getPositionStart() {
		return GVec3(this->_startx, this->_starty, 0);
	}

	void setPositionStart(float x, float y) {
		setPositionStart(GVec2(x, y));
	}

	void setPositionStart(GVec2 pos) {
		setPositionStart(GVec3(pos.x, pos.y, 0));
	}

	void setPositionStart(GVec3 pos) {
		this->_startx = pos.x;
		this->_starty = pos.y;
		onSetPosition(pos);
	}

	void addPosition(float x, float y) {
		addPosition(GVec2(x, y));
	}

	void addPosition(GVec2 pos) {
		addPosition(GVec3(pos.x, pos.y, 0));
	}

	void addPosition(GVec3 pos) {
		setPosition(this->getPosition() + pos);
	}

	void setWidth(int width) { this->_width = width; }
	int getWidth() { return this->_width; }

	void setHeight(int height) { this->_height = height; }
	int getHeight() { return this->_height; }

	void setHP(int hp) { this->_HP = hp; }
	int getHP() { return this->_HP; }

	void setMaxHP(int hp) { this->_MaxHP = hp; }
	int getMaxHP() { return this->_MaxHP; }

	void setDamage(int dame) { this->_Damage = dame; }
	int getDamage() { return this->_Damage; }

	float getVx() { return this->_vx; }
	void setVx(float vx) { this->_vx = vx; }
	void addVx(float vx) { this->_vx += vx; }

	float getVy() { return this->_vy; }
	void setVy(float vy) { this->_vy = vy; }
	void addVy(float vy) { this->_vy += vy; }

	void setDraw(bool isDraw) { this->_isAllowDraw = isDraw; }
	bool getDraw() { return this->_isAllowDraw; }

	void setObjectType(eObjectType objectType) { this->_objectType = objectType; }
	eObjectType getObjectType() { return this->_objectType; }

	void setReverse(bool reverse) { _isReverse = reverse; }
	bool getReverse() { return _isReverse; }

	void setDie(bool die) { _isDie = die; }
	bool getDie() { return _isDie; }

	std::vector<BaseObject*>* getListBullet() { return &_listBullet; }

	void setId(int id) { _id = id; }
	int getId() const { return _id; }

protected:
	// setting up the position of object
	virtual void onSetPosition(GVec3 pos) { }

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
	eObjectType _objectType;

	// List bullet
	std::vector<BaseObject*> _listBullet;

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
	eSideCollision _side_x;

	// collision side to coordinate x
	eSideCollision _side_y;

	BaseObject* _entity_x;
	BaseObject* _entity_y;
};

#endif // !ENTITIES_H
