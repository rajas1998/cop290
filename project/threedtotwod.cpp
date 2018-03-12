#include <string.h>
#include <stdio.h>
//#include <armadillo>
#include <iostream>
#include <fstream>
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
  int  one_, two_, three_;
};

Triplet frontdir;
Triplet topdir;
Triplet cuttingplane;
vector<Triplet> vertices;

Graph toGraph(char f[])
{
	Graph A;
	fstream afile;
	char ch[50];
	int fx,fy,fz,gx,gy,gz,v,e;
	afile.open(f,ios::in);
	afile>>fx>>fy>>fz;
	frontdir.one_=fx;
	frontdir.two_=fy;
	frontdir.three_=fz;
	afile>>fx>>fy>>fz;
	topdir.one_=fx;
	topdir.two_=fy;
	topdir.three_=fz;
	afile>>fx>>fy>>fz;
	cuttingplane.one_=fx;
	cuttingplane.two_=fy;
	cuttingplane.three_=fz;
	afile>>v;
	for (int i = 0; i < v; ++i)
	{
		afile>>fx>>fy>>fz;
		Triplet temp = {fx,fy,fz};
		vertices.push_back(temp);
	}
	afile>>e;
	for (int i = 0; i < e; ++i)
	{
		afile>>fx>>fy>>fz>>gx>>gy>>gz;
		Triplet temp1 = {fx,fy,fz};
		Triplet temp2 = {gx,gy,gz};
		int v1 = find (vertices.begin(), vertices.end(), temp1) - vertices.begin();
		int v2 = find (vertices.begin(), vertices.end(), temp2) - vertices.begin();
		A.insert_edge(v1,v2);
	}
	afile.close();
}

int main(int argc, char const *argv[])
{
	Graph G;
	G = toGraph(argv[0]); //argv[0] is a char array "inputfilename.txt"
}
