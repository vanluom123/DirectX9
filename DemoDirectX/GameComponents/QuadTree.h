#pragma once

#include <d3d9.h>
#include <vector>
#include "../GameObjects/Entity/BaseObject.h"

class QuadTree
{
	//thuc hien chia ra cac node
	void split();

	bool isContain(RECT r);

	//danh sach cac phan tu co trong vung va cham (Bound)
	std::vector<BaseObject*> _listObject;

	RECT _bound;

	//tuong ung voi so node
	int _level;

	QuadTree** _node;


	QuadTree();
	QuadTree(int level, RECT bound);

	static QuadTree* s_instance;

public:
	~QuadTree();

	static QuadTree* getInstance();
	static void release();

	void initialize(int level, RECT bound);

	void clear();
	void insertObject(BaseObject* entity);
	void removeObject(BaseObject* pEntity);

	int getTotalObject();
	void getAllObject(std::vector<BaseObject*>& EntityOut, RECT rect);
	void getObjectCollide(std::vector<BaseObject*>& EntityStatic, RECT rect);
	void getObjectCamera(std::vector<BaseObject*>& EntityOut, RECT rect);

	RECT getBound() const;
	int getLevel() const;
};