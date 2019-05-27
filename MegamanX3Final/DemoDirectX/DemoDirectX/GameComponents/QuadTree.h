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
	void Split(); 

	bool IsContain(RECT r);

	//danh sach cac phan tu co trong vung va cham (Bound)
	std::vector<BaseObject*> _listObject;

	RECT _bound;

	//tuong ung voi so node
	int _level; 

	QuadTree** _node;

public:
	QuadTree(int level, RECT bound);

	void Clear();
	void InsertObject(BaseObject *entity);

	int GetTotalObject();
	void GetAllObject(std::vector<BaseObject*> &ObjectOut, RECT rect);
	void GetObjectCollide(std::vector<BaseObject*> &EntityStatic, RECT rect);
	void GetObjectCamera(std::vector<BaseObject*> &EntityOut, RECT rect);

	RECT GetBound() { return _bound; }
	int GetLevel() { return _level; }
	std::vector<BaseObject*> *GetListObject() { return &_listObject; }
};