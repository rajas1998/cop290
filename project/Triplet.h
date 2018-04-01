//Triplet.h




#ifndef TRIPLET_H_   // if Triplet.h hasn't been included yet
#define TRIPLET_H_   // including 

struct Triplet
{
  double one, two, three;
  bool operator== (const Triplet&ref) const {
  	return (ref.one == one)&&(ref.two == two)&&(ref.three==three);
  }
};

#endif 