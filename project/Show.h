//Show.h



#ifndef SHOW_H_   // if Show.h hasn't been included yet
#define SHOW_H_   // including 

#define WIDTH 700
#define HEIGHT 700

#include <vector>
#include "Graph_Imp.h"
#include "Triplet.h"
#include <QtCore>
#include <QtGui>
#include "Three_D_to_Two_D.h"


class Show
{

public:

	Show(){}

	Graph_Imp set_acc_to_ranges(Graph_Imp g, int mode);
	bool findEdgeInVector(Edge a, std::vector<Edge> hidden);
	void drawGraph(Graph_Imp g, Qt::QPainter &p, std::vector<Edge> hidden, bool hide);
	int show_qt_projections(Three_D_to_Two_D &T, Triplet topdir);

};


#endif 