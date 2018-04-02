#include <string.h>
#include <stdio.h>
#include <armadillo>
#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include "ngraph.hpp"
#include "Triplet.h"
#include "Edges.h"
#include "Graph_Imp.h"
#include "ThreeDtoTwoD.h"

using namespace NGraph;
using namespace arma;
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


// Triplet frontdir;
// Triplet topdir;
// Triplet cuttingplane;
<<<<<<< HEAD


 	Graph_Imp Threedtotwod::toGraph(string f)
=======
class Threedtotwod
{
public:
	Threedtotwod(){}
	Graph_Imp G;
	Graph_Imp projected_xy;
	Graph_Imp projected_yz;
	Graph_Imp projected_zx;
	Graph_Imp rotatedG; 
	Graph_Imp projected_isometric;
	vector<vector<Edge>> faces;
	vector<Edge> hidden_xy;
	vector<Edge> hidden_isometric;
	Graph_Imp toGraph(string f)
>>>>>>> 09698def103538f3b87a9292198808bae1604553
	{
		Graph A;
		vector<Triplet> vert;

		ifstream afile;
		char ch[50];
		double x,y,z;
		int v,e;
		afile.open(f);
		// afile>>x>>y>>z;
		// frontdir.one=x;
		// frontdir.two=y;
		// frontdir.three=z;
		// afile>>x>>y>>z;
		// topdir.one=x;
		// topdir.two=y;
		// topdir.three=z;
		// afile>>x>>y>>z;
		// cuttingplane.one=x;
		// cuttingplane.two=y;
		// cuttingplane.three=z;
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
		int num;
		afile>>num;
		for (int i = 0; i < num; ++i)
		{
			int sz;
			afile>>sz;
			vector<Edge> temp_face;
			for (int j = 0; j < sz; ++j)
			{
				int src, dest;
				afile>>src>>dest;
				Edge temp = {src, dest};
				temp_face.push_back(temp);
			}
			faces.push_back(temp_face);
		}
		afile.close();
		Graph_Imp g;
		g.vertices=vert;
		g.edges=A;
		return g;
	}

	Graph_Imp Threedtotwod::Projection_isometric(Graph_Imp g)
	{
		Graph_Imp g1;
		vector<Triplet> vert;

		for (int i = 0; i < g.vertices.size(); ++i)
		{	
			mat coordinates;
			coordinates<<g.vertices.at(i).one<<endr<<g.vertices.at(i).two<<endr<<g.vertices.at(i).three<<endr;
			mat iso;
			iso<<(sqrt(3)/2)<<(-(sqrt(3)/2))<<0<<endr<<(0.5)<<(0.5)<<(-1)<<endr;
			mat final_coordinates = iso * coordinates;
			Triplet temp = {final_coordinates(0,0),final_coordinates(1,0),0};
			vert.push_back(temp);    
		}
		g1.vertices=vert;
		g1.edges=g.edges;
		std::vector<int> sorted;
		for (int i = 0; i < vert.size(); ++i)
		{
			sorted.push_back(i);
		}
		for (int i = 0; i < g.vertices.size(); ++i)
		{
			for (int j = 0; j < g.vertices.size()-1-i; ++j)
			{
				if (g.vertices[sorted[j]].three > g.vertices[sorted[j+1]].three)
				{
					int temp = sorted[j];
					sorted[j] = sorted[j+1];
					sorted[j+1] = temp;
				}
			}
		}
		std::vector<Edge> madeTillNow;
		std::vector<Edge> hiddenEdges;
		std::vector<bool> doneFaces;
		for (int i = 0; i < faces.size(); ++i)
		{
			doneFaces.push_back(false);
		}
		for (int i = 0; i < sorted.size(); ++i)
		{
			Graph::vertex_set S = g.edges.out_neighbors(sorted[i]);
			for (Graph::vertex_set::const_iterator p = S.begin(); p != S.end(); ++p)
			{
				for (int ptr = 0; ptr < i; ++ptr)
				{
					if (*p == sorted[ptr]){	
						Edge temp = {sorted[i],*p};
						madeTillNow.push_back(temp);
					}
				}
			}
			for (int j = 0; j < faces.size(); ++j)
			{
				if (!doneFaces[j]){
					bool completed = true;
					for (int k = 0; k < faces[j].size(); ++k)
					{
						bool foundEdge = false;
						for (int p = 0; p < madeTillNow.size(); ++p)
						{
							if ((faces[j][k].src==madeTillNow[p].src && faces[j][k].dest==madeTillNow[p].dest) || (faces[j][k].src==madeTillNow[p].dest && faces[j][k].dest==madeTillNow[p].src)){
								foundEdge = true;
								break;
							}
						}
						if (!foundEdge){
							completed = false;
							break;
						}
					}
					if (completed){
						doneFaces[j] = true;
						for (int k = 0; k < madeTillNow.size(); ++k)
						{
							if (vertOnFace(madeTillNow[k].src, faces[j]))
							{
								if (!vertOnFace(madeTillNow[k].dest, faces[j])){
									if (!vertOutsideFace(vert[madeTillNow[k].dest].one, vert[madeTillNow[k].dest].two, faces[j], vert)){
										hiddenEdges.push_back(madeTillNow[k]);
									}
								}
								else {
									if (!findEdge(madeTillNow[k], faces[j])){
										hiddenEdges.push_back(madeTillNow[k]);
									}

								}
							}
							else 
							{
								if (vertOnFace(madeTillNow[k].dest, faces[j])){
									if (!vertOutsideFace(vert[madeTillNow[k].src].one, vert[madeTillNow[k].src].two, faces[j], vert)){
										hiddenEdges.push_back(madeTillNow[k]);
									}
								}
								else {
									if ((!vertOutsideFace(vert[madeTillNow[k].src].one, vert[madeTillNow[k].src].two, faces[j], vert)) && (!vertOutsideFace(vert[madeTillNow[k].dest].one, vert[madeTillNow[k].dest].two, faces[j], vert))){
										hiddenEdges.push_back(madeTillNow[k]);
									}
								}
							}
						}
					}
				}
			}
		}
		hidden_isometric = hiddenEdges;
		return g1;
	}

	bool Threedtotwod::vertOnFace(int vert, std::vector<Edge> face)
	{
		for (int p = 0; p < face.size(); ++p)
		{
			if (vert == face[p].src || vert == face[p].dest)
			{
				return true;
			}
		}
		return false;
	}

	bool Threedtotwod::vertOutsideFace(double xp, double yp, std::vector<Edge> face, std::vector<Triplet> vert)
	{
		int countInt = 0;
		for (int p = 0; p < face.size(); ++p)
		{
			double x1 = vert[face[p].src].one;
			double y1 = vert[face[p].src].two;
			double x2 = vert[face[p].dest].one;
			double y2 = vert[face[p].dest].two;
			if ((xp==x1 && yp==y1) || (xp==x2 && yp==y2)){
				// cout<<"coincide "<<x1<<","<<y1<<endl;
				return false;
			}
			double x = x1 + ((yp - y1) * (x2 - x1))/(y2 - y1);
			if (x > xp && ((yp>y1 && yp<y2) || (yp<y1 && yp>y2)) ){
				countInt++;
			}
		}
		// cout<<"Num of inter "<<countInt<<endl;
		if (countInt%2 == 1){
			return false;
		}
		else return true;
	}

	bool Threedtotwod::findEdge(Edge a, std::vector<Edge> hidden)
	{
	   for (int i = 0; i < hidden.size(); ++i)
	   {
	      if ((a.src == hidden[i].src && a.dest == hidden[i].dest) || (a.dest == hidden[i].src && a.src == hidden[i].dest)){
	         return true;
	      }
	   }
	   return false;
	}

	Graph_Imp Threedtotwod::Projectionxy(Graph_Imp g)
	{
		Graph_Imp g1;
		vector<Triplet> vert;

		for (int i = 0; i < g.vertices.size(); ++i)
		{
			Triplet temp = {g.vertices.at(i).one,g.vertices.at(i).two,0};
			vert.push_back(temp);
		}
		g1.vertices = vert;
		g1.edges = g.edges;
		std::vector<int> sorted;
		for (int i = 0; i < vert.size(); ++i)
		{
			sorted.push_back(i);
		}
		for (int i = 0; i < g.vertices.size(); ++i)
		{
			for (int j = 0; j < g.vertices.size()-1-i; ++j)
			{
				if (g.vertices[sorted[j]].three > g.vertices[sorted[j+1]].three)
				{
					int temp = sorted[j];
					sorted[j] = sorted[j+1];
					sorted[j+1] = temp;
				}
			}
		}
		// cout<<"Sorted vexrtex set"<<endl;
		// for (int i = 0; i < sorted.size(); ++i)
		// {
		// 	cout<<sorted[i]<<" ";
		// }
		// cout<<endl;
		std::vector<Edge> madeTillNow;
		std::vector<Edge> hiddenEdges;
		std::vector<bool> doneFaces;
		for (int i = 0; i < faces.size(); ++i)
		{
			doneFaces.push_back(false);
		}
		for (int i = 0; i < sorted.size(); ++i)
		{
			Graph::vertex_set S = g.edges.out_neighbors(sorted[i]);
			for (Graph::vertex_set::const_iterator p = S.begin(); p != S.end(); ++p)
			{
				for (int ptr = 0; ptr < i; ++ptr)
				{
					if (*p == sorted[ptr]){	
						Edge temp = {sorted[i],*p};
						madeTillNow.push_back(temp);
					}
				}
			}
			// cout<<"Round "<<i<<endl;
			// for (int rajas = 0; rajas < madeTillNow.size(); ++rajas)
			// {
			// 	cout<<madeTillNow[rajas].src<<","<<madeTillNow[rajas].dest<<" ";
			// }
			// cout<<endl;
			for (int j = 0; j < faces.size(); ++j)
			{
				if (!doneFaces[j]){
					bool completed = true;
					for (int k = 0; k < faces[j].size(); ++k)
					{
						bool foundEdge = false;
						for (int p = 0; p < madeTillNow.size(); ++p)
						{
							if ((faces[j][k].src==madeTillNow[p].src && faces[j][k].dest==madeTillNow[p].dest) || (faces[j][k].src==madeTillNow[p].dest && faces[j][k].dest==madeTillNow[p].src)){
								foundEdge = true;
								break;
							}
						}
						if (!foundEdge){
							completed = false;
							break;
						}
					}
					if (completed){
						// cout<<"Round "<<i<<" face number "<<j<<endl;
						doneFaces[j] = true;
						for (int k = 0; k < madeTillNow.size(); ++k)
						{
							if (vertOnFace(madeTillNow[k].src, faces[j]))
							{
								if (!vertOnFace(madeTillNow[k].dest, faces[j])){
									if (!vertOutsideFace(vert[madeTillNow[k].dest].one, vert[madeTillNow[k].dest].two, faces[j], vert)){
										hiddenEdges.push_back(madeTillNow[k]);
										// cout<<"h1 "<<madeTillNow[k].src<<","<<madeTillNow[k].dest<<endl;
									}
								}
								else {
									if (!findEdge(madeTillNow[k], faces[j])){
										hiddenEdges.push_back(madeTillNow[k]);
										// cout<<"h2 "<<madeTillNow[k].src<<","<<madeTillNow[k].dest<<endl;
									}

								}
							}
							else 
							{
								if (vertOnFace(madeTillNow[k].dest, faces[j])){
									if (!vertOutsideFace(vert[madeTillNow[k].src].one, vert[madeTillNow[k].src].two, faces[j], vert)){
										hiddenEdges.push_back(madeTillNow[k]);
										// cout<<"h3 "<<madeTillNow[k].src<<","<<madeTillNow[k].dest<<endl;
									}
								}
								else {
									if ((!vertOutsideFace(vert[madeTillNow[k].src].one, vert[madeTillNow[k].src].two, faces[j], vert)) && (!vertOutsideFace(vert[madeTillNow[k].dest].one, vert[madeTillNow[k].dest].two, faces[j], vert))){
										hiddenEdges.push_back(madeTillNow[k]);
										// cout<<"h4 "<<madeTillNow[k].src<<","<<madeTillNow[k].dest<<endl;
									}
								}
							}
						}
					}
				}
			}
		}
		// cout<<"Hidden Printing"<<endl;
		// for (int i = 0; i < g.vertices.size(); ++i)
		// {
		// 	cout<<g.vertices[i].one<<","<<g.vertices[i].two<<","<<g.vertices[i].three<<endl;
		// }
		// cout<<"----"<<endl;
		// for (int i = 0; i < hiddenEdges.size(); ++i)
		// {
		// 	cout<<hiddenEdges[i].src<<","<<hiddenEdges[i].dest<<endl;
		// }
		hidden_xy = hiddenEdges;
		return g1;
	}

	Graph_Imp Threedtotwod::Projectionyz(Graph_Imp g)
	{
		Graph_Imp g1;
		vector<Triplet> vert;

		for (int i = 0; i < g.vertices.size(); ++i)
		{
			Triplet temp = {0,g.vertices.at(i).two,g.vertices.at(i).three};
		    vert.push_back(temp);
		}
		g1.vertices = vert;
		g1.edges = g.edges;
		return g1;
	}

	Graph_Imp Threedtotwod::Projectionzx(Graph_Imp g)
	{
		Graph_Imp g1;
		vector<Triplet> vert;

		for (int i = 0; i < g.vertices.size(); ++i)
		{
			Triplet temp = {g.vertices.at(i).one,0,g.vertices.at(i).three};
		    vert.push_back(temp);
		}
		g1.vertices = vert;
		g1.edges = g.edges;
		return g1;
	}

	vector<Triplet> Threedtotwod::rotate_vector(vector<Triplet> vertices, Triplet normal_plane)
	{
		vector<Triplet> rotated_vertices;
		double x = normal_plane.one;
		double y = normal_plane.two;
		double z = normal_plane.three;
		double normalizing_factor = sqrt(x*x + y*y + z*z);
		x = x/normalizing_factor;
		y = y/normalizing_factor;
		z = z/normalizing_factor;
		double d = sqrt(y*y + z*z);
		mat rotation_matrix;
		if (d==0)
		{
			rotation_matrix<<1<<0<<0<<endr<<0<<1<<0<<endr<<0<<0<<1<<endr;
		}
		else {
			double cos_alpha = z/d;
			double sin_alpha = y/d;
			mat r_x_alpha;
			r_x_alpha<<1<<0<<0<<endr<<0<<cos_alpha<<(-sin_alpha)<<endr<<0<<sin_alpha<<cos_alpha<<endr;
			double cos_beta = d;
			double sin_beta = x;
			mat r_y_beta;
			r_y_beta<<cos_beta<<0<<(-sin_beta)<<endr<<0<<1<<0<<endr<<(sin_beta)<<0<<cos_beta<<endr;
			rotation_matrix = r_y_beta * r_x_alpha;
		}
		for (int i = 0; i < vertices.size(); ++i)
		{
			mat coordinates;
			coordinates<<vertices[i].one<<endr<<vertices[i].two<<endr<<vertices[i].three<<endr;
			mat rotated_y_x = rotation_matrix * coordinates;
			Triplet temp = {rotated_y_x(0,0), rotated_y_x(1,0), rotated_y_x(2,0)};
			rotated_vertices.push_back(temp);
		}
		return rotated_vertices;
	}
	

// int main(int argc, char const *argv[])
// {
// 	Graph_Imp G,G1,G2,G3,G_rotated;
// 	Threedtotwod T;
// 	T.G = T.toGraph("input.txt"); //argv[0] is a char array "inputfilename.txt"
// 	// for (int i = 0; i < G.vertices.size(); ++i)
// 	// {
// 	// 	cout<<G.vertices.at(i).one<<","<<G.vertices.at(i).two<<","<<G.vertices.at(i).three<<endl;
// 	// }
// 	// for (Graph::const_iterator i = G.edges.begin(); i != G.edges.end(); ++i)
// 	// {
// 	// 	Graph::vertex_set Si = Graph::out_neighbors(i);
// 	// 	for (Graph::vertex_set::const_iterator p = Si.begin(); p != Si.end(); ++p)
// 	// 	{
// 	// 		cout<<*p<<" ";
// 	// 	}
// 	// 	cout<<endl;
// 	// }
// 	// G1 = Projectionxy(G);
// 	// G2 = Projectionyz(G);
// 	// G3 = Projectionzx(G);
	
// 	// for (int i = 0; i < G1.vertices.size(); ++i)
// 	// {
// 	// 	cout<<G1.vertices.at(i).one<<","<<G1.vertices.at(i).two<<","<<G1.vertices.at(i).three<<endl;
// 	// }
// 	// for (Graph::const_iterator i = G1.edges.begin(); i != G1.edges.end(); ++i)
// 	// {
// 	// 	Graph::vertex_set Si = Graph::out_neighbors(i);
// 	// 	for (Graph::vertex_set::const_iterator p = Si.begin(); p != Si.end(); ++p)
// 	// 	{
// 	// 		cout<<*p<<" ";
// 	// 	}
// 	// 	cout<<endl;
// 	// }

// 	// for (int i = 0; i < G2.vertices.size(); ++i)
// 	// {
// 	// 	cout<<G2.vertices.at(i).one<<","<<G2.vertices.at(i).two<<","<<G2.vertices.at(i).three<<endl;
// 	// }
// 	// for (Graph::const_iterator i = G2.edges.begin(); i != G2.edges.end(); ++i)
// 	// {
// 	// 	Graph::vertex_set Si = Graph::out_neighbors(i);
// 	// 	for (Graph::vertex_set::const_iterator p = Si.begin(); p != Si.end(); ++p)
// 	// 	{
// 	// 		cout<<*p<<" ";
// 	// 	}
// 	// 	cout<<endl;
// 	// }

// 	// for (int i = 0; i < G3.vertices.size(); ++i)
// 	// {
// 	// 	cout<<G3.vertices.at(i).one<<","<<G3.vertices.at(i).two<<","<<G3.vertices.at(i).three<<endl;
// 	// }
// 	// for (Graph::const_iterator i = G3.edges.begin(); i != G3.edges.end(); ++i)
// 	// {
// 	// 	Graph::vertex_set Si = Graph::out_neighbors(i);
// 	// 	for (Graph::vertex_set::const_iterator p = Si.begin(); p != Si.end(); ++p)
// 	// 	{
// 	// 		cout<<*p<<" ";
// 	// 	}
// 	// 	cout<<endl;
// 	// }
// 	// cout<<"--------------";
// 	T.projected_isometric = T.Projection_isometric(T.G);
// 	for (int i = 0; i < T.projected_isometric.vertices.size(); ++i)
// 	{
// 		cout<<T.projected_isometric.vertices[i].one<<" "<<T.projected_isometric.vertices[i].two<<endl;
// 	}
// 	cout<<T.projected_isometric.edges;
// 	return 0;
// }
