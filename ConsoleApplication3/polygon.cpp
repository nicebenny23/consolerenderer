#include "polygon.h"
#include "Renderer.h"
#include "boxflt.h"


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
		total+= poly.pointlist[i];
	}
	return total / poly.pointlist.length;
}

bool pgon::lineinpolygon(polygon poly, Vector2 start, Vector2 end)
{

	if (pointinpolygon(start,poly)&&pointinpolygon(end,poly))
	{

		for (int i = 0; i < poly.pointlist.length-1; i++) {


			if (lineinter(start,end,poly[i],poly[i+1]))
			{
				return false;
			}
		}
		if (lineinter(start, end, poly[poly.pointlist.length-1], poly[0])|| !pointinpolygon((start + end) / 2, poly))
		{
			return false;
		}
		return true;
	}
	return false;
}

Vector2 pgon::polygon::operator[](int index)
{
	return pointlist[index] + polypos;
}


pgon::polygon::polygon() {

	
	
	
	

}

pgon::polygon::polygon(Vector2* listofpoints, int length) {
	for (size_t i = 0; i < length; i++)
	{
		pointlist[i] = (listofpoints[i]);
	}

}

void pgon::polygon::append(v2::Vector2 val) {


	pointlist.append(val);

}
bool pgon::pointinpolygon(Vector2 point, polygon poly)
{
	
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
	/*bool parity = false;

	for (int i = 0; i < poly.pointlist.length - 1; i++) {
			parity^= v2::leftofline(point, poly.pointlist[i], poly.pointlist[i + 1]);	
	}
		parity ^= v2::leftofline(point, poly.pointlist[0], poly.pointlist[poly.pointlist.length - 1]);
	
	return parity;
	*/
}
float pgon::area(polygon poly) {
//uses shoelase formula
	float val = 0;
	for (int i = 0;i < poly.pointlist.length-1;i++) {

		val += poly.pointlist[i].x * poly.pointlist[i + 1].y - poly.pointlist[i].y * poly.pointlist[i + 1].x;

	}
	return (val/2);

}

void pgon::polygon::drawout(int thickness, COLORREF pixelvalue)
{
	Render::drawthickcircle(pointlist[0].x + polypos.x, pointlist[0].y + polypos.y, thickness, pixelvalue);
	for (int i = 0; i < pointlist.length - 1; i++)
	{
		Render::drawthickcircle(pointlist[i + 1].x + polypos.x, pointlist[i + 1].y + polypos.y, thickness, pixelvalue);

		Render::drawlinet(pointlist[i] + polypos, pointlist[i + 1] + polypos, thickness, pixelvalue);

	}

	array<triangle> list = triangulate(*this);
	for (int i = 0; i < list.length; i++)
	{
		Render::drawtriangle(list[i],i*32+32);
	}
}
	array<triangle> pgon::triangulate(polygon poly) {

		
		int len = poly.pointlist.length;
		array<triangle> list = array<triangle>(len-2);
		int i = 1;
		while (len>3)
		{
			
		
		
			if (!lineinpolygon(poly, poly[(i - 1) % len], poly[(i + 1) % len]))
			{

				list.append(triangle( poly[(i - 1)%len], poly[(i)] , poly[(i + 1) % len]));
				
				poly.pointlist.deleteind(i);
				len--;
			
			}
			i += 1;
			if (i>=len)
			{
				i = 1;
			}
			

		}
		list.append(triangle(poly[0], poly[1], poly[2]));
		return list;
	}

