#include <math.h>
#include <QtCore>
#include <QtGui>
#include <threedtotwod.cpp>

#define PI 3.1415926536
#define SIZE 200
#define FACTOR 100

const float STEP = 2*PI/SIZE;

using namespace Qt;


int main(int argc, char *argv[])
{
   Graph_Imp G,G1,G2,G3,G_rotated;
   G = toGraph("input.txt");
   G_rotated.vertices = rotate_vector(G.vertices, topdir);
   G_rotated.edges = G.edges;
   G1 = Projectionxy(G_rotated);
   G2 = Projection_isometric(G);
   for (int i = 0; i < G1.vertices.size(); ++i)
   {
      cout<<G1.vertices[i].one<<" "<<G1.vertices[i].two<<" "<<G1.vertices[i].three<<endl;  
   }
   QApplication a(argc, argv);
   QLabel l;
   QPicture pi;
   QPainter p(&pi);

   p.setRenderHint(QPainter::Antialiasing);
   // p.setPen(QPen(Qt::black, 5, Qt::DashDotLine, Qt::RoundCap));
   p.setPen(QPen(Qt::black, 5));
   // p.drawLine(0, 0, 200, 200);
   
   float x, y, prev_x=0, prev_y=0 ;
   for (int i = 0; i < G2.vertices.size(); ++i)
   {
      Graph::vertex_set Si = G2.edges.out_neighbors(i);
      for (Graph::vertex_set::const_iterator out_vertex = Si.begin(); out_vertex != Si.end(); ++out_vertex)
      {
         p.drawLine(FACTOR*(G2.vertices[i].one),FACTOR*(G2.vertices[i].two),FACTOR*(G2.vertices[*out_vertex].one),FACTOR*(G2.vertices[*out_vertex].two));
      }
   }

 //   for (int i = 1; i < SIZE; ++i){
	// 	x = i*STEP;
	// 	y = sin(x);
	// 	p.drawLine(FACTOR*prev_x, FACTOR*prev_y, FACTOR*x, FACTOR*y);

	// 	prev_x = x;
	// 	prev_y = y;
	// }
   
   p.end(); // Don't forget this line!

   l.setPicture(pi);
   l.show();
   return a.exec();
}
