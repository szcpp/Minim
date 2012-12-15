#ifndef _PLOT_HPP
#define _PLOT_HPP

#include <sstream>
#include <QWidget>
#include <qwt_plot_histogram.h>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_series_data.h>
#include <QTextCodec>
#include <QThread>
#include <QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>
#include "Algorithm.hpp"

class Plot : public QwtPlot
{
     Q_OBJECT 
public:
	Plot(float alpha, float pc, float pm, unsigned short population_size, unsigned long maximum_iteration_count, int stepDraw);
	~Plot(){}
public slots:
	void Launch();
	void changePlot();
signals:
	void changed();
private:
	float minR; // minimum osi poziomej
	float maxR; // maksimum osi poziomej
	int binN; // liczba binów
	int _stepDraw;
	int _nr;
	Algorithm _alg;
	void DrawHist(int nr);
	QwtPlotHistogram* p;
   QFuture<void> *future;
   QFutureWatcher<void> *watcher;
	void LaunchAlg();
};
#endif
