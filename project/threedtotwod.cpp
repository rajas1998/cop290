#include <string.h>
#include <stdio.h>
#include <armadillo>
#include <iostream>
#include <fstream>
#include <NGraph>

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

vector<Triplet> vertices;

Graph toGraph(char f[])
{
	fstream afile;
	afile.open(f,ios::in);
	while(afile){
	}
	afile.close();
}

int main(int argc, char const *argv[])
{
	Graph G;
	G = toGraph(argv[0]); //argv[0] is a char array "inputfilename.txt"
}
