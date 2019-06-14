#include "QuadTree.h"
#include "GameCollision.h"

QuadTree::QuadTree(int level, RECT bound)
{
	//chia lam 4

	this->_bound = bound;
	this->_level = level;

	_node = nullptr;
}

QuadTree::~QuadTree()
{
	this->clear();
}

void QuadTree::clear()
{
	if (_node)
	{
		for (size_t i = 0; i < (size_t)4; i++)
		{
			if (_node[i])
			{
				_node[i]->clear();
				delete _node[i];
				_node[i] = nullptr;
			}
		}

		delete[] _node;
	}
}

void QuadTree::insertObject(BaseObject* entity)
{
	if (_node)
	{
		if (_node[0]->isContain(entity->getBound()))
			_node[0]->insertObject(entity);
		if (_node[1]->isContain(entity->getBound()))
			_node[1]->insertObject(entity);
		if (_node[2]->isContain(entity->getBound()))
			_node[2]->insertObject(entity);
		if (_node[3]->isContain(entity->getBound()))
			_node[3]->insertObject(entity);

		return; //Thoát ra luôn
	}

	//Thêm đối tượng vào quadtree
	if (this->isContain(entity->getBound()))
		this->_listObject.push_back(entity);

	if (_listObject.size() > 5 && _level < 6)
	{
		split();

		while (!_listObject.empty())
		{
			if (_node[0]->isContain(_listObject.back()->getBound()))
				_node[0]->insertObject(_listObject.back());
			if (_node[1]->isContain(_listObject.back()->getBound()))
				_node[1]->insertObject(_listObject.back());
			if (_node[2]->isContain(_listObject.back()->getBound()))
				_node[2]->insertObject(_listObject.back());
			if (_node[3]->isContain(_listObject.back()->getBound()))
				_node[3]->insertObject(_listObject.back());

			_listObject.pop_back();
		}
	}
}

bool QuadTree::isContain(RECT rect1)
{
	return !(rect1.left > _bound.right || rect1.right < _bound.left || rect1.top > _bound.bottom || rect1.bottom < _bound.top);
}

void QuadTree::split()
{
	//cat phan region (ranh gioi) ra thanh 4 phan bang nhau
	_node = new QuadTree * [4];

	RECT bound;

	int width = (_bound.right - _bound.left) / 2;
	int height = (_bound.bottom - _bound.top) / 2;

	//phan goc trai tren
	bound.left = _bound.left;
	bound.right = bound.left + width;
	bound.top = _bound.top;
	bound.bottom = bound.top + height;
	_node[0] = new QuadTree(_level + 1, bound);

	//phan goc phai tren
	bound.left = _bound.left + width;
	bound.right = bound.left + width;
	bound.top = _bound.top;
	bound.bottom = bound.top + height;
	_node[1] = new QuadTree(_level + 1, bound);

	//phan goc trai duoi
	bound.left = _bound.left;
	bound.right = bound.left + width;
	bound.top = _bound.top + height;
	bound.bottom = bound.top + height;
	_node[2] = new QuadTree(_level + 1, bound);

	//phan goc phai duoi
	bound.left = _bound.left + width;
	bound.right = bound.left + width;
	bound.top = _bound.top + height;
	bound.bottom = bound.top + height;
	_node[3] = new QuadTree(_level + 1, bound);
}

int QuadTree::getTotalObject()
{
	int total = _listObject.size();

	if (_node)
	{
		for (size_t i = 0; i < (size_t)4; i++)
		{
			total += _node[i]->getTotalObject();
		}
	}

	return total;
}

void QuadTree::getAllObject(std::vector<BaseObject*>& EntityOut, RECT rect)
{
	for (auto child : _listObject)
	{
		EntityOut.push_back(child);
	}

	if (_node)
	{
		for (size_t i = 0; i < 4; i++)
		{
			_node[i]->getAllObject(EntityOut, rect);
		}
	}
}

void QuadTree::getObjectCollide(std::vector<BaseObject*>& EntityStatic, RECT rect)
{
	if (_node)
	{
		if (_node[0]->isContain(rect))
			_node[0]->getObjectCollide(EntityStatic, rect);
		if (_node[1]->isContain(rect))
			_node[1]->getObjectCollide(EntityStatic, rect);
		if (_node[2]->isContain(rect))
			_node[2]->getObjectCollide(EntityStatic, rect);
		if (_node[3]->isContain(rect))
			_node[3]->getObjectCollide(EntityStatic, rect);

		return;
	}

	//Lấy tất cả đối tượng trong vùng
	if (isContain(rect))
	{
		for (auto child : _listObject)
		{
			bool istrue = true;

			for (auto& entity : EntityStatic)
				if (child->getId() == entity->getId())
				{
					istrue = false;
					break;
				}

			if (istrue)
			{
				if (child->getObjectType() != BaseObject::ENEMY && child->getObjectType() != BaseObject::BOSS && child->getObjectType() != BaseObject::ITEM)
					EntityStatic.push_back(child);
			}
		}
	}
}

void QuadTree::getObjectCamera(std::vector<BaseObject*>& EntityOut, RECT rect)
{
	if (_node)
	{
		if (_node[0]->isContain(rect))
			_node[0]->getObjectCamera(EntityOut, rect);
		if (_node[1]->isContain(rect))
			_node[1]->getObjectCamera(EntityOut, rect);
		if (_node[2]->isContain(rect))
			_node[2]->getObjectCamera(EntityOut, rect);
		if (_node[3]->isContain(rect))
			_node[3]->getObjectCamera(EntityOut, rect);

		return;
	}

	//Lấy tất cả đối tượng trong vùng
	if (isContain(rect))
	{
		for (auto child : _listObject)
		{
			if (GameCollision::isCollision(child->getBound(), rect))
			{
				bool istrue = true;

				for (auto& entity : EntityOut)
				{
					if (child->getId() == entity->getId())
					{
						istrue = false;
						break;
					}
				}

				if (istrue)
				{
					if (child->getObjectType() != BaseObject::STATIC)
						EntityOut.push_back(child);
				}
			}
		}
	}
}

RECT QuadTree::getBound() const
{
	return _bound;
}

int QuadTree::getLevel() const
{
	return _level;
}

std::vector<BaseObject*>* QuadTree::getListObject()
{
	return &_listObject;
}
