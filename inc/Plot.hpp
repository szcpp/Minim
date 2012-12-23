#ifndef _PLOT_HPP_
#define _PLOT_HPP_

#include <sstream>
#include <QWidget>
#include <qwt_plot_histogram.h>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_series_data.h>
#include <QTextCodec>
#include <QThread>
#include <qt.h>
#include <QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>
#include "Algorithm.hpp"
#include "MetaAlgorithm.hpp"

class Plot : public QwtPlot
{
     Q_OBJECT 
public:
	Plot(MetaAlgorithm& ,unsigned const int );
	~Plot(){}
public slots:
	void Launch();
	void changePlot();
signals:
	void changed();
private:
	int _stepDraw;
	MetaAlgorithm _alg;
	float minR; // minimum osi poziomej
	float maxR; // maksimum osi poziomej
	int binN; // liczba binów
	int _nr;
	void DrawHist(const Algorithm&, int nr);
	QwtPlotHistogram* p;
   QFuture<void> *future;
   QFutureWatcher<void> *watcher;
	void LaunchAlg();
};
#endif
