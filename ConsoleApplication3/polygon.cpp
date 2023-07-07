#include "polygon.h"
#include "Renderer.h"
Vector2& pgon::polygon::getelem(int index)
{
    return pointlist[index];
}

void pgon::polygon::insertelement(int index, Vector2 value)
{

    pointlist.insertind(index, value);


}
void pgon::polygon::append(Vector2 value)
{
	pointlist.append(value);

}
pgon::polygon::polygon() {

	
	
	


}

void pgon::polygon::drawout(int thickness,COLORREF pixelvalue)
{
	for (int i = 0; i < pointlist.length-1; i++)
	{
		
		Render::drawlinet(pointlist[i], pointlist[i + 1], thickness, pixelvalue);

	}

	Render::drawlinet(pointlist[pointlist.length - 1], pointlist[0], thickness, pixelvalue);

}
