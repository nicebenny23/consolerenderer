#include "collision.h"
#include "Renderer.h"
#include "dynamicarray.h"
#include "boxflt.h"
#include <cmath>
#include "userinput.h"
#include "debug.h"
using namespace dynamicarray;
array<collider*> collist;

void initcollisionsystem()
{
	collist = array<collider*>();

}

collider::collider()
{
	ind = collist.length;
	collist.append(this);
	Vector2 dpoint[] = { Vector2(0,0), Vector2(0,50), Vector2(30,30),Vector2(30,50),Vector2(33,50),Vector2(33,0) };
	poly.pointlist = array<Vector2>(dpoint, 6);

}

collider::collider(polygon basepoly)
{
	ind = collist.length;
	collist.append(this);
	poly.pos = zerov;
	poly.pointlist = basepoly.pointlist;

}



void collider::update()
{
}

void collider::ondestroy()
{
	collist.deleteind(ind);
	poly.pointlist.destroy();
}



void checkcol() {

	array<circle> circlelist;
	for (int i = 0; i < collist.length; i++)
	{
		circlelist.append(circle());
		circlelist[i].center=centerofmass(collist[i]->poly);
		for (int vertexwalk= 0; vertexwalk < collist[i]->poly.length(); vertexwalk++)
		{
			circlelist[i].radius = max(circlelist[i].radius, distance(circlelist[i].center,collist[i]->poly[vertexwalk]));
		}
	}



	array<array<polygon>> decomposedlist = array<array<polygon>>();
	for (int i = 0; i < collist.length; i++)
	{
		array<polygon> decomposed = convexdecomp(collist[i]->poly);
		if(DEBUG_COLLISION)
		for (int j = 0; j < decomposed.length; j++)
		{
			decomposed[j].pos = collist[i]->poly.pos;
	        decomposed[j].drawout(1, 176);
	        decomposed[j].pos = zerov;
		}
		decomposedlist.append(decomposed);
	}


	
	for (int attempts = 0; attempts < coliterations; attempts++)
	{
		for (int i = 0; i < collist.length; i++)
		{
			
			collist[i]->poly.pos += (collist[i]->holder->pos - collist[i]->storepos) / coliterations;

		}
		for (int i = 0; i < collist.length; i++)
		{
			for (int j = i; j < collist.length; j++)
			{
				if (i != j) {
					Vector2 totalseperatingvector = zerov;
							for (int i1= 0;i1< decomposedlist[i].length;i1++)
							{
								for (int j1 = 0;j1 < decomposedlist[j].length;j1++) {
									Vector2 force = computecoll(decomposedlist[i][i1], decomposedlist[j][j1], collist[i]->poly.pos, collist[j]->poly.pos);
									totalseperatingvector += force;
									collist[i]->poly.pos += force / 2;
									collist[j]->poly.pos -= force / 2;
									if (DEBUG_COLLISION)
									{
										Render::drawlinet(zerov, force * coliterations, 1, 208);
									}
								}

							}	
							//applycollision(collist[i], collist[j]);
						
				          }
			}
		}
	}
	for (int i = 0; i < collist.length; i++)
	{
		collist[i]->storepos = collist[i]->poly.pos;
		collist[i]->holder->pos = collist[i]->poly.pos;
	}



	for (int i = 0; i < decomposedlist.length; i++)
	{

		for (int j = 0; j < decomposedlist[i].length; j++)
		{
					(decomposedlist[i][j]).destroy();
		}
		decomposedlist[i].destroy();
	}
		decomposedlist.destroy();

	}





Vector2 computecoll(polygon& a, polygon& b, Vector2 pos1, Vector2 pos2)
{


	//seting position to zero 

	Vector2 first = computeonecoll(a, b, pos1, pos2);
	Vector2 second = computeonecoll(b, a, pos2, pos1);

	if (magnitude(first) < magnitude(second))
	{
		return first;
	}
	else
	{
		return second * -1;
	}


}


///<summary>
///computes a displacment vector with only one polygons vertices being taken into account
///</summary>
Vector2 computeonecoll(polygon& a, polygon& b,Vector2 pos1,Vector2 pos2)
{
	
	int alength = a.pointlist.length;//pointlist1length
	float mtvmag = INFINITY;//magnatude of mtv
	Vector2 mimimaltranslationvector = zerov;//colision vector

	for (int i = 0; i < alength; i++)//goes through each line
	{
		
		if (mtvmag==0)
		{
			break;
		}
		
		Vector2 p1 = a[i];//first point on line
		Vector2 p2 = a[(i + 1) % alength];//secont point
		Vector2 p3 = zerov;//orthogonal line
		if (slope(p1, p2) == 0)//zero slope case
		{

			p3 = Vector2(p1.x + 0.0001, p1.y + 1);//calculating veritcal line
		}
		else {

			p3 = Vector2(p1.x - 1, p1.y + 1 / slope(p1, p2));//computing the orthigonal vector
		}
		   

		Vector2 pmax = Vector2(-INFINITY, 0);
		Vector2 pmin = Vector2(INFINITY, 0);
		Vector2  p1max = Vector2(-INFINITY, 0);
		Vector2 p1min = Vector2(INFINITY, 0);
		bool sideminmax=false;
		for (int j = 0; j < alength; j++)
		{
			Vector2 pointonline = closestpointonline(a[j] + pos1, p1, p3);
			if (pointonline.x >= pmax.x)
			{
				if (j==i)
				{
					sideminmax = true;
				}
				pmax = pointonline;
			}
			if (pointonline.x < pmin.x)
			{
				pmin = pointonline;
				
			}
			
		}
		for (int j = 0; j < b.pointlist.length; j++)
		{
			Vector2 pointonline = closestpointonline(b[j] + pos2, p1, p3);//projected to a line

			if (pointonline.x > p1max.x)
			{
				p1max = pointonline;
				
			}
			if (pointonline.x < p1min.x)
			{
				p1min = pointonline;
				
			}
		
		}
	

		Vector2 mindirectionalforce = zerov;//temperary force

			if (pmax.x > p1max.x)
			{
				mindirectionalforce = collcasework(pmax, pmin, p1max, p1min,sideminmax);
			}
			else
			{
				mindirectionalforce = collcasework(p1max, p1min, pmax, pmin,!sideminmax) * -1;
			}
		
			if (magnitude(mindirectionalforce) < mtvmag	) {
				mtvmag = magnitude(mindirectionalforce);
				mimimaltranslationvector = mindirectionalforce;

			}
		
		
	}

	return mimimaltranslationvector;
	
}
///<summary>
///computes casework for sat intervals
///</summary>
Vector2 collcasework(Vector2 pmax, Vector2 pmin, Vector2 p1max, Vector2 p1min, bool way) {


	if (p1max.x <= pmin.x) {

		//no intersection
		return zerov;
	}
	else
	{

		//when p is at least in p1
		if (pmin.x > p1min.x)
		{
			//p is not fully in p1
			return  (p1max - pmin);



		}

		if (pmin.x <= p1min.x)
		{
			//when p1 is fully in p

			//probobly right but just guessed
			if (way)
			{
				return  (p1min - pmax);
			}
			else
			{
				return  (p1max - pmin);
			}

		}



	}

 
} 