#include "Plot.hpp"
#include <sstream>

Plot::Plot(float min, float max, int bin): minR(min), maxR(max), binN(bin)
{
	// plplot initialization
	pls = new plstream();
	pls->sdev ("xwin");
	pls->init();
	pls->spause(0);
	//delete pls;
}

void Plot::DrawHist(int liczba, int gen, unsigned short* dane)
{
	PLFLT* data = new PLFLT[liczba];
	for(int i = 0; i<liczba; i++) data[i]=(double)dane[i];
	pls->col0( 3 );
	pls->hist( liczba, data, minR, maxR, binN, PL_HIST_IGNORE_OUTLIERS );
	pls->col0( 4 );
	stringstream gg;
	gg<<" Generacja " << gen+1;
	pls->lab( "r", "liczba osobnikow", gg.str().c_str() );
}
