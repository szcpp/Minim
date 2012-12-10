#ifndef _PLOT_HPP
#define _PLOT_HPP

#include "plstream.h"
#include <unistd.h>

using namespace std;

class Plot
{
public:
	Plot(float min, float max, int bin);
	~Plot(){delete pls;}
	void DrawHist(int liczba, int gen, unsigned short*  dane);
private:
	plstream* pls;
	PLFLT minR;
	PLFLT maxR;
	PLINT binN;
};

#endif
