#include "Plot.hpp"
using namespace std;

Plot::Plot(MetaAlgorithm& algorithm, unsigned const int stepDraw, float _maxPc,float _maxPm): _stepDraw(stepDraw), _alg( algorithm ), _binN(1024), _minPm(0), _maxPm(_maxPm), _minPc(0), _maxPc(_maxPc),  _minPreview(0), _maxPreview(pow(2,CHROMOSOME_LENGTH)), _pmPlot(), _pcPlot(), _previewPlot()
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
	_previewPlot.setTitle( " " );
	_previewPlot.setAxisTitle( _pmPlot.xBottom, "r" );
	_previewPlot.axisMaxMajor(_pmPlot.xBottom);
	_previewPlot.setAxisTitle( _pmPlot.yLeft, "liczba reprezentantów" );
	_previewPlot.axisAutoScale(_pmPlot.yLeft);
	_previewPlot.canvas()->setPalette( canvasPalette );
		
	//rysowanie histogramu
	_pmHist = new QwtPlotHistogram( "histogramPm" );
	_pmHist->setPen( QPen( Qt::green ) );
	_pmHist->setBrush( QBrush( Qt::green ) );
	_pmHist->attach( &_pmPlot );
	_pcHist = new QwtPlotHistogram( "histogramPc" );
	_pcHist->setPen( QPen( Qt::green ) );
	_pcHist->setBrush( QBrush( Qt::green ) );
	_pcHist->attach( &_pcPlot );
	_previewHist = new QwtPlotHistogram( "histogramAlg" );
	_previewHist->setPen( QPen( Qt::green ) );
	_previewHist->setBrush( QBrush( Qt::green ) );
	_previewHist->attach( &_previewPlot );

	_future = new QFuture<void>;

	//podłączenie sygnału informującego o zmianie wykresu
	connect(&_alg, SIGNAL(replotMAG()), this, SLOT(ChangePlots()));
	connect(&_alg, SIGNAL(replotAG()), this, SLOT(ChangePlotPreview()));
	connect(this, SIGNAL(StopAlgorithm()), &_alg, SLOT(StopAlgorithm()));

	QVBoxLayout *Layout = new QVBoxLayout();
	Layout->addWidget(&_pmPlot);	
	Layout->addWidget(&_pcPlot);	
	this->setLayout(Layout);

	ChangePlots();
	ChangePlotPreview();
}
void Plot::Preview()
{
	if(_previewOpened)
	{
		_previewPlot.hide();
		_previewOpened = false;
	}
	else
	{
		_previewPlot.show();
		_previewPlot.setGeometry(650,100,500,400);
		_previewOpened = true;
	}
}
void Plot::ChangePlots()
{
	DrawHist(_alg.GetGenerationMAG()	);
	_pmPlot.replot();
	_pcPlot.replot();
	stringstream title;
	title<<"Generacja "<<_nrGenMAG+1;
	_pmPlot.setTitle(QString(title.str().c_str()));
	_pcPlot.setTitle(QString(title.str().c_str()));
}
void Plot::ChangePlotPreview()
{
	DrawHistPreview(_alg.GetGenerationAG());
	_previewPlot.replot();
	stringstream title;
	title<<"Algorytm "<<_nrAG;
	_previewPlot.setTitle(QString(title.str().c_str()));
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

	_nrGenMAG = nr;
}

void Plot::DrawHistPreview(int nr)
{
	//wypełnianie histogramu danymi z populacji
	unsigned short int ddPreview[_binN];
	const float stepPreview=(_maxPreview-_minPreview)/_binN;
	for(int iterBin = 0; iterBin < _binN; ++iterBin)
		ddPreview[iterBin]=0;
	for(int iterPop = 0; iterPop < _alg.GetAGPopulationSize(); ++iterPop)
	{
		for(int iterBin = 0; iterBin < _binN; ++iterBin)
		{
			if(_alg.GetAlgChromosome(nr, iterPop) >= stepPreview*iterBin+_minPreview && _alg.GetAlgChromosome(nr, iterPop) < stepPreview*(iterBin+1)+_minPreview )
				ddPreview[iterBin]++;
		}
	}
	//przepisywanie na format odczytywalny przez qwt
	QVector<QwtIntervalSample> dataPreview;
	for(int iterBin = 0; iterBin < _binN; ++iterBin)
	{
		dataPreview.append(QwtIntervalSample( ddPreview[iterBin], stepPreview*iterBin+_minPreview, stepPreview*(iterBin+1)+_minPreview ));
	}
	//ustawianie danych
	_previewHist->setSamples(dataPreview);
	_previewHist->attach( &_previewPlot );

	_nrAG = nr;
}

void Plot::Launch()
{
	if(_programOpened == false)
	{
		*_future = QtConcurrent::run(this, &Plot::LaunchAlg);	//uruchomienie magicznego wątku niezależnego od gui
		_alg.SetActiveLaunch();
		_programOpened = true;
	}
	else emit StopAlgorithm();
	return;
}

void Plot::LaunchAlg()
{
	_alg.Launch();
}

