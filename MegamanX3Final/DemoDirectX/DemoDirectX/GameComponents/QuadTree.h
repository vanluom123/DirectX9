#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include "Camera.h"
#include "../GameObjects/Entity/Entity.h"

class QuadTree
{
protected:
	void split(); //thuc hien chia ra cac node
	bool isContain(RECT r);
	std::vector<Entity*> mListEntity; //danh sach cac phan tu co trong vung va cham (Bound)
	RECT Bound;
	int mLevel; //tuong ung voi so node
public:
	QuadTree();
	QuadTree(int level, RECT bound);
	~QuadTree();
	void Clear();
	void insertObject(Entity *entity);

	int getTotalObject();
	void getAllObject(std::vector<Entity*> &ObjectOut, RECT rect);
	void getObjectsCollideAble(std::vector<Entity*> &EntityStatic, RECT rect);
	void getObjectsInCamera(std::vector<Entity*> &EntityOut, RECT rect);
	RECT getBound() { return Bound; }
	int getLevel() { return mLevel; }
	std::vector<Entity*> *getListEntity() { return &mListEntity; }

	QuadTree **Nodes;

};