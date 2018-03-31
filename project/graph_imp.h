struct Triplet
{
  double  one, two, three;
  bool operator== (const Triplet&ref) const;
};
class Graph_Imp
{
public:
	vector<Triplet> vertices;
	Graph edges;
	Graph_Imp();
};
