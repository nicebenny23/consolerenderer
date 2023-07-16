#include "polygon.h"
#include "Renderer.h"
#include "boxflt.h"


Vector2 pgon::centerofmass(polygon poly)
{
	if (poly.pointlist.length==0)
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
	return Vector2(xval, yval) / (6*area);
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
float pgon::area(polygon poly) {
//uses shoelase formula
	float val = 0;
	for (int i = 0;i < poly.pointlist.length-1;i++) {

		val += poly.pointlist[i].x * poly.pointlist[i + 1].y - poly.pointlist[i].y * poly.pointlist[i + 1].x;

	}
	return (val/2);

}

void pgon::polygon::drawout(int thickness,COLORREF pixelvalue)
{
	Render::drawthickcircle(pointlist[0].x, pointlist[0].y, thickness, pixelvalue);
	for (int i = 0; i < pointlist.length-1; i++)
	{
		Render::drawthickcircle(pointlist[i+1].x+polypos.x, pointlist[i+1].y+polypos.y, thickness, pixelvalue);
	
		Render::drawlinet(pointlist[i]+polypos, pointlist[i + 1]+polypos, thickness, pixelvalue);

	}

	Render::drawlinet(pointlist[pointlist.length - 1]+polypos, pointlist[0]+polypos, thickness, pixelvalue);

}
