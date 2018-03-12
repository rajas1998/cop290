#include <string.h>
#include <stdio.h>
#include <armadillo>
#include <iostream>
#include <fstream>
#include "ngraph.hpp"
#include <algorithm>
#include <map>
#include <math.h>
//using namespace NGraph;
using namespace std;
using namespace arma;

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
  double one, two, three;
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
vector<Triplet> rotate_vector(vector<Triplet> vertices){
	vector<Triplet> rotated_vertices;
	for (int i = 0; i < vertices.size(); ++i)
	{
		mat coordinates;
		double x = vertices.at(i).one;
		double y = vertices.at(i).two;
		double z = vertices.at(i).three;
		coordinates<<x<<endr<<y<<endr<<z<<endr;
		double d = sqrt(y*y + z*z);
		double cos_alpha = z/d;
		double sin_alpha = y/d;
		mat r_x_alpha;
		r_x_alpha<<1<<0<<0<<endr<<0<<cos_alpha<<(-sin_alpha)<<endr<<0<<sin_alpha<<cos_alpha<<endr;
		mat rotated_x = r_x_alpha * coordinates;
		double cos_beta = d;
		double sin_beta = x;
		mat r_y_beta;
		r_y_beta<<cos_beta<<0<<(-sin_beta)<<endr<<0<<1<<0<<endr<<(sin_beta)<<0<<cos_beta<<endr;
		mat rotated_y_x = r_y_beta * rotated_x;
		Triplet temp = {rotated_y_x(0,0), rotated_y_x(1,0), rotated_y_x(2,0)};
		rotated_vertices.push_back(temp);
	}
	return rotated_vertices;
}
int main(int argc, char const *argv[])
{
	std::vector<Triplet> vertices;
	Triplet temp = {1/sqrt(3),1/sqrt(3),1/sqrt(3)};
	vertices.push_back(temp);
	vertices.push_back(temp);
	cout<<rotate_vector(vertices).at(1).three;
}
