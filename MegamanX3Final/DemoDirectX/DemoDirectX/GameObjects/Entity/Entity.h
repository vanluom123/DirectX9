#ifndef ENTITIES_H
#define ENTITIES_H

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include "../../GameComponents/Camera.h"

class Entity
{
public:
	virtual ~Entity() = default;
	Entity();

	enum SideCollisions
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

	enum Tag
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

	virtual RECT GetBound();

	D3DXVECTOR3 GetPosition() {
		return { x, y, 0 };
	}

	void SetPosition(float x, float y) {
		SetPosition({ x, y });
	}

	void SetPosition(D3DXVECTOR2 pos) {
		SetPosition({ pos.x, pos.y, 0 });
	}

	void SetPosition(D3DXVECTOR3 pos) {
		this->x = pos.x; this->y = pos.y; OnSetPosition(pos);
	}

	D3DXVECTOR3 getPositionStart() {
		return{ startx, starty, 0 };
	}

	void SetPositionStart(float x, float y) {
		SetPositionStart({ x, y });
	}

	void SetPositionStart(D3DXVECTOR2 pos) {
		SetPositionStart({ pos.x, pos.y, 0 });
	}

	void SetPositionStart(D3DXVECTOR3 pos) {
		this->startx = pos.x; this->starty = pos.y; OnSetPosition(pos);
	}

	void AddPosition(float x, float y) {
		AddPosition({ x, y });
	}

	void AddPosition(D3DXVECTOR2 pos) {
		AddPosition({ pos.x, pos.y, 0 });
	}

	void AddPosition(D3DXVECTOR3 pos) {
		SetPosition(this->GetPosition() + pos);
	}

	void SetWidth(int width) { this->width = width; }
	int GetWidth() { return this->width; }

	void SetHeight(int height) { this->height = height; }
	int GetHeight() { return this->height; }

	void SetHP(int hp) { this->HP = hp; }
	int GetHP() { return this->HP; }

	void SetMaxHP(int hp) { this->MaxHP = hp; }
	int GetMaxHP() { return this->MaxHP; }

	void SetDamage(int dame) { this->Damage = dame; }
	int GetDamage() { return this->Damage; }

	float GetVx() { return this->vx; }
	void SetVx(float vx) { this->vx = vx; }
	void AddVx(float vx) { this->vx += vx; }

	float GetVy() { return this->vy; }
	void SetVy(float vy) { this->vy = vy; }
	void AddVy(float vy) { this->vy += vy; }

	void SetDraw(bool isDraw) { this->allowDraw = isDraw; }
	bool GetDraw() { return this->allowDraw; }

	void SetTag(Tag tags) { this->tag = tags; }
	Tag GetTag() { return this->tag; }

	void SetReverse(bool reverse) { isReverse = reverse; }
	bool GetReverse() { return isReverse; }

	void SetDie(bool die) { isDie = die; }
	bool GetDie() { return isDie; }

	virtual void NewEntity() {}

	void CheckTimeCollision(float collisionTime, SideCollisions side, Entity * other);

	virtual void Update(float dt);
	virtual void Draw(Camera * camera, RECT rect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), float angle = 0.0f, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) {};

	//Control collision
	//When entity collide, this function will be called
	virtual void OnCollision(SideCollisions side);
	virtual void OnCollision(Entity * obj);
	virtual void OnNoCollisionWithBottom();
	std::vector<Entity*>* GetListBullet();

	int id;

protected:

	//duoc goi khi set position cua Entity, dung cho ke thua
	virtual void OnSetPosition(D3DXVECTOR3 pos) { }

	//vi tri tam position x va y
	float x, y, startx, starty;

	//phan toc vx, vy
	float vx, vy;
	int HP, Damage, MaxHP;
	//size cua entity
	float width, height;

	float collisionTimeMinX;
	float collisionTimeMinY;

	bool allowDraw;	// allow to draw the sprite when the Camera contain Enemies

	SideCollisions sideX;
	SideCollisions sideY;
	Entity* entityX;
	Entity* entityY;
	Tag tag;

	std::vector<Entity*> listBullet;

	bool isReverse;
	bool isDie;
};

#endif // !ENTITIES_H
