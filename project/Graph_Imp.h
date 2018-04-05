//Graph_Imp.h




#ifndef GRAPH_IMP_H_   // if Graph_Imp.h hasn't been included yet
#define GRAPH_IMP_H_   // including 

#include <vector>
#include "Triplet.h"
#include "ngraph.hpp"

class Graph_Imp
{
public:
	std::vector<Triplet> vertices;
	NGraph::Graph edges;
	Graph_Imp(){}
};

#endif 