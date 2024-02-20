#include "collision.h"
#include "Renderer.h"
#include "dynamicarray.h"
#include "boxflt.h"

using namespace dynamicarray;
array<collider*> collist;
///<summary>
///computes all colisions and runs collision updates
///</summary>
void checkcol() {
	array<box> boundingboxlist;
	for (int i = 0; i < collist.length; i++)
	{
		boundingboxlist.append(box(collist[i]->poly, collist[i]->holder->pos));

	}
	array<array<polygon>> pollist=array<array<polygon>>();
	for (int i = 0; i < collist.length; i++)
	{
		pollist.append(convexdecomp(collist[i]->poly));
	}


	for (int i = 0; i < collist.length; i++)
	{
		Vector2 pos = collist[i]->holder->pos;
		collist[i]->poly.polypos = pos;
		collist[i]->poly.drawout(3, 160);
		for (int j = i; j < collist.length; j++)
		{
			if (i != j) {
				if (boundingboxlist[i].intersect(boundingboxlist[j]))
				{
				

					int s = pollist[i].length;
					for (int z = 0;z < pollist[i].length;z++) {
						for (int x=0;x<pollist[j].length;x++)
						{
							

					Vector2 force = computecoll(pollist[j][x], pollist[i][z],collist[j]->holder->pos,collist[i]->holder->pos);

							collist[i]->holder->pos -= force;
							collist[j]->holder->pos += force ;
							}
					}
				}

			}
		}
	}
	for (int i = 0; i < pollist.length; i++)
	{
		for (int j = 0; j < pollist[i].length; j++)
		{
			pollist[i][j].pointlist.destroy();
		}
		pollist[i].destroy();
	}
	pollist.destroy();
	
}
///<summary>
///starts collision
///</summary>
void initcol()
{
	collist = array<collider*>();

}

collider::collider(polygon basepoly)
{
	ind = collist.length;
	collist.append(this);


	poly.polypos = zerov;
	poly.pointlist = basepoly.pointlist;
	      

}

collider::collider()
{
	ind = collist.length;
	collist.append(this);
	Vector2 dpoint[] = { Vector2(-10,-10),Vector2(-30,10),Vector2(20,10), Vector2(-5,-20)};
	poly.pointlist = array<Vector2>(dpoint,4);
}

void collider::update()
{
	
	 for (int i = 0; i < poly.pointlist.length; i++)
	 {
		 Vector2 d = poly[i];
		 int g = 2;
	 }
}

void collider::ondestroy()
{
	collist.deleteind(ind);
	poly.pointlist.destroy();
}



///<summary>
///does the casework for the collision intervals
///</summary>
Vector2 collcasework(Vector2 pmax, Vector2 pmin, Vector2 p1max, Vector2 p1min) {

	if (pmax.x < p1max.x)
	{
		if (pmax.x < p1min.x) {

			//no intersection
			return zerov;
		}

		if (pmax.x > p1min.x)
		{
			//when p is at least in p1


			if (p1min.x > pmin.x)
			{
				//p is not fully in p1
				return  (pmax - p1min);



			}

			if (p1min.x < pmin.x)
			{
				//when p1 is fully in p

				//thse 2 find smallest diffrence
				if ((p1max - pmin).x < (pmax - p1min).x)
				{

					return p1max - p1min;

				}
				else
				{

					return  p1max - pmin;

				}


			}



		}
	}
	return zerov;
}
///<summary>
///computes a displacment vector with only one polygons vertices being taken into account
///</summary>
Vector2 computeonecoll(polygon& a, polygon& b,Vector2 pos1,Vector2 pos2)
{



	int p1l = a.pointlist.length;//pointlist1length
	float mag2 = 10000;//actual magnatude
	Vector2 colforce = zerov;//colision vector

	for (int i = 0; i < p1l; i++)//goes through each line
	{
		int i1 = i;//first index for line

		int i2 = (i + 1) % p1l;//second index for line

		Vector2 p1 = a[i1];//first point on line
		Vector2 p2 = a[i2];//secont point
		Vector2 p3 = zerov;//orthogonal line
		if (slope(p1, p2) == 0)//zero slope case
		{

			p3 = Vector2(p1.x + 0.001, p1.y + 1);//calculating veritcal line
		}
		else {



			p3 = Vector2(p1.x - 1, p1.y + 1 / slope(p1, p2));//computing the orthigonal vector
		}

		Vector2 pmax = Vector2(-INFINITY, 0);//
		Vector2 pmin = Vector2(INFINITY, 0);
		Vector2  p1max = Vector2(-INFINITY, 0);
		Vector2 p1min = Vector2(INFINITY, 0);
		for (int j = 0; j < b.pointlist.length; j++)
		{
			Vector2 pointonline = closestpointonline(b[j] + pos2, p1, p3);//projected to a line

			if (pointonline.x < pmin.x)
			{
				pmin = pointonline;
			}
			if (pointonline.x > pmax.x)
			{
				pmax = pointonline;
			}
		}
		for (int j = 0; j < p1l; j++)
		{
			Vector2 pointonline = closestpointonline(a[j] + pos1, p1, p3);

			if (pointonline.x < p1min.x)
			{
				p1min = pointonline;
			}
			if (pointonline.x > p1max.x)
			{
				p1max = pointonline;
			}
		}
	
		Vector2 curcforce1 = zerov;//temperary force

		//orientation caswork when p1 goes further than p
		
			//orientation caswork when p goes further than p1
			if (p1max.x > pmax.x)
			{
				curcforce1 = collcasework(pmax, pmin, p1max, p1min);
			}
			else
			{

			
				curcforce1 = collcasework(p1max, p1min, pmax, pmin)*-1;
			}

			if (magnitude(curcforce1) < mag2) {
				mag2 = magnitude(curcforce1);
				colforce = curcforce1;

			}

		
	}

	return colforce;

}
///<summary>
///computes a displacment vector between 2 polygons
///</summary>
Vector2 computecoll(polygon& a, polygon& b, Vector2 pos1, Vector2 pos2)
{


	//seting position to zero 
	a.polypos = zerov;

	b.polypos = zerov;
	Vector2 first = computeonecoll(a, b, pos1, pos2);
	Vector2 second = computeonecoll(b, a, pos2, pos1);
	a.polypos = pos1;

	b.polypos = pos2;
	if (magnitude(first) > magnitude(second))
	{
		return second * -1;
	}
	else
	{
		return first;
	
	}

}