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
#define TWO_D_TO_THREE_D_H_   // including the required files


#include <vector>
#include "Triplet.h"
#include "Graph_Imp.h"
#include "gnuplot_i.hpp"


//! Defines a class needed to generate the 3D object from the 3 2D projections
/*!
	Contains the necessary data members and functions required to generate the 3D object from the 3 2D projections
*/
class Two_D_to_Three_D
{

  public:

  	//! Defines a contructor for the class Two_D_to_Three_D
	Two_D_to_Three_D(){}

	//! Waits for user input
	/*!
		Gtk Window tends to close on lack of user input <br>
		It prevents the GUI window from closing and helps in waiting for the user's response
	*/
	void wait_for_key ();

	//! Converts to 3D wireframe
	/*!
		Takes the 3 input graphs and combines them to form 3D wireframe model
		\param f
		\param x_g
		\param y_g
		\param z_g
	*/
	void toGraphAllThree(char* f, Graph_Imp &x_g, Graph_Imp &y_g, Graph_Imp &z_g);

	//! Makes 3D vertices
	/*!
		Takes the 3 2D vertex inputs and converts them to 3D vertices
		\param x
		\param y
		\param z
	*/
	std::vector<Triplet> make3DVertices(Graph_Imp &x, Graph_Imp &y, Graph_Imp &z);

	//! Checks if 2 vertices have a common coordinate
	/*!
		\param vert
		\param toBeFound 
	*/
	std::vector<int> sameCoordinates(std::vector<Triplet> vert, Triplet toBeFound);

	//! Defines a class needed to generate the 3D object from the 3 projections
	/*!
		Takes the 3 input graphs as a string and converts it into a single 3D graph.
	*/
	std::vector<std::pair<int,int> > makeEdges(Graph_Imp &x);

	//! Defines a class needed to generate the 3D object from the 3 projections
	/*!
		Takes the 3 input graphs as a string and converts it into a single 3D graph.
	*/
	std::vector<std::pair<int, int> > intersection(std::vector<std::pair<int, int> > a, std::vector<std::pair<int, int> > b, std::vector<std::pair<int, int> > c);
	
	//! Defines a class needed to generate the 3D object from the 3 projections
	/*!
		Takes the 3 input graphs as a string and converts it into a single 3D graph.
	*/
	Graph_Imp makethreed(Graph_Imp G_on_xy, Graph_Imp G_on_yz, Graph_Imp G_on_xz);

	//! Defines a class needed to generate the 3D object from the 3 projections
	/*!
		Takes the 3 input graphs as a string and converts it into a single 3D graph.
	*/
	void show_gnu_plot(Graph_Imp G3D);

};


#endif 