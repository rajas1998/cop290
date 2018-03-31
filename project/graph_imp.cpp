#include "graph_imp.h"
using namespace std;

bool Triplet::operator== (const Triplet&ref) const {
	return (ref.one == one)&&(ref.two == two)&&(ref.three==three);
}


Graph_Imp::Graph_Imp(){
}
