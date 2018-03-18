#include <string.h>
#include <stdio.h>
#include <armadillo>
#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include "ngraph.hpp"
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

struct Triplet
{
  double one, two, three;
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

	ifstream afile;
	char ch[50];
	double x,y,z;
	int v,e;
	afile.open(f);
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
Graph_Imp Projection_isometric(Graph_Imp g){
	Graph_Imp g1;
	Graph A;
	vector<Triplet> vert;
	map <int, int> m;

	for (int i = 0; i < g.vertices.size(); ++i)
	{
		mat coordinates<<g.vertices.at(i).one<<endr<<g.vertices.at(i).two<<endr<<g.vertices.at(i).three<<endr;
		mat iso<<(sqrt(3)/2)<<(-(sqrt(3)/2))<<0<<endr<<(0.5)<<(0.5)<<(-1)<<endr;
		mat final_coordinates = iso * coordinates;
		Triplet temp = {final_coordinates(0,0),final_coordinates(0,0),0};

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

Graph_Imp Projectionyz(Graph_Imp g)
{
	Graph_Imp g1;
	Graph A;
	vector<Triplet> vert;
	map <int, int> m;

	for (int i = 0; i < g.vertices.size(); ++i)
	{
		Triplet temp = {0,g.vertices.at(i).two,g.vertices.at(i).three};

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

Graph_Imp Projectionzx(Graph_Imp g)
{
	Graph_Imp g1;
	Graph A;
	vector<Triplet> vert;
	map <int, int> m;

	for (int i = 0; i < g.vertices.size(); ++i)
	{
		Triplet temp = {g.vertices.at(i).one,0,g.vertices.at(i).three};

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

vector<Triplet> rotate_vector(vector<Triplet> vertices, Triplet normal_plane){
	vector<Triplet> rotated_vertices;
	double x = normal_plane.one;
	double y = normal_plane.two;
	double z = normal_plane.three;
	double normalizing_factor = sqrt(x*x + y*y + z*z);
	x = x/normalizing_factor;
	y = y/normalizing_factor;
	z = z/normalizing_factor;
	double d = sqrt(y*y + z*z);
	double cos_alpha = z/d;
	double sin_alpha = y/d;
	mat r_x_alpha;
	r_x_alpha<<1<<0<<0<<endr<<0<<cos_alpha<<(-sin_alpha)<<endr<<0<<sin_alpha<<cos_alpha<<endr;
	double cos_beta = d;
	double sin_beta = x;
	mat r_y_beta;
	r_y_beta<<cos_beta<<0<<(-sin_beta)<<endr<<0<<1<<0<<endr<<(sin_beta)<<0<<cos_beta<<endr;
	mat rotation_matrix = r_y_beta * r_x_alpha;
	if (d==0)
	{
		rotation_matrix<<0<<0<<0<<endr<<0<<1<<0<<endr<<0<<0<<1<<endr;
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

int main(int argc, char const *argv[])
{
	Graph_Imp G,G1,G2,G3,G_rotated;
	G = toGraph("input.txt"); //argv[0] is a char array "inputfilename.txt"
	// for (int i = 0; i < G.vertices.size(); ++i)
	// {
	// 	cout<<G.vertices.at(i).one<<","<<G.vertices.at(i).two<<","<<G.vertices.at(i).three<<endl;
	// }
	// for (Graph::const_iterator i = G.edges.begin(); i != G.edges.end(); ++i)
	// {
	// 	Graph::vertex_set Si = Graph::out_neighbors(i);
	// 	for (Graph::vertex_set::const_iterator p = Si.begin(); p != Si.end(); ++p)
	// 	{
	// 		cout<<*p<<" ";
	// 	}
	// 	cout<<endl;
	// }
	// G1 = Projectionxy(G);
	// G2 = Projectionyz(G);
	// G3 = Projectionzx(G);
	
	// for (int i = 0; i < G1.vertices.size(); ++i)
	// {
	// 	cout<<G1.vertices.at(i).one<<","<<G1.vertices.at(i).two<<","<<G1.vertices.at(i).three<<endl;
	// }
	// for (Graph::const_iterator i = G1.edges.begin(); i != G1.edges.end(); ++i)
	// {
	// 	Graph::vertex_set Si = Graph::out_neighbors(i);
	// 	for (Graph::vertex_set::const_iterator p = Si.begin(); p != Si.end(); ++p)
	// 	{
	// 		cout<<*p<<" ";
	// 	}
	// 	cout<<endl;
	// }

	// for (int i = 0; i < G2.vertices.size(); ++i)
	// {
	// 	cout<<G2.vertices.at(i).one<<","<<G2.vertices.at(i).two<<","<<G2.vertices.at(i).three<<endl;
	// }
	// for (Graph::const_iterator i = G2.edges.begin(); i != G2.edges.end(); ++i)
	// {
	// 	Graph::vertex_set Si = Graph::out_neighbors(i);
	// 	for (Graph::vertex_set::const_iterator p = Si.begin(); p != Si.end(); ++p)
	// 	{
	// 		cout<<*p<<" ";
	// 	}
	// 	cout<<endl;
	// }

	// for (int i = 0; i < G3.vertices.size(); ++i)
	// {
	// 	cout<<G3.vertices.at(i).one<<","<<G3.vertices.at(i).two<<","<<G3.vertices.at(i).three<<endl;
	// }
	// for (Graph::const_iterator i = G3.edges.begin(); i != G3.edges.end(); ++i)
	// {
	// 	Graph::vertex_set Si = Graph::out_neighbors(i);
	// 	for (Graph::vertex_set::const_iterator p = Si.begin(); p != Si.end(); ++p)
	// 	{
	// 		cout<<*p<<" ";
	// 	}
	// 	cout<<endl;
	// }
	// cout<<"--------------";
	Graph_Imp new_G = Projection_isometric(G);
	for (int i = 0; i < new_G.vertices().size(); ++i)
	{
		cout<<new_G.vertices[i].one<<" "<<new_G.vertices[i].two<<endl;
	}
	return 0;
}
