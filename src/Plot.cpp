#include "Plot.hpp"
using namespace std;

Plot::Plot(float alpha, float pc, float pm, unsigned short population_size, unsigned long maximum_iteration_count, QWidget* parent): _alg( alpha, pc, pm, population_size, maximum_iteration_count), QwtPlot( parent )
{
	//kodowanie polskich znaków
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8")); 
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	
	cout << endl << "\tMem size:\t" << (sizeof _alg)/1000 << "K" << endl;

	//ustawienia osi, tytułów okna wykresu
	setTitle( "Ostatnia generacja" );
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
}

void Plot::DrawHist()
{
	//wypełnianie histogramu danymi z populacji
	unsigned short dd[binN];
	const float step=(maxR-minR)/binN;
	for(int iterBin = 0; iterBin < binN; ++iterBin) dd[iterBin]=0;
	for(int iterPop = 0; iterPop < _alg._populationSize; ++iterPop)
	{
		for(int iterBin = 0; iterBin < binN; ++iterBin)
		{
			if(_alg._chromosome[iterPop] >= step*iterBin+minR && _alg._chromosome[iterPop] < step*(iterBin+1)+minR )
				dd[iterBin]++;
		}
	}
	//przepisywanie na format odczytywalny przez qwt
	QVector<QwtIntervalSample> data;
	for(int iterBin = 0; iterBin < binN; ++iterBin)
		data.append(QwtIntervalSample( dd[iterBin], step*iterBin+minR, step*(iterBin+1)+minR ));
	p->setSamples(data);
	p->attach( this );
	this->replot(); 
}


void Plot::Launch()
{
	LaunchAlg(1);
	return;
}

void Plot::LaunchAlg(int stepDraw)
{
	// TODO stop condition
	std::fstream file("status.out");
	for(unsigned long i = 0; i < _alg._maximumIterationCount; ++i)
	{
		_alg.Reproduce();
		_alg.Crossover();
		_alg.Mutate();
		std::cout << "i:\t" << i+1 << " /\t" << _alg._maximumIterationCount << std::endl;
		if(i % 1 == 0)
		{	
			float mean = 0;
			for(int j = 0; j < _alg._populationSize; ++j)
				mean += _alg._chromosome[j];
			mean /= _alg._populationSize;
			file << mean << "\t";
			for(int j = 0; j < _alg._populationSize; ++j)
				file << _alg._chromosome[j] << "\t";
			file << std::endl;
		}
		if(stepDraw != 0 && i%stepDraw == 0) 
		{
			DrawHist();
		}
	}
	file.close();
}

