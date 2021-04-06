#ifndef _QUADTREES_H
#define _QUADTREES_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Point 
{ 
    int x; 
    int y; 

    Point(int _x, int _y) 
    { 
        x = _x; 
        y = _y; 
    } 

    Point() 
    { 
        x = 0; 
        y = 0; 
    } 
}; 
  
class quadNode
{
public:
	string cityName;
	Point coo;

	//sons:
    quadNode *NW;
    quadNode *NE;
	quadNode *SW;
    quadNode *SE;

	quadNode()
		: cityName( "" ), coo(),NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr) {}
	quadNode( const string & name, Point _coo, quadNode *nw, quadNode *ne, quadNode *sw, quadNode *se )
		: cityName( name ), coo( _coo ), NW(nw), NE(ne), SW(sw), SE(se){}
	friend class quadTree;
};

//CLASS:
class quadTree
{
public:

	quadTree();
	~quadTree();
	
	void setBoundary(int max_x, int max_y);
	void insert(quadNode* p);
	void pretty_print();
	void makeEmpty();
	void search(Point p, float radius);
	float getDistance(Point a, Point b);

private:

	quadNode *root;

	// for printing in order for query.txt file
	vector<string> found;
	vector<string> road;

	// for boundaries:
	int max_x;
	int max_y;

	// helper functions for being recursive 
	void makeEmpty(quadNode *& ptr)const;
	void pretty_print(quadNode* curr);
	string compare(quadNode* p, quadNode* r);
	void search(Point p, float radius, quadNode* ptr);
};
#endif