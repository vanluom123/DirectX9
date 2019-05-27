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
	std::vector<BaseObject*> m_listObject;

	RECT m_bound;

	//tuong ung voi so node
	int m_level; 

	QuadTree** m_node;

public:
	QuadTree(int level, RECT bound);
	~QuadTree();

	void Clear();
	void InsertObject(BaseObject *entity);

	int GetTotalObject();
	void GetAllObject(std::vector<BaseObject*> &ObjectOut, RECT rect);
	void GetObjectCollide(std::vector<BaseObject*> &EntityStatic, RECT rect);
	void GetObjectCamera(std::vector<BaseObject*> &EntityOut, RECT rect);

	RECT GetBound() const;
	int GetLevel() const;
	std::vector<BaseObject*>* GetListObject();
};