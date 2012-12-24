#include "Plot.hpp"
using namespace std;

Plot::Plot(MetaAlgorithm& algorithm, unsigned const int stepDraw, float _maxPc,float _maxPm): _stepDraw(stepDraw), _alg( algorithm ), _binN(100), _minPm(0), _maxPm(_maxPm), _minPc(0), _maxPc(_maxPc), _pmPlot(), _pcPlot()
{
	//kodowanie polskich znaków
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8")); 
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	
	cout << endl << "\tMem size:\t" << (sizeof _alg)/1000 << "K" << endl;

	//ustawienia osi, tytułów okna wykresu, czarnego tła
	QPalette canvasPalette( Qt::black ); 
	_pmPlot.setTitle( " " );
	_pmPlot.setAxisTitle( _pmPlot.xBottom, "prawdopodobienstwo mutacji" );
	_pmPlot.axisMaxMajor(_pmPlot.xBottom);
	_pmPlot.setAxisTitle( _pmPlot.yLeft, "liczba reprezentantów" );
	_pmPlot.axisAutoScale(_pmPlot.yLeft);
	_pmPlot.canvas()->setPalette( canvasPalette ); 
	_pcPlot.setTitle( " " );
	_pcPlot.setAxisTitle( _pcPlot.xBottom, "prawdopodobienstwo krzyżowania" );
	_pcPlot.axisMaxMajor(_pcPlot.xBottom);
	_pcPlot.setAxisTitle( _pcPlot.yLeft, "liczba reprezentantów" );
	_pcPlot.axisAutoScale(_pcPlot.yLeft);
	_pcPlot.canvas()->setPalette( canvasPalette ); 
		
	//rysowanie histogramu
	_pmHist = new QwtPlotHistogram( "histogramPm" );
	_pmHist->setPen( QPen( Qt::green ) );
	_pmHist->setBrush( QBrush( Qt::green ) );
	_pmHist->attach( &_pmPlot );
	_pcHist = new QwtPlotHistogram( "histogramPc" );
	_pcHist->setPen( QPen( Qt::green ) );
	_pcHist->setBrush( QBrush( Qt::green ) );
	_pcHist->attach( &_pcPlot );

	_future = new QFuture<void>;

	//podłączenie sygnału informującego o zmianie wykresu
	connect(&_alg, SIGNAL(replot()), this, SLOT(changePlot()));

	QVBoxLayout *Layout = new QVBoxLayout();
	Layout->addWidget(&_pmPlot);	
	Layout->addWidget(&_pcPlot);	
	this->setLayout(Layout);
}
void Plot::changePlot()
{
	DrawHist(_alg.GetGeneration()	);
	_pmPlot.replot();
	_pcPlot.replot();
	stringstream title;
	title<<"Generacja "<<_nr;
	_pmPlot.setTitle(QString(title.str().c_str()));
	_pcPlot.setTitle(QString(title.str().c_str()));
}

void Plot::DrawHist(int nr)
{
	//wypełnianie histogramu danymi z populacji
	unsigned short int ddPm[_binN], 
							ddPc[_binN];
	const float stepPm=(_maxPm-_minPm)/_binN,
					 stepPc=(_maxPc-_minPc)/_binN;
	for(int iterBin = 0; iterBin < _binN; ++iterBin)
	{
		ddPm[iterBin]=0;
		ddPc[iterBin]=0;
	}
	for(int iterPop = 0; iterPop < _alg.GetPopulationSize(); ++iterPop)
	{
		for(int iterBin = 0; iterBin < _binN; ++iterBin)
		{
			if(_alg.GetAlgPm(iterPop) >= stepPm*iterBin+_minPm && _alg.GetAlgPm(iterPop) < stepPm*(iterBin+1)+_minPm )
				ddPm[iterBin]++;
			if(_alg.GetAlgPc(iterPop) >= stepPc*iterBin+_minPc && _alg.GetAlgPc(iterPop) < stepPc*(iterBin+1)+_minPc )
				ddPc[iterBin]++;
		}
	}
	//przepisywanie na format odczytywalny przez qwt
	QVector<QwtIntervalSample> dataPm,
										dataPc;
	for(int iterBin = 0; iterBin < _binN; ++iterBin)
	{
		dataPm.append(QwtIntervalSample( ddPm[iterBin], stepPm*iterBin+_minPm, stepPm*(iterBin+1)+_minPm ));
		dataPc.append(QwtIntervalSample( ddPc[iterBin], stepPc*iterBin+_minPc, stepPc*(iterBin+1)+_minPc ));
	}
	//ustawianie danych
	_pmHist->setSamples(dataPm);
	_pmHist->attach( &_pmPlot );
	_pcHist->setSamples(dataPc);
	_pcHist->attach( &_pcPlot );

	_nr = nr;
}

void Plot::Launch()
{
	//uruchomienie magicznego wątku niezależnego od gui
	*_future = QtConcurrent::run(this, &Plot::LaunchAlg);
	return;
}

void Plot::LaunchAlg()
{
	_alg.Launch();
}

