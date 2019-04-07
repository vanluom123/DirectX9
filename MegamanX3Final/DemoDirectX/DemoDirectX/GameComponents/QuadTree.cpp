#include "QuadTree.h"
#include "GameCollision.h"

QuadTree::~QuadTree()
{
}
QuadTree::QuadTree()
{

}
QuadTree::QuadTree(int level, RECT bound)
{
	//chia lam 4

	this->Bound = bound;
	this->mLevel = level;
}

void QuadTree::Clear()
{
	if (Nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (Nodes[i])
			{
				Nodes[i]->Clear();
				delete Nodes[i];
				Nodes[i] = nullptr;
			}
		}

		delete[] Nodes;
	}
}

void QuadTree::insertObject(Entity *entity)
{
	if (Nodes)
	{
		if (Nodes[0]->isContain(entity->GetBound()))
			Nodes[0]->insertObject(entity);
		if (Nodes[1]->isContain(entity->GetBound()))
			Nodes[1]->insertObject(entity);
		if (Nodes[2]->isContain(entity->GetBound()))
			Nodes[2]->insertObject(entity);
		if (Nodes[3]->isContain(entity->GetBound()))
			Nodes[3]->insertObject(entity);

		return; //Thoát ra luôn
	}

	//Thêm đối tượng vào quadtree
	if (this->isContain(entity->GetBound()))
		this->mListEntity.push_back(entity);

	if (mListEntity.size() > 5 && mLevel < 6)
	{
		split();

		while (!mListEntity.empty())
		{
			if (Nodes[0]->isContain(mListEntity.back()->GetBound()))
				Nodes[0]->insertObject(mListEntity.back());
			if (Nodes[1]->isContain(mListEntity.back()->GetBound()))
				Nodes[1]->insertObject(mListEntity.back());
			if (Nodes[2]->isContain(mListEntity.back()->GetBound()))
				Nodes[2]->insertObject(mListEntity.back());
			if (Nodes[3]->isContain(mListEntity.back()->GetBound()))
				Nodes[3]->insertObject(mListEntity.back());

			mListEntity.pop_back();
		}
	}
}

bool QuadTree::isContain(RECT rect1)
{
	return !(rect1.left > Bound.right || rect1.right < Bound.left || rect1.top > Bound.bottom || rect1.bottom < Bound.top);
}

void QuadTree::split()
{
	//cat phan region (ranh gioi) ra thanh 4 phan bang nhau
	Nodes = new QuadTree *[4];

	RECT bound;

	int width = (Bound.right - Bound.left) / 2;
	int height = (Bound.bottom - Bound.top) / 2;

	//phan goc trai tren
	bound.left = Bound.left;
	bound.right = bound.left + width;
	bound.top = Bound.top;
	bound.bottom = bound.top + height;
	Nodes[0] = new QuadTree(mLevel + 1, bound);

	//phan goc phai tren
	bound.left = Bound.left + width;
	bound.right = bound.left + width;
	bound.top = Bound.top;
	bound.bottom = bound.top + height;
	Nodes[1] = new QuadTree(mLevel + 1, bound);

	//phan goc trai duoi
	bound.left = Bound.left;
	bound.right = bound.left + width;
	bound.top = Bound.top + height;
	bound.bottom = bound.top + height;
	Nodes[2] = new QuadTree(mLevel + 1, bound);

	//phan goc phai duoi
	bound.left = Bound.left + width;
	bound.right = bound.left + width;
	bound.top = Bound.top + height;
	bound.bottom = bound.top + height;
	Nodes[3] = new QuadTree(mLevel + 1, bound);
}

int QuadTree::getTotalObject()
{
	int total = mListEntity.size();

	if (Nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			total += Nodes[i]->getTotalObject();
		}
	}

	return total;
}

void QuadTree::getAllObject(std::vector<Entity*> &EntityOut, RECT rect)
{
	for (auto child : mListEntity)
	{
			EntityOut.push_back(child);
	}

	if (Nodes)
	{
		for (size_t i = 0; i < 4; i++)
		{
			Nodes[i]->getAllObject(EntityOut, rect);
		}
	}
}

void QuadTree::getObjectsCollideAble(std::vector<Entity*> &EntityStatic, RECT rect)
{
	if (Nodes)
	{
		if (Nodes[0]->isContain(rect))
			Nodes[0]->getObjectsCollideAble(EntityStatic, rect);
		if (Nodes[1]->isContain(rect))
			Nodes[1]->getObjectsCollideAble(EntityStatic, rect);
		if (Nodes[2]->isContain(rect))
			Nodes[2]->getObjectsCollideAble(EntityStatic, rect);
		if (Nodes[3]->isContain(rect))
			Nodes[3]->getObjectsCollideAble(EntityStatic, rect);

		return;
	}

	//Lấy tất cả đối tượng trong vùng
	if (isContain(rect))
	{
		for (auto child : mListEntity)
		{
			bool istrue = true;

			for (auto& entity : EntityStatic)
				if (child->id == entity->id)
				{
					istrue = false;
					break;
				}
			
			if (istrue)
			{
				if (child->GetTag() != Entity::ENEMY && child->GetTag() != Entity::BOSS && child->GetTag() != Entity::ITEM)
					EntityStatic.push_back(child);
			}
		}
	}
}

void QuadTree::getObjectsInCamera(std::vector<Entity*> &EntityOut, RECT rect)
{
	if (Nodes)
	{
		if (Nodes[0]->isContain(rect))
			Nodes[0]->getObjectsInCamera(EntityOut, rect);
		if (Nodes[1]->isContain(rect))
			Nodes[1]->getObjectsInCamera(EntityOut, rect);
		if (Nodes[2]->isContain(rect))
			Nodes[2]->getObjectsInCamera(EntityOut, rect);
		if (Nodes[3]->isContain(rect))
			Nodes[3]->getObjectsInCamera(EntityOut, rect);

		return;
	}

	//Lấy tất cả đối tượng trong vùng
	if (isContain(rect))
	{
		for (auto child : mListEntity)
		{
			if (GameCollision::IsCollision(child->GetBound(), rect))
			{
				bool istrue = true;

				for (auto& entity : EntityOut)
					if (child->id == entity->id)
					{
						istrue = false;
						break;
					}

				if (istrue)
				{
					if (child->GetTag() != Entity::STATIC)
						EntityOut.push_back(child);
				}
			}
		}
	}
}