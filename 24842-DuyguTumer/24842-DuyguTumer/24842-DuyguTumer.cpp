#include "24842-DuyguTumer.h"
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

////////////constructor////////////
quadTree::quadTree()
{
	root = nullptr;
	max_x = 0;
	max_y = 0;
}

////////////setBoundary////////////
void quadTree::setBoundary(int x, int y)
{
	max_x = x;
	max_y = y;
}
////////////compare////////////
string quadTree::compare(quadNode* p, quadNode* r)
{
	if(p->coo.x < r->coo.x)
	{
		if(p->coo.y < r->coo.y)
		{
			return "SW";
		}
		return "NW";
	}
	else if(p->coo.y < r->coo.y)
	{
		return "SE";
	}
	else
	{
		return "NE";
	}
}

////////////insert(not recursive)////////////
void quadTree::insert(quadNode* p)
{
	if (root == nullptr)
	{
		root = p;
		return;
	}

	quadNode* curr = root;
	quadNode* father = nullptr;
	string direction;
	while(curr != nullptr)
	{
		father = curr; // remember your father (dont forget to call him sometimes)

		direction = compare(p, curr); //which way

		if (direction == "SW")
		{
			curr = curr->SW;
		}
		else if (direction == "SE")
		{
			curr = curr->SE;
		}
		else if (direction == "NW")
		{
			curr = curr->NW;
		}
		else if (direction == "NE")
		{
			curr = curr->NE;
		}
	}
	//since current is null now so we have to put it with the direction
	if (direction == "SW")
	{
		father->SW = p;
	}
	else if (direction == "SE")
	{
		father->SE = p;
	}
	else if (direction == "NW")
	{
		father->NW = p;
	}
	else if (direction == "NE")
	{
		father->NE = p;
	}
}

////////////getDistance////////////
float quadTree::getDistance(Point a, Point b)
{
	return (sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2)));
}

////////////search////////////
//private:
void quadTree::search(Point p, float radius, quadNode* ptr)
{ 
	//case-0: 
	if(ptr == nullptr) return; // Base Case

	road.push_back(ptr->cityName); //since it is recursive, it will push all the cities starting from the node with in order

	//case-1:
	if(ptr->coo.x < p.x - radius && ptr->coo.y > p.y + radius)
	{
		search(p, radius, ptr->SE);
	}
	//case-2:
	else if(ptr->coo.x > p.x - radius && ptr->coo.x < p.x + radius && ptr->coo.y > p.y + radius)
	{
		search(p, radius, ptr->SE);
		search(p, radius, ptr->SW);
	}
	//case-3:
	else if(ptr->coo.x > p.x + radius && ptr->coo.y > p.y + radius)
	{
		search(p, radius, ptr->SW);
	}
	//case-4:
	else if(ptr->coo.x  < p.x - radius && ptr->coo.y < p.y + radius && ptr->coo.y > p.y - radius)
	{
		search(p, radius, ptr->SE);
		search(p, radius, ptr->NE);
	}
	//case-5:
	else if(ptr->coo.x > p.x + radius && ptr->coo.y < p.y + radius && ptr->coo.y > p.y - radius)
	{
		search(p, radius, ptr->SW);
		search(p, radius, ptr->NW);
	}
	//case-6:
	else if(ptr->coo.x < p.x - radius && ptr->coo.y < p.y - radius)
	{
		search(p, radius, ptr->NE);
	}
	//case-7:
	else if(ptr->coo.x > p.x - radius && ptr->coo.x < p.x + radius && ptr->coo.y < p.y - radius)
	{
		search(p, radius, ptr->NE);
		search(p, radius, ptr->NW);	
	}
	//case-8:
	else if(ptr->coo.x > p.x + radius && ptr->coo.y < p.y - radius)
	{
		search(p, radius, ptr->NW);	
	}
	//case-9:
	else if( ptr->coo.x < p.x && ptr->coo.y > p.y && getDistance(ptr->coo, p) > radius)
	{
		search(p, radius, ptr->SE);
		search(p, radius, ptr->SW);
		search(p, radius, ptr->NE);
	}
	//case-10:
	else if(ptr->coo.x > p.x && ptr->coo.y > p.y && getDistance(ptr->coo, p) > radius)
	{
		search(p, radius, ptr->SE);
		search(p, radius, ptr->SW);	
		search(p, radius, ptr->NW);	
	}
	//case-11:
	else if(ptr->coo.x < p.x && ptr->coo.y < p.y && getDistance(ptr->coo, p) > radius)
	{
		search(p, radius, ptr->SE);	
		search(p, radius, ptr->NE);
		search(p, radius, ptr->NW);		
	}
	//case-12:
	else if(ptr->coo.x > p.x && ptr->coo.y < p.y && getDistance(ptr->coo, p) > radius)
	{
		search(p, radius, ptr->SW);	
		search(p, radius, ptr->NE);
		search(p, radius, ptr->NW);		
	}
	//case-13:
	else if(getDistance(ptr->coo, p) < radius)
	{
		found.push_back(ptr->cityName); // since I have to first print name of in the circle
		search(p, radius, ptr->SE);
		search(p, radius, ptr->SW);	
		search(p, radius, ptr->NE);
		search(p, radius, ptr->NW);	
	}
}
//public:
void quadTree::search(Point p, float radius)
{
	search(p,radius,root);

	if(found.size() == 0)
	{
		cout << "<None>";
	}
	for(int i = 0; i < found.size(); i++)
	{
		if(i == 0)
		{
			cout << found[i];
		}
		else
		{
			cout << ", " << found[i];
		}
	}
	cout << endl;

	for(int i = 0; i < road.size(); i++)
	{
		if(i == 0)
		{
			cout << road[i];
		}
		else
		{
			cout << ", " << road[i];
		}
	}
	cout << endl << endl;

	found.clear();
	road.clear();
}
////////////pretty_print////////////
//private:
void quadTree::pretty_print(quadNode* curr)
{
	if(curr == nullptr) return;
	if (curr != nullptr)
	{ 
		cout << curr->cityName << endl;
		pretty_print(curr->SE);
		pretty_print(curr->SW);
		pretty_print(curr->NE); 
		pretty_print(curr->NW);
	}
}
//public:
void quadTree::pretty_print()
{
	pretty_print(root);
}

////////////makeEmpty////////////
//private:
void quadTree::makeEmpty(quadNode * & ptr ) const
{
	if( ptr != NULL )
    {
		makeEmpty( ptr->NW );
		makeEmpty( ptr->NE );
		makeEmpty( ptr->SW );
		makeEmpty( ptr->SE );
		delete ptr;
    }
	ptr = NULL;
}
//public:
void quadTree::makeEmpty() 
{
	makeEmpty(root);
}

////////////destructor////////////
quadTree::~quadTree()
{
	makeEmpty();
}