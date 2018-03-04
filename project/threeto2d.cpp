#include <string.h>
#include <stdio.h>

//! Data structure to store graph edges
/*
	Contains an edge between src and dest. 
	src and dest are labels that are provided in vertices. 
*/
struct Edge {
    int src; /*< Labeled source of the edge*/
    int dest; /*< Labeled destination of the edge*/
};
//! Data structure to store direction vector
struct Direction
{
	int x; /*< i component of the vector*/
	int y; /*< j component of the vector*/
	int z; /*< k component of the vector*/
};
//! Class for storing a graph
class Graph{
	public:
		//! Vector for vertices.
	    /*!
	      The vertices are indexed by their position in the vector and this is used to identify a vertex.
	    */
		std::vector<pair <int,int>> vertices;
		//! Vector for edges.
	    /*!
	      \sa Edge
	    */
		std::vector<Edge> edges;
		//! Finds the chorldless cycles in the graph and returns as a list.
		/*!
			Looks at the graph and finds all shortest cycles which do not have a chord
			(line connected any two vertices in the graph). These represent faces and are
			returned in the form of a vector of all the graphs.
		*/
		std::vector<Graph>  findChordlessCycles();
};
//! Defines a class needed to generate the projections of the input graph
/*!
	Takes the input graph from the file as a string and makes the necessary manipulations to output it as a projected graph.
	Can also find the isometric projection of a graph if asked for.
*/
class threeto2d
{
	public:
		//! A constructor for the 3d to 2d application
	    /*!
	      Takes the file string as an input and sets the inputG field.
	      \param inp_from_file string input which is converted into a graph data structure.
	      \sa inputG
	    */
		threeto2d(string inp_from_file);
		//! a destructor
		~threeto2d();
		//! Stores the input 3D file as a graph
		Graph inputG;
		//! Stores the viweing direction
		Direction viweingDirection;
		//! Stores the translated graph
		Graph translatedG;
		//! Stores the rotated graph
		Graph rotatedG;
		//! Stores the projected graph in x direction
		Graph projectedGx;
		//! Stores the projected graph in y direction
		Graph projectedGy;
		//! Stores the projected graph in z direction
		Graph projectedGz;
		//! Stores the cut graph with new edges if required
		Graph refinedG;
		//! Translates the graph according to the parameters provided
		/*!
			Sets the translatedG parameter
			\param toBeTranslated the input graph which has to be translated 
			\param x_c
			\param y_c
			\param z_c
		*/
		void translate(Graph toBeTranslated, int x_c, int y_c, int z_c);
		//! Translates the graph according to the parameters provided
		/*!
			Sets the rotatedG parameter
			\param toBeRotated the input graph which has to be rotated 
		*/
		void rotate(Graph toBeRotated);
		//! Projects the graph according to the viewing direction
		/*!
			Sets the projectedG parameter
			\param toBeProjected the input graph which has to be projected 
		*/
		void project(Graph toBeProjected);
		//! Cuts the object with the plane and makes the required edges.
		/*!
			Sets the refinedG parameter.
			\param toBeCut defines the graph which has to be cut.
			\param normal Defines the vector normal to the cutting plane
			\param point Defines a point on the plane
		*/
		void findNewEdges(Graph toBeCut, Direction normal, Direction point);
		//! Takes the isometric projection
		void projectIsometric(Graph toBeIsometric);
};