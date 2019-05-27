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

	virtual void NewEntity() {}

	void CheckTimeCollision(float collisionTime, eSideCollision side, BaseObject* other);

	virtual void Update(float dt);
	virtual void Draw(Camera* camera, RECT rect = RECT(), GVec2 scale = GVec2(), float angle = 0.0f, GVec2 rotationCenter = GVec2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) {};

	//Control collision
	//When entity collide, this function will be called
	virtual void OnCollision(eSideCollision side);
	virtual void OnCollision(BaseObject* obj);
	virtual void OnNoCollisionWithBottom();

	// SUB-FUNCTION
public:
	virtual RECT GetBound();

	GVec3 GetPosition() {
		return GVec3(_posX, _posY, 0);
	}

	void SetPosition(float x, float y) {
		SetPosition(GVec2(x, y));
	}

	void SetPosition(GVec2 pos) {
		SetPosition(GVec3(pos.x, pos.y, 0));
	}

	void SetPosition(GVec3 pos) {
		this->_posX = pos.x;
		this->_posY = pos.y;
		OnSetPosition(pos);
	}

	GVec3 GetPositionStart() {
		return GVec3(this->_startx, this->_starty, 0);
	}

	void SetPositionStart(float x, float y) {
		SetPositionStart(GVec2(x, y));
	}

	void SetPositionStart(GVec2 pos) {
		SetPositionStart(GVec3(pos.x, pos.y, 0));
	}

	void SetPositionStart(GVec3 pos) {
		this->_startx = pos.x;
		this->_starty = pos.y;
		OnSetPosition(pos);
	}

	void AddPosition(float x, float y) {
		AddPosition(GVec2(x, y));
	}

	void AddPosition(GVec2 pos) {
		AddPosition(GVec3(pos.x, pos.y, 0));
	}

	void AddPosition(GVec3 pos) {
		SetPosition(this->GetPosition() + pos);
	}

	void SetWidth(int width) { this->_width = width; }
	int GetWidth() { return this->_width; }

	void SetHeight(int height) { this->_height = height; }
	int GetHeight() { return this->_height; }

	void SetHP(int hp) { this->_HP = hp; }
	int GetHP() { return this->_HP; }

	void SetMaxHP(int hp) { this->_MaxHP = hp; }
	int GetMaxHP() { return this->_MaxHP; }

	void SetDamage(int dame) { this->_Damage = dame; }
	int GetDamage() { return this->_Damage; }

	float GetVx() { return this->_vx; }
	void SetVx(float vx) { this->_vx = vx; }
	void AddVx(float vx) { this->_vx += vx; }

	float GetVy() { return this->_vy; }
	void SetVy(float vy) { this->_vy = vy; }
	void AddVy(float vy) { this->_vy += vy; }

	void SetDraw(bool isDraw) { this->_isAllowDraw = isDraw; }
	bool GetDraw() { return this->_isAllowDraw; }

	void SetObjectType(eObjectType objectType) { this->_objectType = objectType; }
	eObjectType GetObjectType() { return this->_objectType; }

	void SetReverse(bool reverse) { _isReverse = reverse; }
	bool GetReverse() { return _isReverse; }

	void SetDie(bool die) { _isDie = die; }
	bool GetDie() { return _isDie; }

	std::vector<BaseObject*>* GetListBullet();

	void SetId(int id);
	int GetId() const;

protected:

	//duoc goi khi set position cua Entity, dung cho ke thua
	virtual void OnSetPosition(GVec3 pos) { }

	//vi tri tam position x va y
	float _posX, _posY, _startx, _starty;

	//phan toc vx, vy
	float _vx, _vy;
	int _HP, _Damage, _MaxHP;
	//size cua entity
	float _width, _height;

	float _collisionTimeMinX;
	float _collisionTimeMinY;

	bool _isAllowDraw;	// allow to draw the sprite when the Camera contain Enemies

	eSideCollision _sideX;
	eSideCollision _sideY;
	BaseObject* _entityX;
	BaseObject* _entityY;
	eObjectType _objectType;

	std::vector<BaseObject*> _listBullet;

	bool _isReverse;
	bool _isDie;

	int _id;
};

#endif // !ENTITIES_H
