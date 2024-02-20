#include "polygon.h"
#include "Renderer.h"
#include "random.h"
#include "quack.h"
#include "mathc.h"
using namespace pgon;

#include "dynamicarray.h"

///<summary>
/// the sign can tell whether points are clockwise or counter clockwize
///</summary>
bool rotorder(Vector2 a, Vector2 b, Vector2 c) {
	int ans = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
	return  ans >= 0;
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
bool lineinpolygon2(polygon poly, Vector2 start, Vector2 end)
{


		for (int i = 0; i < poly.pointlist.length; i++) {

			if (poly[i]!=start&& poly[i] != end)
			{
				if (lineinter(start, end, poly[i], poly[(i + 1)%poly.pointlist.length]))
				{
					return false;
				}
			}
		
		}
		if (!pointinpolygon((start + end) / 2, poly))
		{
			return false;
		}
		return true;
	
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
pgon::polygon::polygon(const polygon& poly): pointlist(poly.pointlist)
{

	polypos = zerov;
	
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

Vector2 pgon::polygon::operator[](int index)
{
	return pointlist[index] + polypos;
}






void pgon::polygon::append(v2::Vector2 val) {


	pointlist.append(val);

}
bool pgon::pointinpolygon(Vector2 point, polygon poly)
{



	bool parity = false;

	for (int i = 0; i < poly.pointlist.length - 1; i++) {
		parity ^= v2::leftofline(point, poly.pointlist[i], poly.pointlist[i + 1]);
	}
	parity ^= v2::leftofline(point, poly.pointlist[0], poly.pointlist[poly.pointlist.length - 1]);

	return parity;
	/*
	short wind = 0;


	for (int i = 0; i < poly.pointlist.length; i++)
	{
		if (poly[i].y <= point.y)
		{


			if (point.y<poly[(i + 1) % (poly.pointlist.length)].y)
			{
				if (badleftofline(point, poly[i], poly[(i + 1) % (poly.pointlist.length)]))
				{
					wind++;
				}
			}
		}
		else
		{

				if ( poly[(i + 1) % poly.pointlist.length].y<=point.y)
				{
					if (badrightofline(point, poly[i], poly[(i + 1) % (poly.pointlist.length)]))
					{
						wind--;
					}
				}


		}
	}
	return wind !=0;
	*/



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


		Render::drawthickcircle(pointlist[0].x + polypos.x, pointlist[0].y + polypos.y, thickness, pixelvalue);
		for (int i = 0; i < pointlist.length; i++)
		{
			Render::drawthickcircle(pointlist[(i + 1) % len].x + polypos.x, pointlist[(i + 1) % len].y + polypos.y, thickness, pixelvalue);

			Render::drawlinet(pointlist[i] + polypos, pointlist[(i + 1) % len] + polypos, thickness, pixelvalue);

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

array<triangle> pgon::triangulate(polygon poly) {
	int len = poly.pointlist.length;
	array<triangle> list = array<triangle>(len - 2);
	int i = 1;
	while (len > 3)
	{



		if (!lineinpolygon(poly, poly[(i - 1) % len], poly[(i + 1) % len]))
		{

			list.append(triangle(poly[(i - 1) % len], poly[(i)], poly[(i + 1) % len]));

			poly.pointlist.deleteind(i);
			len--;

		}
		i += 1;
		if (i >= len)
		{
			i = 1;
		}


	}
	list.append(triangle(poly[0], poly[1], poly[2]));
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
polygon pgon::convexhull(polygon poly2)
{
	polygon poly = polygon(poly2);
	Vector2 pntloc = poly.polypos;
	poly.polypos = zerov;
	int lvind = 1;
	Vector2 lv = Vector2(FLT_MAX, 0);
	for (int i = 0;i < poly.pointlist.length;i++) {

		if (poly[i].x<lv.x)
		{
			lvind = i;
			lv = poly[i];
		}if (poly[i].x == lv.x)
		{
			if (poly[i].y < lv.y)
			{
				lvind = i;
				lv = poly[i];
			}
		}

	}

Vector2 v[] = {lv};
Vector2 newpoint=lv;

array<int> visit= array<int>();




for (int i = 0; i < poly.pointlist.length; i++)
{
	visit[i] = -1;
}

visit[lvind] = 1;
	polygon newpol = polygon(v,1);
	do {

		int delind=-1;
		Vector2 pnt;
		polygon polylist = poly;
		bool valid = false;
			for (int i = 0; i < poly.pointlist.length; i++) {
				if (newpoint!= poly[i])
				{


					if (rotorder(newpoint, pnt, poly[i]))
					{
						valid = true;
					}
					if (delind == -1 || rotorder(newpoint, pnt, poly[i])) {
						pnt = poly[i];
						delind = i;
					}
				}
			}
			
			if (!valid)
			{
				polylist.pointlist.destroy();

				break;
			}
			if (visit[delind]==-1)
			{
				visit[delind] = 0;
				newpol.pointlist.append(pnt);
				newpoint = pnt;
				polylist.pointlist.destroy();
			}
			else {
				polylist.pointlist.destroy();
			
				break;
			}
	} while (true);
	
	poly.polypos = pntloc;
	visit.destroy();
	return newpol;
}

///<summary>
///decomposes a polygon into convex ones
///</summary>
array<polygon> pgon::convexdecomp(polygon poly)
{
	
	int pntlen = poly.pointlist.length;
	
	for (int i = 0; i < pntlen; i++)
	{
		if (rotorder(poly[mod((i - 1), pntlen)],poly[i],poly[mod((i + 1), pntlen)]) == false)
		{

			array<polygon> conarr = array <polygon>();
			int farind = i;
			bool findconvpoint = false;
			for (int j = 0;j < pntlen;j++) {
				if (i != j)
				{
					//todo working polygon convex tests for all polygons so i need reverse case implemented
					bool check1 = rotorder(poly[j], poly[i], poly[mod((i + 1), pntlen)]);
					bool check2 = (rotorder(poly[mod((i - 1), pntlen)], poly[i], poly[j]));
							
								if (check1==check2) {
									if (abs(i - j) > abs(farind - i) && lineinpolygon2(poly, poly[i], poly[j]))
									{
										findconvpoint = true;
										farind = j;
									}  
								}
								else if (findconvpoint==false)
								{


									if (abs(i - j) > abs(farind - i) && lineinpolygon2(poly, poly[i], poly[j]))
									{
										farind = j;
									}

								}
					
				
				}
				
			}

			polygon con2 = poly;
				con2.pointlist.cutind(i + 1, farind - 1);
				polygon con1 = poly;
			
				array<polygon> output = array<polygon>();
				con1.pointlist.slice(i, farind);
				output = convexdecomp(con2);
				
				output.append(convexdecomp(con1));
				
				return output;
			
			}
		
	}
	array<polygon> output = array<polygon>();

	output[0]=(poly);
	
	
	return output;
}