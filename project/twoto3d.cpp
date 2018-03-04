#include <stdio.h>

//! Defines a class needed to generate the 3D object from the 3 projections
/*!
	Takes the 3 input graphs as a string and converts it into a single 3D graph.
*/
class twoto3d
{
public:
	//! A constructor for the 2D-3D application taking the 3 input files as strings
	/*!
		Takes as input the 3 projections of the object (all in mutually perpendicular directions)
		Sets the proj1, proj2 and proj3 parameters.
	*/
	twoto3d(string proj1, string proj2, string proj3);
	//! A destructor
	~twoto3d();
	//! The probable edges
	/*!
		This contains edges which can be correct edges in the 3D view also.
	*/
	std::vector<Edge> pEdges;
	//! The probable vertices
	/*!
		Contains a labeled mapping of all probable vertices.
	*/
	std::vector<int, pair <int,int>> pVertices;
	std::vector<int, pair <int,int>> proj1;/*< Labeled projection in one plane*/
	std::vector<int, pair <int,int>> proj2;/*< Labeled projection in one plane*/
	std::vector<int, pair <int,int>> proj3;/*< Labeled projection in one plane*/
	std::vector<Graph> faces; /*< Stores all the probable faces of the 3D object*/
	//! Generates the probable vertices
	/*!
		Generates the list of probable vertices by looking through the projections proj1, proj2 and proj3.
		Looks for vertices which are labeled by the same index and adds such vertices by combining their coordinates
		in different planes.
	*/
	void generatePVertices();
	//! Generates the probable edges vector
	/*!
		Generates the list of probable edges by extending the list of edges from the 2D projections.
		Checks the edge through all the projections.
	*/
	void generatePEdges();
	//! Checks if the edge is present in all 3 views. Returns true if so.
	/*!
		\param edge Input edge whose presence in all 3 views is to be checked. 
	*/
	bool checkEdge(Edge edge);
	//! Checks if the edge is present in atleast 2 faces.	
	bool presentIn2(Edge edge);
};