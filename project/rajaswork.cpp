#include <string.h>
#include <stdio.h>
#include <armadillo>
#include <iostream>
#include <fstream>
#include "ngraph.hpp"
#include <algorithm>
#include <map>
//using namespace NGraph;
using namespace std;

/*

Input File Format:

1 int int int   : Front viewing direction
2 int int int   : Top viewing direction
3 int int int   : Cutting Plane
4 int v 		: Number of vertices
5
.
.
.
5+v-1
5+v int e 		: Number of edges
5+v+1
.
.
.
5+v+e-1

*/

map <int, vector<int> > v;
struct Triplet
{
  double  one, two, three;
};
class Graph{
	public:
		vector<Triplet> vertices;
		map <int, std::vector<int> > edges;
};
struct Doublet
{
	double one, two;
	bool not_present;
};
vector<Triplet> vertices;
vector<Doublet> projx;
void projectx(){
	for (int i = 0; i < vertices.size(); ++i)
	{
		bool added = false;
		Doublet temp = {vertices.at(i).one, vertices.at(i).two};
		for (int j = 0; j < i; ++j)
		{
			if ((temp.one == vertices.at(j).one) && (temp.two == vertices.at(j).two)){
				temp.not_present = true;
				break;
			}
		}
		projx.push_back(temp);
	}
}

int main(int argc, char const *argv[])
{
	Triplet temp = {1,2,3};
	Triplet t;
	vertices.push_back(temp);
	vertices.push_back(t);
	cout<<vertices.at(0).one<<endl;
	Graph x;
	
}
