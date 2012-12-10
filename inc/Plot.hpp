#ifndef _PLOT_HPP
#define _PLOT_HPP

#include "plstream.h"
#include <sstream>

class Plot
{
public:
	Plot(float min, float max, int bin);
	~Plot(){delete pls;}
	void DrawHist(int liczba, int gen, unsigned short* dane); // przyjmuje liczbę punktów do umieszczenia i tablicę wartości
private:
	plstream* pls;
	PLFLT minR; // minimum osi poziomej
	PLFLT maxR; // maksimum osi poziomej
	PLINT binN; // liczba binów
};

#endif
