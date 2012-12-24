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
#include <QVBoxLayout>
#include "Algorithm.hpp"
#include "MetaAlgorithm.hpp"

class Plot : public QWidget
{
     Q_OBJECT 
public:
	Plot(MetaAlgorithm& ,unsigned const int, float, float);
	~Plot(){}
public slots:
	void Launch();
	void changePlot();
signals:
	void changed();
private:
	MetaAlgorithm _alg;
	float _minPm,
			_maxPm,
			_minPc,
			_maxPc;
	int _binN,
		_nr,
		_stepDraw;
	QwtPlotHistogram* _pmHist,
						* _pcHist;
	QwtPlot _pmPlot,
				_pcPlot;
   QFuture<void>* _future;
	void DrawHist(const MetaAlgorithm&, int);
	void LaunchAlg();
};
#endif
