//Three_D_to_Two_D.h

/*

Input File Format:

1 					int int int   			: Front viewing direction
2 					int int int   			: Top viewing direction
3 					int int int   			: Cutting Plane
4 					int v 					: Number of vertices
5					int int int 			: Coordinates of vertices (space separated x y z coordinates; each in a new line)
.
.
.
5+v-1
5+v 				int e 					: Number of edges
5+v+1				int int 	 			: Edges in xy projection (space separated start & end vertex; each in a new line)
.
.
.
5+v+e-1

*/


#ifndef THREE_D_TO_TWO_D_H_   // if Edges.h hasn't been included yet
#define THREE_D_TO_TWO_D_H_   // including 

#include <vector>
#include "Graph_Imp.h"


class Three_D_to_Two_D
{
public:
	Three_D_to_Two_D(){}
	Graph_Imp G;
	Graph_Imp projected_xy;
	Graph_Imp projected_yz;
	Graph_Imp projected_zx;
	Graph_Imp rotatedG; 
	Graph_Imp projected_isometric;
	std::vector<std::vector<Edge>> faces;
	std::vector<Edge> hidden_xy;
	std::vector<Edge> hidden_isometric;
	Graph_Imp toGraph(std::string f);
	Graph_Imp Projection_isometric(Graph_Imp g);
	bool vertOnFace(int vert, std::vector<Edge> face);
	bool vertOutsideFace(double xp, double yp, std::vector<Edge> face, std::vector<Triplet> vert);
	bool findEdge(Edge a, std::vector<Edge> hidden);
	Graph_Imp Projectionxy(Graph_Imp g);
	Graph_Imp Projectionyz(Graph_Imp g);
	Graph_Imp Projectionzx(Graph_Imp g);
	std::vector<Triplet> rotate_vector(std::vector<Triplet> vertices, Triplet normal_plane);
};


#endif 