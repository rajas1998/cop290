CXX=g++
LFLAGS        = -m64
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. 
LIBS          = -L/usr/lib/x86_64-linux-gnu/ -lm -lQtGui -larmadillo
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB
OBJECTS       = main.o
TARGET        = draw

all:  threedtotwod.cpp input.txt twodtothreed.cpp
	$(CXX) -o threedtotwod threedtotwod.cpp $(LFLAGS) $(LIBS) -std=c++11
	$(CXX) -o twodtothreed twodtothreed.cpp $(LFLAGS) $(LIBS) -std=c++11
show:
	$(CXX) -o show_canvas show_canvas.cpp $(INCPATH) $(LFLAGS) $(LIBS) -std=c++11
.PHONY: clean doxygen

clean: 
	rm -f *.o $(TARGET)
doxygen:
	doxygen doxyfile