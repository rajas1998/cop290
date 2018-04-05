//Two_D_to_Three_D.h

/*

Input File Format:

1						int v		    			: Number of vertices (is a constant through all the projections)
2 						int int int		    		: Coordinates of vertices in xy projection (space separated x y z coordinates; each in a new line)
.
.
2+v-1 
2+v 					int exy						: Number of edges in xy projection
2+v+1 					int int 	 				: Edges in xy projection (space separated start & end vertex; each in a new line)
.
.
2+v+exy-1
2+v+exy 				int int int					: Coordinates of vertices in yz projection (space separated x y z coordinates; each in a new line)
.
.
2+v+exy+v-1				
2+v+exy+v 				int eyz 					: Number of edges in yz projection
2+v+exy+v+1 			int int 					: Edges in yz projection (space separated start & end vertex; each in a new line)
.
.
2+v+exy+v+eyz-1
2+v+exy+v+eyz			int int int					: Coordinates of vertices in zx projection (space separated x y z coordinates; each in a new line)
.
.
2+v+exy+v+eyz+v-1				
2+v+exy+v+eyz+v 		int ezx 					: Number of edges in zx projection
2+v+exy+v+eyz+v+1 		int int 					: Edges in zx projection (space separated start & end vertex; each in a new line)
.
.
2+v+exy+v+eyz+v+ezx-1


*/


#ifndef TWO_D_TO_THREE_D_H_   // if Two_D_to_Three_D.h hasn't been included yet
#define TWO_D_TO_THREE_D_H_   // including

#include <vector>
#include "Triplet.h"
#include "Graph_Imp.h"
#include "gnuplot_i.hpp"


class Two_D_to_Three_D
{

public:

	Two_D_to_Three_D(){}

	void wait_for_key ();
	void toGraphAllThree(char* f, Graph_Imp &x_g, Graph_Imp &y_g, Graph_Imp &z_g);
	std::vector<Triplet> make3DVertices(Graph_Imp &x, Graph_Imp &y, Graph_Imp &z);
	std::vector<int> sameCoordinates(std::vector<Triplet> vert, Triplet toBeFound);
	std::vector<std::pair<int,int> > makeEdges(Graph_Imp &x);
	std::vector<std::pair<int, int> > intersection(std::vector<std::pair<int, int> > a, std::vector<std::pair<int, int> > b, std::vector<std::pair<int, int> > c);
	Graph_Imp makethreed(Graph_Imp G_on_xy, Graph_Imp G_on_yz, Graph_Imp G_on_xz);
	void show_gnu_plot(Graph_Imp G3D);

};


#endif 