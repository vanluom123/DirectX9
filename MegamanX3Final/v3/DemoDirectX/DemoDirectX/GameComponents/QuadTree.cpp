#include "QuadTree.h"
#include "GameCollision.h"

QuadTree::QuadTree(int level, RECT bound)
{
	//chia lam 4

	this->m_bound = bound;
	this->m_level = level;

	m_node = nullptr;
}

QuadTree::~QuadTree()
{
	this->Clear();
}

void QuadTree::Clear()
{
	if (m_node)
	{
		for (size_t i = 0; i < (size_t)4; i++)
		{
			if (m_node[i])
			{
				m_node[i]->Clear();
				delete m_node[i];
				m_node[i] = nullptr;
			}
		}

		delete[] m_node;
	}
}

void QuadTree::InsertObject(BaseObject* entity)
{
	if (m_node)
	{
		if (m_node[0]->IsContain(entity->GetBound()))
			m_node[0]->InsertObject(entity);
		if (m_node[1]->IsContain(entity->GetBound()))
			m_node[1]->InsertObject(entity);
		if (m_node[2]->IsContain(entity->GetBound()))
			m_node[2]->InsertObject(entity);
		if (m_node[3]->IsContain(entity->GetBound()))
			m_node[3]->InsertObject(entity);

		return; //Thoát ra luôn
	}

	//Thêm đối tượng vào quadtree
	if (this->IsContain(entity->GetBound()))
		this->m_listObject.push_back(entity);

	if (m_listObject.size() > 5 && m_level < 6)
	{
		Split();

		while (!m_listObject.empty())
		{
			if (m_node[0]->IsContain(m_listObject.back()->GetBound()))
				m_node[0]->InsertObject(m_listObject.back());
			if (m_node[1]->IsContain(m_listObject.back()->GetBound()))
				m_node[1]->InsertObject(m_listObject.back());
			if (m_node[2]->IsContain(m_listObject.back()->GetBound()))
				m_node[2]->InsertObject(m_listObject.back());
			if (m_node[3]->IsContain(m_listObject.back()->GetBound()))
				m_node[3]->InsertObject(m_listObject.back());

			m_listObject.pop_back();
		}
	}
}

bool QuadTree::IsContain(RECT rect1)
{
	return !(rect1.left > m_bound.right || rect1.right < m_bound.left || rect1.top > m_bound.bottom || rect1.bottom < m_bound.top);
}

void QuadTree::Split()
{
	//cat phan region (ranh gioi) ra thanh 4 phan bang nhau
	m_node = new QuadTree * [4];

	RECT bound;

	int width = (m_bound.right - m_bound.left) / 2;
	int height = (m_bound.bottom - m_bound.top) / 2;

	//phan goc trai tren
	bound.left = m_bound.left;
	bound.right = bound.left + width;
	bound.top = m_bound.top;
	bound.bottom = bound.top + height;
	m_node[0] = new QuadTree(m_level + 1, bound);

	//phan goc phai tren
	bound.left = m_bound.left + width;
	bound.right = bound.left + width;
	bound.top = m_bound.top;
	bound.bottom = bound.top + height;
	m_node[1] = new QuadTree(m_level + 1, bound);

	//phan goc trai duoi
	bound.left = m_bound.left;
	bound.right = bound.left + width;
	bound.top = m_bound.top + height;
	bound.bottom = bound.top + height;
	m_node[2] = new QuadTree(m_level + 1, bound);

	//phan goc phai duoi
	bound.left = m_bound.left + width;
	bound.right = bound.left + width;
	bound.top = m_bound.top + height;
	bound.bottom = bound.top + height;
	m_node[3] = new QuadTree(m_level + 1, bound);
}

int QuadTree::GetTotalObject()
{
	int total = m_listObject.size();

	if (m_node)
	{
		for (size_t i = 0; i < (size_t)4; i++)
		{
			total += m_node[i]->GetTotalObject();
		}
	}

	return total;
}

void QuadTree::GetAllObject(std::vector<BaseObject*>& EntityOut, RECT rect)
{
	for (auto child : m_listObject)
	{
		EntityOut.push_back(child);
	}

	if (m_node)
	{
		for (size_t i = 0; i < 4; i++)
		{
			m_node[i]->GetAllObject(EntityOut, rect);
		}
	}
}

void QuadTree::GetObjectCollide(std::vector<BaseObject*>& EntityStatic, RECT rect)
{
	if (m_node)
	{
		if (m_node[0]->IsContain(rect))
			m_node[0]->GetObjectCollide(EntityStatic, rect);
		if (m_node[1]->IsContain(rect))
			m_node[1]->GetObjectCollide(EntityStatic, rect);
		if (m_node[2]->IsContain(rect))
			m_node[2]->GetObjectCollide(EntityStatic, rect);
		if (m_node[3]->IsContain(rect))
			m_node[3]->GetObjectCollide(EntityStatic, rect);

		return;
	}

	//Lấy tất cả đối tượng trong vùng
	if (IsContain(rect))
	{
		for (auto child : m_listObject)
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
				if (child->GetObjectType() != BaseObject::OBJECT_ENEMY && child->GetObjectType() != BaseObject::OBJECT_BOSS && child->GetObjectType() != BaseObject::OBJECT_ITEM)
					EntityStatic.push_back(child);
			}
		}
	}
}

void QuadTree::GetObjectCamera(std::vector<BaseObject*>& EntityOut, RECT rect)
{
	if (m_node)
	{
		if (m_node[0]->IsContain(rect))
			m_node[0]->GetObjectCamera(EntityOut, rect);
		if (m_node[1]->IsContain(rect))
			m_node[1]->GetObjectCamera(EntityOut, rect);
		if (m_node[2]->IsContain(rect))
			m_node[2]->GetObjectCamera(EntityOut, rect);
		if (m_node[3]->IsContain(rect))
			m_node[3]->GetObjectCamera(EntityOut, rect);

		return;
	}

	//Lấy tất cả đối tượng trong vùng
	if (IsContain(rect))
	{
		for (auto child : m_listObject)
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
					if (child->GetObjectType() != BaseObject::OBJECT_STATIC)
						EntityOut.push_back(child);
				}
			}
		}
	}
}

RECT QuadTree::GetBound() const
{
	return m_bound;
}

int QuadTree::GetLevel() const
{
	return m_level;
}

std::vector<BaseObject*>* QuadTree::GetListObject()
{
	return &m_listObject;
}
