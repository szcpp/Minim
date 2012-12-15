#ifndef _PLOT_HPP
#define _PLOT_HPP

//#include <sstream>
#include <QWidget>
#include <qwt_plot_histogram.h>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_series_data.h>
#include <QTextCodec>
#include "Algorithm.hpp"

class Plot : public QwtPlot
{
     Q_OBJECT 
public:
	Plot(float alpha, float pc, float pm, unsigned short population_size, unsigned long maximum_iteration_count, QWidget* parent = NULL);
	~Plot(){}
public slots:
	void Launch();
private:
	float minR; // minimum osi poziomej
	float maxR; // maksimum osi poziomej
	int binN; // liczba binów
	Algorithm _alg;
	void LaunchAlg(int stepDraw);
	void DrawHist();
	QwtPlotHistogram* p;
};

#endif
