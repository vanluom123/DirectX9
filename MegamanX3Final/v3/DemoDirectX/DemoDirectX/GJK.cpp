#include "GJK.h"

GJK::GJK()
{
}

GJK::~GJK()
{
}

// Triple product expansion is used to calculate Perpendicular normal vectors 
// which kinda 'prefer' pointing towards the Origin in Minkowski space
GVec2 GJK::TripleProduct(GVec2 a, GVec2 b, GVec2 c)
{
	GVec2 r;

	float ac = a.x * c.x + a.y * c.y; // perform a.dot(c)
	float bc = b.x * c.x + b.y * c.y; // perform b.dot(c)

	// perform b * a.dot(c) - a * b.dot(c)
	r.x = b.x * ac - a.x * bc;
	r.y = b.y * ac - a.y * bc;
	return r;
}

// This is to compute average center (roughly). It might be different from
// Center of Gravity, especially for bodies with nonuniform density,
// but this is ok as initial direction of simplex search in GJK.
GVec2 GJK::AveragePoint(const GVec2* vertices, size_t count)
{
	GVec2 avg = { 0.f, 0.f };
	for (size_t i = 0; i < count; i++) {
		avg.x += vertices[i].x;
		avg.y += vertices[i].y;
	}
	avg.x /= count;
	avg.y /= count;
	return avg;
}

// Get furthest vertex along a certain direction
size_t GJK::IndexOfFurthestPoint(const GVec2* vertices, size_t count, GVec2 d)
{
	float maxProduct = DotProduct(d, vertices[0]);
	size_t index = 0;
	for (size_t i = 1; i < count; i++) {
		float product = DotProduct(d, vertices[i]);
		if (product > maxProduct) {
			maxProduct = product;
			index = i;
		}
	}
	return index;
}

// Minkowski sum Support function for GJK
GVec2 GJK::Support(const GVec2* vertices1, size_t count1, const GVec2* vertices2, size_t count2, GVec2 d)
{
	// get furthest point of first body along an arbitrary direction
	size_t i = IndexOfFurthestPoint(vertices1, count1, d);

	// get furthest point of second body along the opposite direction
	size_t j = IndexOfFurthestPoint(vertices2, count2, Negate(d));

	// Subtract (Minkowski sum) the two points to see if bodies 'overlap'
	return Subtract(vertices1[i], vertices2[j]);
}

// GJK
int GJK::GilbertJohnsonKeerthi(const GVec2* vertices1, size_t count1, const GVec2* vertices2, size_t count2)
{
	size_t index = 0; // index of current vertex of simplex
	GVec2 a, b, c, d, ao, ab, ac, abperp, acperp, simplex[3];

	GVec2 position1 = AveragePoint(vertices1, count1); // not a CoG but
	GVec2 position2 = AveragePoint(vertices2, count2); // it's ok for GJK )

	// initial direction from the center of 1st body to the center of 2nd body
	d = Subtract(position1, position2);

	// if initial direction is zero – set it to any arbitrary axis (we choose X)
	if ((d.x == 0) && (d.y == 0))
		d.x = 1.f;

	// set the first Support as initial point of the new simplex
	a = simplex[0] = Support(vertices1, count1, vertices2, count2, d);

	if (DotProduct(a, d) <= 0)
		return 0; // no collision

	d = Negate(a); // The next search direction is always towards the origin, so the next search direction is Negate(a)

	while (1) {
		m_iter_count++;

		a = simplex[++index] = Support(vertices1, count1, vertices2, count2, d);

		if (DotProduct(a, d) <= 0)
			return 0; // no collision

		ao = Negate(a); // from point A to Origin is just negative A

		// simplex has 2 points (a line segment, not a triangle yet)
		if (index < 2) {
			b = simplex[0];
			ab = Subtract(b, a); // from point A to B
			d = TripleProduct(ab, ao, ab); // normal to AB towards Origin
			if (LengthSquared(d) == 0)
				d = Perpendicular(ab);
			continue; // skip to next iteration
		}

		b = simplex[1];
		c = simplex[0];
		ab = Subtract(b, a); // from point A to B
		ac = Subtract(c, a); // from point A to C

		acperp = TripleProduct(ab, ac, ac);

		if (DotProduct(acperp, ao) >= 0) {

			d = acperp; // new direction is normal to AC towards Origin

		}
		else {

			abperp = TripleProduct(ac, ab, ab);

			if (DotProduct(abperp, ao) < 0)
				return 1; // collision

			simplex[0] = simplex[1]; // swap first element (point C)

			d = abperp; // new direction is normal to AB towards Origin
		}

		simplex[1] = simplex[2]; // swap element in the middle (point B)
		--index;
	}

	return 0;
}
