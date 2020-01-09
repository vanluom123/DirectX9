#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include "Camera.h"
#include "../GameObjects/Entity/BaseObject.h"

class QuadTree
{
private:
	//thuc hien chia ra cac node
	void split(); 

	bool isContain(RECT r);

	//danh sach cac phan tu co trong vung va cham (Bound)
	std::vector<BaseObject*> _listObject;

	RECT _bound;

	//tuong ung voi so node
	int _level; 

	QuadTree** _node;

public:
	QuadTree(int level, RECT bound);
	~QuadTree();

	void clear();
	void insertObject(BaseObject *entity);

	int getTotalObject();
	void getAllObject(std::vector<BaseObject*> &EntityOut, RECT rect);
	void getObjectCollide(std::vector<BaseObject*> &EntityStatic, RECT rect);
	void getObjectCamera(std::vector<BaseObject*> &EntityOut, RECT rect);

	RECT getBound() const;
	int getLevel() const;
};