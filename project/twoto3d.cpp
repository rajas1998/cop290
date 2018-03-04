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
	/*
		This contains edges which can be correct edges in the 3D view also.
	*/
	Vector<Edge> pEdges;
	Vector<int, pair <int,int>> proj1;/*< Labeled projection in one plane*/
	Vector<int, pair <int,int>> proj2;/*< Labeled projection in one plane*/
	Vector<int, pair <int,int>> proj3;/*< Labeled projection in one plane*/
	//! Generates the probable vertices
	/*!
		Generates the list of probable vertices by looking through the projections proj1, proj2 and proj3.
		Looks for vertices which are labeled by the same index and adds such vertices by combining their coordinates
		in different planes.
	*/
	void generatePVertices();
	//! Checks if the edge is present in all 3 views. Returns true if so.
	/*!
		\param edge Input edge whose presence in all 3 views is to be checked. 
	*/
	bool checkEdge(Edge edge);	

};