#include "Plot.hpp"
using namespace std;

Plot::Plot(MetaAlgorithm& algorithm, unsigned const int stepDraw): _stepDraw(stepDraw), _alg( algorithm ), QwtPlot()
{
	//kodowanie polskich znaków
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8")); 
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	
	cout << endl << "\tMem size:\t" << (sizeof _alg)/1000 << "K" << endl;

	//ustawienia osi, tytułów okna wykresu
	setTitle( " " );
	setAxisTitle( xBottom, "r" );
	axisMaxMajor(xBottom);
	setAxisTitle( yLeft, "Liczba reprezentantów" );
	axisAutoScale(yLeft);

	//czarne tło wykresu
	QPalette canvasPalette( Qt::black ); 
	canvas()->setPalette( canvasPalette ); 
	
	//parametry histogramu
	minR=0.; 
	maxR=pow(2,CHROMOSOME_LENGTH);
	binN=100;
	
	//rysowanie histogramu
	p = new QwtPlotHistogram( "hist" );
	p->setPen( QPen( Qt::green ) );
	p->setBrush( QBrush( Qt::green ) );
	p->attach( this );

	future = new QFuture<void>;
	//watcher = new QFutureWatcher<void>; //czy to się nam kiedyś przyda? ...

	//podłączenie sygnału informującego o zmianie wykresu
	connect(this, SIGNAL(changed()), this, SLOT(changePlot()));
}
void Plot::changePlot()
{
	this->replot();
	stringstream title;
	title<<"Generacja "<<_nr;
	setTitle(QString(title.str().c_str()));
}

void Plot::DrawHist(const Algorithm& algorithm, int nr)
{
	// TODO do przerobienia pod metaalgorytm
	//wypełnianie histogramu danymi z populacji
	unsigned short dd[binN];
	const float step=(maxR-minR)/binN;
	for(int iterBin = 0; iterBin < binN; ++iterBin) dd[iterBin]=0;
	for(int iterPop = 0; iterPop < algorithm._populationSize; ++iterPop)
	{
		for(int iterBin = 0; iterBin < binN; ++iterBin)
		{
			if(algorithm._chromosome[iterPop] >= step*iterBin+minR && algorithm._chromosome[iterPop] < step*(iterBin+1)+minR )
				dd[iterBin]++;
		}
	}
	//przepisywanie na format odczytywalny przez qwt
	QVector<QwtIntervalSample> data;
	for(int iterBin = 0; iterBin < binN; ++iterBin)
		data.append(QwtIntervalSample( dd[iterBin], step*iterBin+minR, step*(iterBin+1)+minR ));
	//ustawianie danych
	p->setSamples(data);
	p->attach( this );

	_nr = nr;
	//emisja sygnału
	emit changed();

}

void Plot::Launch()
{
	//uruchomienie magicznego wątku niezależnego od gui
	*future = QtConcurrent::run(this, &Plot::LaunchAlg);
   //watcher->setFuture(*future); //potrzebne np do pobrania wyników końcowych
	return;
}

void Plot::LaunchAlg()
{
	_alg.Launch();
}

