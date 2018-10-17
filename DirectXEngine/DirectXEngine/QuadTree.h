#ifndef _QUADTREE_H
#define _QUADTREE_H
#include <d3d9.h>
#include "Entity.h"
#include <vector>

class QuadTree
{
public:
	QuadTree(int level, RECT bound);
	~QuadTree();

	void Clear();
	void InsertEntity(Entity* entity);

	// Taking list Entities can happen collision. Return list the elements in collision range 
	void getEntitiesCollideAble(std::vector<Entity*> &entitiesOut, Entity* entity);

	void getAllEntities(std::vector<Entity*> &entitiesOut);

	int getTotalEntities();

	RECT Bound;

protected:
	QuadTree** Nodes;
	// List elements has a in collision range (Bound)
	std::vector<Entity*> mListEntity;

	/*
	 * Taking position of Entity
	 * 0: in child node TOP-LEFT
	 * 1: in child node TOP-RIGHT
	 * 2: in child node BOTTOM-LEFT
	 * 3: in child node BOTTOM-RIGHT
	 */
	int getIndex(RECT body);
	// Split node
	void Split();

	bool isContain(Entity* entity);
	// Level with node
	int mLevel;
};
#endif
