CXX=g++
LFLAGS        = -m64
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -pthread -I/usr/include/gtk-2.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/libpng12 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libpng12 -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/freetype2

LIBS          = -L/usr/lib/x86_64-linux-gnu/ -lm -lQtGui -larmadillo -lgtk-x11-2.0 -lgdk-x11-2.0 -lpangocairo-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0 -lfontconfig -lfreetype

DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB
OBJECTS       = main.o
TARGET        = draw

all:  threedtotwod.cpp input.txt twodtothreed.cpp
	$(CXX) -o threedtotwod threedtotwod.cpp $(LFLAGS) $(LIBS) -std=c++11
	$(CXX) -o twodtothreed twodtothreed.cpp $(LFLAGS) $(LIBS) -std=c++11
show:
	$(CXX) -o show_canvas show_canvas.cpp $(INCPATH) $(LFLAGS) $(LIBS) -std=c++11
gui:
	$(CXX) -o first first.cpp $(INCPATH) $(LFLAGS) $(LIBS) -std=c++11
.PHONY: clean doxygen

clean: 
	rm -f *.o $(TARGET)
doxygen:
	doxygen doxyfile
