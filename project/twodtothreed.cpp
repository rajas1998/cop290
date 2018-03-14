#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include "ngraph.hpp"
using namespace NGraph;
using namespace std;

/*

Input File Format:

int v
1.  int, int, int
2.
3.
...
...
...
v. int, int, int
v+1. int, int, int
v+2.
...
...
2v.
2v+1.
...
...
3v. int, int, int
*/

struct Triplet
{
  int  one, two, three;
  bool operator== (const Triplet&ref) const {
  	return (ref.one == one)&&(ref.two == two)&&(ref.three==three);
  }
};

class Graph_Imp
{
public:
	vector<Triplet> vertices;
	Graph edges;
	Graph_Imp(){

	}
};

void toGraphAllThree(string f, Graph_Imp &x_g, Graph_Imp &y_g, Graph_Imp &z_g)
{
	Graph A,B,C;
	fstream afile;
	afile.open(f,ios::in);
	int x,y,z,e,n;
	afile>>n;
	std::vector<Triplet> vert;
	for (int i = 0; i < n; ++i)
	{
		afile>>x>>y>>z;
		Triplet temp = {x,y,z};
		vert.push_back(temp);
	}
	afile>>e;
	for (int i = 0; i < e; ++i)
	{
		afile>>x>>y;
		if (x<y) A.insert_edge(x,y);
		else A.insert_edge(y,x);
	}
	x_g.vertices = vert;
	x_g.edges = A;
	vert.clear();
	for (int i = 0; i < n; ++i)
	{
		afile>>x>>y>>z;
		Triplet temp = {x,y,z};
		vert.push_back(temp);
	}
	afile>>e;
	for (int i = 0; i < e; ++i)
	{
		afile>>x>>y;
		if (x<y) B.insert_edge(x,y);
		else B.insert_edge(y,x);
	}
	y_g.vertices = vert;
	y_g.edges = B;
	vert.clear();
	for (int i = 0; i < n; ++i)
	{
		afile>>x>>y>>z;
		Triplet temp = {x,y,z};
		vert.push_back(temp);
	}
	afile>>e;
	for (int i = 0; i < e; ++i)
	{
		afile>>x>>y;
		if (x<y) C.insert_edge(x,y);
		else C.insert_edge(y,x);
	}
	z_g.vertices = vert;
	z_g.edges = C;
	afile.close();
	
}
std::vector<Triplet> make3DVertices(Graph_Imp &x, Graph_Imp &y, Graph_Imp &z){
	std::vector<Triplet> vert;
	for (int i = 0; i < x.vertices.size(); ++i)
	{
		Triplet temp = x.vertices.at(i);
		temp.three = y.vertices.at(i).three;
		vert.push_back(temp);
	}
	return vert;
}
std::vector<int> sameCoordinates(std::vector<Triplet> vert, Triplet toBeFound){
	std::vector<int> ret;
	for (int i = 0; i < vert.size(); ++i)
	{
		if (vert.at(i) == toBeFound)
			ret.push_back(i);
	}
	return ret;
}
std::vector< pair<int,int> > makeEdges(Graph_Imp &x){
	std::vector< pair<int,int> > pEdges;
	std::vector<int> u,v;
	for (int i = 0; i < x.vertices.size(); ++i)
	{	
		Graph::vertex_set S = x.edges.out_neighbors(i);
		u = sameCoordinates(x.vertices, x.vertices.at(i));
		for (Graph::vertex_set::const_iterator p = S.begin(); p != S.end(); ++p)
		{
			v = sameCoordinates(x.vertices, x.vertices.at(*p));
			cout<<i<<" "<<*p<<endl;
			for (int i = 0; i < u.size(); ++i)
			{
				cout<<u[i]<<" ";
			}
			for (int i = 0; i < v.size(); ++i)
			{
				cout<<v[i]<<" ";
			}
			cout<<endl;
			for (int i = 0; i < u.size(); ++i)
			{
				for (int j = 0; j < v.size(); ++j)
				{
					pEdges.push_back(make_pair(u.at(i), v.at(j)));
					pEdges.push_back(make_pair(v.at(j), u.at(i)));
				}
			}
			for (int i = 0; i < u.size(); ++i)
			{
				for (int j = 0; j < i; ++j)
				{
					pEdges.push_back(make_pair(u.at(i), u.at(j)));
					pEdges.push_back(make_pair(u.at(j), u.at(i)));
				}
			}
			for (int i = 0; i < v.size(); ++i)
			{
				for (int j = 0; j < i; ++j)
				{
					pEdges.push_back(make_pair(v.at(i), v.at(j)));
					pEdges.push_back(make_pair(v.at(j), v.at(i)));
				}
			}
		}
	}
	return pEdges;
}
int main(int argc, char const *argv[])
{
	Graph_Imp G_on_xy,G_on_yz,G_on_xz;
	toGraphAllThree("inp_for_2.txt",G_on_xy,G_on_yz,G_on_xz);
	Graph_Imp G3D;
	G3D.vertices = make3DVertices(G_on_xy, G_on_yz, G_on_xz);
	std::vector< pair<int,int> > probEdges = makeEdges(G_on_xy);
}
