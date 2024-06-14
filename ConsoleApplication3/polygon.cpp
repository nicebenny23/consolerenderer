#include "polygon.h"
#include "Renderer.h"
#include "random.h"
#include "quack.h"
#include "debug.h"
#include "mathc.h"
using namespace pgon;

#include "dynamicarray.h"

///<summary>
/// the sign can tell whether points are clockwise or counter clockwize
///</summary>

bool rotorder(Vector2 a, Vector2 b, Vector2 c) {
	int ans = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
	//collinearity!= concavity
	return  ans >= 0;
}
bool imprecisepointinpolygon(Vector2 point, polygon& poly)
{

	bool parity = false;

	for (int i = 0; i < poly.pointlist.length - 1; i++) {

		parity ^= v2::impreciseleftofline(point, poly[i], poly[i + 1]);
	}

	parity ^= v2::impreciseleftofline(point, poly[poly.length() - 1], poly[0]);

	return parity;

}
Vector2 pgon::centerofmass(polygon poly)
{
	/*if (poly.pointlist.length == 0)
	{
		return Vector2(0, 0);

	}
	if (poly.pointlist.length == 1)
	{
		return poly.pointlist[0];

	}

	float xval = 0;
	float yval = 0;
	float conval = 0;
	float area = pgon::area(poly);
	for (int i = 0;i < poly.pointlist.length-1;i++)
	{
		conval = poly.pointlist[i + 1].y * poly.pointlist[i].x - poly.pointlist[i].y * poly.pointlist[i + 1].x;
			xval += conval * (poly.pointlist[i].x + poly.pointlist[i + 1].x);
			yval += conval * (poly.pointlist[i].y + poly.pointlist[i + 1].y);
	}
	return Vector2(xval, yval) / (6*area);\
	*/
	Vector2 total = Vector2();
	for (int i = 0; i < poly.pointlist.length; i++)
	{
		total += poly.pointlist[i];
	}
	return total / poly.pointlist.length;
}
bool pgon::simple(polygon poly)
{
	return false;
}
pgon::polygon::polygon() {






}
bool pgon::basicintersect(polygon& a, polygon& b)
{
	//if false can tbe in interior
	if (imprecisepointinpolygon(a[0], b))
	{
		return true;
	}
	for (int i = 0; i < a.length(); i++)
	{
		
		for (int j = 0;j < b.length();j++) {
			if (lineinter(a[i],a[mod(i+1,a.length())], b[j], b[mod(j + 1, b.length())],false,false))
			{
				return true;
			}


		}
	}
	
	return false;
}
bool lineinpolygon2(polygon poly, Vector2 start, Vector2 end,bool countiflineisonpolygon =false)
{


		for (int i = 0; i < poly.pointlist.length; i++) {

			if (poly[i]!=start&& poly[i] != end)
			{
				//dont know if correct
				if (poly[(i + 1) % poly.pointlist.length] != start && poly[(i + 1) % poly.pointlist.length] != end)
				{
					//
					if (lineinter(start, end, poly[i], poly[(i + 1) % poly.pointlist.length]),countiflineisonpolygon)
					{
						return false;
					}
				}
			
			}
		
		}
		if (pointinpolygon((start + end) / 2, poly,!countiflineisonpolygon))
		{
			return true;
		}
	return false;
}
bool pgon::lineinpolygon(polygon poly, Vector2 start, Vector2 end)
{

	if (pointinpolygon(start, poly) && pointinpolygon(end, poly))
	{

		for (int i = 0; i < poly.pointlist.length - 1; i++) {


			if (lineinter(start, end, poly[i], poly[i + 1]))
			{
				return false;
			}
		}
		if (!pointinpolygon((start + end) / 2, poly))
		{
			return false;
		}
		return true;
	}
	return false;
}
//copes existing polygon
pgon::polygon::polygon(const polygon& poly): pointlist(poly.pointlist)
{

	pos = zerov;
	
}

pgon::polygon::polygon(Vector2* listofpoints, int length) {
	for (size_t i = 0; i < length; i++)
	{
		pointlist[i] = (listofpoints[i]);
	}

}


array<array<int>> pgon::trilisttoint(array<int> trilist)
{
	array<array<int>> pollist = array<array<int>>();
	for (int i = 0; i < trilist.length; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			pollist.append(array<int>(trilist[i]));
		}
	}
	return pollist;
}

inline Vector2 pgon::polygon::operator[](int index)
{
	return pointlist[index] + pos;
}






void pgon::polygon::append(v2::Vector2 val) {


	pointlist.append(val);

}
//determanes whether a point is in a polygon(
// inpolygonifonsides determanes whether a point on the sides of a polygon counts as being in the polygon uses position
bool pgon::pointinpolygon(Vector2 point, polygon& poly,bool inpolygonifonsides)
{



	bool parity = false;

	for (int i = 0; i < poly.pointlist.length - 1; i++) {
		if (poly.pointlist[i]==point)
		{
			return true;
		}
		parity ^= v2::leftofline(point, poly.pointlist[i], poly.pointlist[i + 1], inpolygonifonsides);
	}	
	if (inpolygonifonsides&& poly.pointlist[poly.length()-1] == point)
	{
		return true;
	}
	parity ^= v2::leftofline(point, poly.pointlist[0], poly.pointlist[poly.length() - 1], inpolygonifonsides);

	return parity;



}

float pgon::area(polygon poly) {
	//uses shoelase formula
	float val = 0;
	for (int i = 0; i < poly.pointlist.length - 1; i++) {

		val += poly.pointlist[i].x * poly.pointlist[i + 1].y - poly.pointlist[i].y * poly.pointlist[i + 1].x;

	}
	return (val / 2);

}

void pgon::polygon::drawout(int thickness, COLORREF pixelvalue)
{
	int len = pointlist.length;
	if (len > 0)
	{


		Render::drawthickcircle(pointlist[0].x + pos.x, pointlist[0].y + pos.y, thickness, pixelvalue);
		for (int i = 0; i < pointlist.length; i++)
		{
			Render::drawthickcircle(pointlist[(i + 1) % len].x + pos.x, pointlist[(i + 1) % len].y + pos.y, thickness, pixelvalue);

			Render::drawlinet(pointlist[i] + pos, pointlist[(i + 1) % len] + pos, thickness, pixelvalue);

		}
	}
}

array<int> pgon::numbtri(polygon poly) {
	int len = poly.pointlist.length;
	array<int> list = array<int>(len - 2);
	int i = 1;
	while (len > 3)
	{



		if (!lineinpolygon(poly, poly[(i - 1) % len], poly[(i + 1) % len]))
		{

		
			list.append((i - 1) % len);
			list.append(i);
			list.append((i + 1) % len);
			poly.pointlist.deleteind(i);
			len--;

		}
		i += 1;
		if (i >= len)
		{
			i = 1;
		}


	}
	list.append(0);
	list.append(1);
	list.append(2);
	return list;

}




	int parttion(polygon arr, int low, int high,Vector2 pnt)
	{
		Vector2 pivot = arr[int(floor((high + low) / 2))];
		int leftind = low - 1;
		int rightind = high + 1;

		while (true)
		{

			do
			{
				leftind++;
			} while (-slope(arr[leftind],pnt) < -slope(pivot,pnt));
			do
			{
				rightind--;
			} while (-slope(arr[rightind],pnt) > -slope(pnt,pivot));

			if (-slope(arr[leftind], pnt) >= -slope(arr[rightind], pnt))
			{
				return rightind;
			}
		 Vector2	carry = arr[leftind];
			arr[leftind] = arr[rightind];
			arr[rightind] = carry;

		}

	}



	void polyquicksub(polygon arr, int low, int high,Vector2 pnt) {

		if (low < high)
		{
			int p = parttion(arr, low, high,pnt);

			polyquicksub(arr, low, p,pnt);
			polyquicksub(arr, p + 1, high,pnt);
		}



	}



	
	void polsortpnt(polygon arr,Vector2 pnt) {
		polyquicksub(arr, 0, arr.pointlist.length-1,pnt);
		float prevang = -1000;
		Vector2 prevpnt = Vector2(-int(INFINITE), INFINITE);
		 
	}

	polygon pgon::quickerhull(polygon poly)
	{
	//implement quickhull


		return polygon();
	}

	int vdist(int i, int  j, int len) {

		return min(abs(i - j), len - abs ( i - j));
	}
///<summary>
///decomposes a polygon into convex ones
///</summary>
	array<polygon> pgon::convexdecomp(polygon poly)
	{
	
		int pntlen = poly.pointlist.length;
		//first cycle of verices
		for (int i = 0; i < pntlen; i++)
		{
			//checks if oriented incorrectly
			if (rotorder(poly[mod((i - 1), pntlen)], poly[i], poly[mod((i + 1), pntlen)]) == false)
			{

				array<polygon> conarr = array <polygon>();
				//furtheest index satifyigng the conditions found
				int farind = i;
				//working point satisfies at leas one of 2 of convexities
				bool foundhalfconvexpoint = false;
				//convex point satisies both
				bool foundconvpoint = false;
				//found a point which will removes some convecities

				for (int j = 0;j < pntlen;j++) {

					int l = vdist(i, j, pntlen);
					
					if (vdist(i,j,pntlen)>1)
					{
						//todo make counteclockwize work;
						//sees if polygon can be split to remove  concavities 
						bool check1 = rotorder(poly[j], poly[i], poly[mod((i + 1), pntlen)]);
						bool check2 = (rotorder(poly[mod((i - 1), pntlen)], poly[i], poly[j]));



						if (check1 == check2 ||(!foundconvpoint &&(check1^check2))) {
							if (lineinpolygon2(poly, poly[i], poly[j])) {

								if ( !foundhalfconvexpoint)
								{
									
									farind = j;
									foundhalfconvexpoint = true;

								}
								
								if ((vdist(i, j, pntlen) > vdist(i, farind, pntlen)) ||( (check1 == check2) && !foundconvpoint)) {
									farind = j;
									if ((check1 == check2))
									{
										foundconvpoint = true;
									}
								}
								
								
								
							}
						}
						


					}
				}


				polygon poly1 = poly;
				//slices polygon into 2 diffrent parts
				//contained part
				poly1.pointlist.slice(i, farind);

				polygon poly2 = poly;
				//slices polygon into 2 diffrent parts
				poly2.pointlist.cutind(mod(min(i,farind)+1, poly.pointlist.length), mod(max(farind ,i)-1, poly.pointlist.length));


				array<polygon> output = array<polygon>();
				array<polygon> decomposed1 = convexdecomp(poly1);
				array<polygon> decomposed2 = convexdecomp(poly2);
				output.append(decomposed1);
				output.append(decomposed2);


				decomposed1.destroy();
				decomposed2.destroy();
			
				return output;
			}
		}
		
		array<polygon> output = array<polygon>();
		output.append(poly);
		poly.pointlist.destroy();
		if (DEBUG)
		{
			debug::writestring("	");
			for (int u = 0; u < output[0].length(); u++)
			{
				debug::writestring(vectostring(output[0][u]));
			}
		}
		
		return output;
		
	
	}
	
	int pgon::findindexofpoint(polygon& poly, int startsearch, Vector2 point)
	{
		for (int i = 0; i < poly.length(); i++)
		{
			int ind = mod(startsearch + i, poly.length());
			if (poly[ind]==point)
			{
				return ind;
			}
		}
		return -1;
	}