#include "QuadTree.h"

QuadTree::QuadTree(int level, RECT bound): Nodes(NULL)
{
	this->Bound = bound;
	this->mLevel = level;
}

QuadTree::~QuadTree()
{}

void QuadTree::Clear()
{
	if(Nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if(Nodes[i])
			{
				Nodes[i]->Clear();
				delete Nodes[i];
				Nodes[i] = NULL;
			}
		}

		delete[] Nodes;
	}
}

void QuadTree::InsertEntity(Entity* entity)
{
	int index = getIndex(entity->GetBound());

	// Neu node cha ton tai thi insert vao node con
	if(Nodes != NULL)
	{
		if(index != -1)
		{
			Nodes[index]->InsertEntity(entity);
			return;
		}
	}

	// Luc nay entity nam giua 2 bound nen se duoc add vao luon
	if (index == -1)
		mListEntity.push_back(entity);
	else
	{
		// Node chua duoc tao nen se tao va split roi moi insert
		if (Nodes == NULL)
			Split();

		Nodes[index]->InsertEntity(entity);
	}
}

void QuadTree::getEntitiesCollideAble(std::vector<Entity*>& entitiesOut, Entity* entity)
{
	int index = this->getIndex(entity->GetBound());

	if (index != -1)
	{
		// Nhung Entity o day se la nam tren 2 node con nen chung ta cung se lay de set va cham
		for (auto child : mListEntity)
			entitiesOut.push_back(child);

		if (Nodes != NULL)
		{
			// Kiem tra va lay cac node trong node con
			Nodes[index]->getEntitiesCollideAble(entitiesOut, entity);
		}
	}
	else getAllEntities(entitiesOut);
}

void QuadTree::getAllEntities(std::vector<Entity*>& entitiesOut)
{
	for (auto child : mListEntity)
		entitiesOut.push_back(child);

	if(Nodes)
	{
		for (size_t i = 0; i < 4; i++)
			Nodes[i]->getAllEntities(entitiesOut);
	}
}

int QuadTree::getTotalEntities()
{
	int total = mListEntity.size();

	if(Nodes)
	{
		for (size_t i = 0; i < 4; i++)
			total += Nodes[i]->getTotalEntities();
	}

	return total;
}

int QuadTree::getIndex(RECT body)
{
	/*lay vi tri cua Entity
	0: nam trong Node con goc trai tren
	1: nam trong Node con goc phai tren
	2: nam trong Node con goc trai duoi
	3: nam trong Node con goc phai duoi
	-1: bi dinh > 2 node con*/

	float middleVertical = Bound.left + (Bound.right - Bound.left) / 2.0f;
	float middleHorizontal = Bound.top - (Bound.top - Bound.bottom) / 2.0f;

	if(body.top < Bound.top && body.bottom > middleHorizontal)
	{
		// Nam o phia tren
		if(body.left > Bound.left && body.right < middleVertical)
		{
			// Nam o phia ben trai
			return 0;
		}
		if(body.left > middleVertical && body.right < Bound.right )
		{
			// Nam o phia ben phai
			return 1;
		}
	}
	if(body.top < middleHorizontal && body.bottom > Bound.bottom)
	{
		// Nam o phia duoi
		if(body.left > Bound.left && body.right < middleVertical)
		{
			// Nam o phia ben trai
			return 2;
		}
		if(body.left > middleVertical && body.right < Bound.right)
		{
			// Nam o phia ben phai
			return 3;
		}
	}

	return -1;
}

void QuadTree::Split()
{
	// Cat phan region (ranh gioi) ra thanh 4 phan bang nhau
	Nodes = new QuadTree*[4];

	RECT bound;

	int width = (Bound.right - Bound.left) / 2;
	int height = (Bound.bottom - Bound.top) / 2;

	// Phan goc tren trai
	bound.left = Bound.left;
	bound.right = bound.left + width;
	bound.top = Bound.top;
	bound.bottom = bound.top + height;
	Nodes[0] = new QuadTree(mLevel, bound);

	// PHan goc tren phai
	bound.left = Bound.left + width;
	bound.right = bound.left + width;
	bound.top = Bound.top;
	bound.bottom = bound.top + height;
	Nodes[1] = new QuadTree(mLevel, bound);

	// Phan goc duoi trai
	bound.left = Bound.left;
	bound.right = bound.left + width;
	bound.top = Bound.top + height;
	bound.bottom = bound.top + height;
	Nodes[2] = new QuadTree(mLevel, bound);

	// Phan goc duoi phai
	bound.left = Bound.left + width;
	bound.right = bound.left + width;
	bound.top = Bound.top + height;
	bound.bottom = bound.top + height;
	Nodes[3] = new QuadTree(mLevel, bound);
}

bool QuadTree::isContain(Entity* entity)
{
	RECT r = entity->GetBound();

	return (r.left >= Bound.left && r.right <= Bound.right && r.top >= Bound.top && r.bottom <= Bound.bottom);
}
