#pragma once
#include "GameDefines/GameDefine.h"

class GJK
{
public:
	GJK();
	~GJK();

	GVec2 Subtract(GVec2 a, GVec2 b)
	{
		a.x -= b.x;
		a.y -= b.y;
		return a;
	}

	GVec2 Negate(GVec2 v)
	{
		v.x = -v.x;
		v.y = -v.y;
		return v;
	}

	GVec2 Perpendicular(GVec2 v)
	{
		GVec2 p = { v.y, -v.x };
		return p;
	}

	float DotProduct(GVec2 a, GVec2 b)
	{
		return a.x * b.x + a.y * b.y;
	}

	float LengthSquared(GVec2 v)
	{
		return v.x * v.x + v.y * v.y;
	}

	GVec2 TripleProduct(GVec2 a, GVec2 b, GVec2 c);
	GVec2 AveragePoint(const GVec2* vertices, size_t count);
	size_t IndexOfFurthestPoint(const GVec2* vertices, size_t count, GVec2 d);
	GVec2 Support(const GVec2* vertices1, size_t count1, const GVec2* vertices2, size_t count2, GVec2 d);

	int GilbertJohnsonKeerthi(const GVec2* vertices1, size_t count1, const GVec2* vertices2, size_t count2);

private:
	int m_iter_count;
};

