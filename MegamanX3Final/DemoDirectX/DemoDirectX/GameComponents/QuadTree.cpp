#include "QuadTree.h"
#include "GameCollision.h"

QuadTree::QuadTree(int level, RECT bound)
{
	//chia lam 4

	this->_bound = bound;
	this->_level = level;
}

void QuadTree::Clear()
{
	if (_node)
	{
		for (size_t i = 0; i < (size_t)4; i++)
		{
			if (_node[i])
			{
				_node[i]->Clear();
				delete _node[i];
				_node[i] = nullptr;
			}
		}

		delete[] _node;
	}
}

void QuadTree::InsertObject(BaseObject *entity)
{
	if (_node)
	{
		if (_node[0]->IsContain(entity->GetBound()))
			_node[0]->InsertObject(entity);
		if (_node[1]->IsContain(entity->GetBound()))
			_node[1]->InsertObject(entity);
		if (_node[2]->IsContain(entity->GetBound()))
			_node[2]->InsertObject(entity);
		if (_node[3]->IsContain(entity->GetBound()))
			_node[3]->InsertObject(entity);

		return; //Thoát ra luôn
	}

	//Thêm đối tượng vào quadtree
	if (this->IsContain(entity->GetBound()))
		this->_listObject.push_back(entity);

	if (_listObject.size() > 5 && _level < 6)
	{
		Split();

		while (!_listObject.empty())
		{
			if (_node[0]->IsContain(_listObject.back()->GetBound()))
				_node[0]->InsertObject(_listObject.back());
			if (_node[1]->IsContain(_listObject.back()->GetBound()))
				_node[1]->InsertObject(_listObject.back());
			if (_node[2]->IsContain(_listObject.back()->GetBound()))
				_node[2]->InsertObject(_listObject.back());
			if (_node[3]->IsContain(_listObject.back()->GetBound()))
				_node[3]->InsertObject(_listObject.back());

			_listObject.pop_back();
		}
	}
}

bool QuadTree::IsContain(RECT rect1)
{
	return !(rect1.left > _bound.right || rect1.right < _bound.left || rect1.top > _bound.bottom || rect1.bottom < _bound.top);
}

void QuadTree::Split()
{
	//cat phan region (ranh gioi) ra thanh 4 phan bang nhau
	_node = new QuadTree *[4];

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

int QuadTree::GetTotalObject()
{
	int total = _listObject.size();

	if (_node)
	{
		for (size_t i = 0; i < 4; i++)
		{
			total += _node[i]->GetTotalObject();
		}
	}

	return total;
}

void QuadTree::GetAllObject(std::vector<BaseObject*> &EntityOut, RECT rect)
{
	for (auto child : _listObject)
	{
			EntityOut.push_back(child);
	}

	if (_node)
	{
		for (size_t i = 0; i < 4; i++)
		{
			_node[i]->GetAllObject(EntityOut, rect);
		}
	}
}

void QuadTree::GetObjectCollide(std::vector<BaseObject*> &EntityStatic, RECT rect)
{
	if (_node)
	{
		if (_node[0]->IsContain(rect))
			_node[0]->GetObjectCollide(EntityStatic, rect);
		if (_node[1]->IsContain(rect))
			_node[1]->GetObjectCollide(EntityStatic, rect);
		if (_node[2]->IsContain(rect))
			_node[2]->GetObjectCollide(EntityStatic, rect);
		if (_node[3]->IsContain(rect))
			_node[3]->GetObjectCollide(EntityStatic, rect);

		return;
	}

	//Lấy tất cả đối tượng trong vùng
	if (IsContain(rect))
	{
		for (auto child : _listObject)
		{
			bool istrue = true;

			for (auto& entity : EntityStatic)
				if (child->GetId() == entity->GetId())
				{
					istrue = false;
					break;
				}
			
			if (istrue)
			{
				if (child->GetObjectType() != BaseObject::ENEMY && child->GetObjectType() != BaseObject::BOSS && child->GetObjectType() != BaseObject::ITEM)
					EntityStatic.push_back(child);
			}
		}
	}
}

void QuadTree::GetObjectCamera(std::vector<BaseObject*> &EntityOut, RECT rect)
{
	if (_node)
	{
		if (_node[0]->IsContain(rect))
			_node[0]->GetObjectCamera(EntityOut, rect);
		if (_node[1]->IsContain(rect))
			_node[1]->GetObjectCamera(EntityOut, rect);
		if (_node[2]->IsContain(rect))
			_node[2]->GetObjectCamera(EntityOut, rect);
		if (_node[3]->IsContain(rect))
			_node[3]->GetObjectCamera(EntityOut, rect);

		return;
	}

	//Lấy tất cả đối tượng trong vùng
	if (IsContain(rect))
	{
		for (auto child : _listObject)
		{
			if (GameCollision::IsCollision(child->GetBound(), rect))
			{
				bool istrue = true;

				for (auto& entity : EntityOut)
					if (child->GetId() == entity->GetId())
					{
						istrue = false;
						break;
					}

				if (istrue)
				{
					if (child->GetObjectType() != BaseObject::STATIC)
						EntityOut.push_back(child);
				}
			}
		}
	}
}