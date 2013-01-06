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
signals:
	void StopAlgorithm();
public slots:
	void Launch();
	void Preview();
	void ChangePlots();
	void ChangePlotPreview();
	void Stop(){emit StopAlgorithm();}
private:
	MetaAlgorithm& _alg;
	float _minPm,
			_maxPm,
			_minPc,
			_maxPc,
			_minPreview,
			_maxPreview;
	int _binN,
		_nrGenMAG,
		_nrAG,
		_stepDraw;
	bool _previewOpened,
			_programOpened;
	QwtPlotHistogram* _pmHist,
						* _pcHist,
						* _previewHist;
	QwtPlot _pmPlot,
				_pcPlot,
				_previewPlot;
   QFuture<void>* _future;
	void DrawHist(int);
	void DrawHistPreview(int);
	void LaunchAlg();
};
#endif
