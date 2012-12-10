#include "Plot.hpp"

Plot::Plot(float min, float max, int bin): minR(min), maxR(max), binN(bin)
{
	pls = new plstream();
	pls->sdev ("xwin"); //może "tk" ? 
	pls->init();
	pls->spause(0); // blokowanie czekania na np enter
}

void Plot::DrawHist(int liczba, int gen, unsigned short* dane)
{
	PLFLT* data = new PLFLT[liczba];
	for(int i = 0; i<liczba; i++) data[i]=(double)dane[i]; // można zmienić to przepisywanie (=przyspieszyć) jeśli uda Ci się zmienić tablicę short na tablicę doubli (PLFLT to double)
	pls->col0( 3 ); // kolor wykresu
	pls->hist( liczba, data, minR, maxR, binN, PL_HIST_IGNORE_OUTLIERS );
	pls->col0( 4 ); //kolor napisów
	std::stringstream gg;
	gg<<" Generacja " << gen+1;
	pls->lab( "r", "liczba osobnikow", gg.str().c_str() );
}

