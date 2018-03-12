#include <string.h>
#include <stdio.h>
//#include <armadillo>
#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include "ngraph.hpp"
using namespace NGraph;
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

Triplet frontdir;
Triplet topdir;
Triplet cuttingplane;

Graph_Imp toGraph(string f)
{
	Graph A;
	vector<Triplet> vert;

	fstream afile;
	char ch[50];
	int x,y,z,v,e;
	afile.open(f,ios::in);
	afile>>x>>y>>z;
	frontdir.one=x;
	frontdir.two=y;
	frontdir.three=z;
	afile>>x>>y>>z;
	topdir.one=x;
	topdir.two=y;
	topdir.three=z;
	afile>>x>>y>>z;
	cuttingplane.one=x;
	cuttingplane.two=y;
	cuttingplane.three=z;
	afile>>v;
	for (int i = 0; i < v; ++i)
	{
		afile>>x>>y>>z;
		Triplet temp = {x,y,z};
		vert.push_back(temp);
	}
	afile>>e;
	for (int i = 0; i < e; ++i)
	{
		afile>>x>>y;
		A.insert_edge(x,y);
		A.insert_edge(y,x);
		// afile>>fx>>fy>>fz>>gx>>gy>>gz;
		// Triplet temp1 = {fx,fy,fz};
		// Triplet temp2 = {gx,gy,gz};
		// int v1 = find (vertices.begin(), vertices.end(), temp1) - vertices.begin();
		// int v2 = find (vertices.begin(), vertices.end(), temp2) - vertices.begin();
		// A.insert_edge(v1,v2);
	}
	afile.close();
	Graph_Imp g;
	g.vertices=vert;
	g.edges=A;
	return g;
}

Graph_Imp Projectionxy(Graph_Imp g)
{
	Graph_Imp g1;
	Graph A;
	vector<Triplet> vert;
	map <int, int> m;

	for (int i = 0; i < g.vertices.size(); ++i)
	{
		Triplet temp = {g.vertices.at(i).one,g.vertices.at(i).two,0};

		//This step makes the new vertices and maps old vertices to new ones

		vector<Triplet>::iterator iter;
		iter = find(vert.begin(), vert.end(), temp);
	    if(iter != vert.end())
	    {
	    	m[i]=(iter - vert.begin());
	        //m.insert(pair <int, int> (i,(iter - vert.begin())) );
	    }
	    else
	    {
	        m[i]=(vert.size());
	        vert.push_back(temp);
			//m.insert(pair <int, int> (i,vert.size()) );
	    }
	}
	
 //    map <int, int> :: iterator itr;
 //    cout << "\nThe map m is : \n";
 //    cout << "\tKEY\tELEMENT\n";
 //    for (itr = m.begin(); itr != m.end(); ++itr)
 //    {
 //        cout  <<  '\t' << itr->first 
 //              <<  '\t' << itr->second << '\n';
 //    }

	//Modifying old graph into new
	int k=0;
	for (Graph::const_iterator i = g.edges.begin(); i != g.edges.end(); ++i,++k)
	{
		Graph::vertex_set S = Graph::out_neighbors(i);
		for (Graph::vertex_set::const_iterator p = S.begin(); p != S.end(); ++p)
		{
			int d=m[*p];
			int w=m[k];
			if(d!=w){
			A.insert_edge(w,d);
			A.insert_edge(d,w);
			}
		}
	}
	g1.vertices=vert;
	g1.edges=A;
	return g1;
}

int main(int argc, char const *argv[])
{
	Graph_Imp G,G1;
	G = toGraph("input.txt"); //argv[0] is a char array "inputfilename.txt"
	for (int i = 0; i < G.vertices.size(); ++i)
	{
		cout<<G.vertices.at(i).one<<","<<G.vertices.at(i).two<<","<<G.vertices.at(i).three<<endl;
	}
	for (Graph::const_iterator i = G.edges.begin(); i != G.edges.end(); ++i)
	{
		Graph::vertex_set Si = Graph::out_neighbors(i);
		for (Graph::vertex_set::const_iterator p = Si.begin(); p != Si.end(); ++p)
		{
			cout<<*p<<" ";
		}
		cout<<endl;
	}
	G1 = Projectionxy(G);
	for (int i = 0; i < G1.vertices.size(); ++i)
	{
		cout<<G1.vertices.at(i).one<<","<<G1.vertices.at(i).two<<","<<G1.vertices.at(i).three<<endl;
	}
	for (Graph::const_iterator i = G1.edges.begin(); i != G1.edges.end(); ++i)
	{
		Graph::vertex_set Si = Graph::out_neighbors(i);
		for (Graph::vertex_set::const_iterator p = Si.begin(); p != Si.end(); ++p)
		{
			cout<<*p<<" ";
		}
		cout<<endl;
	}
	return 0;
}
