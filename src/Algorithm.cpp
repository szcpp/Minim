#include "Algorithm.hpp"

Algorithm::Algorithm(float alpha, float pc, float pm, unsigned int populationSize, long maximumIteractionCount, unsigned short stepCheck) : 
		_alpha(alpha),
		_beta(0),
		_pc(pc),
		_pm(pm),
		_dR(100*sqrt(2)/pow(2,CHROMOSOME_LENGTH)),
		_populationSize(populationSize),
		_maximumIterationCount(maximumIteractionCount),
		_stepCheck(stepCheck),
		_result(0),
		_numberOfSteps(0)
{
	NormalizeFitness(); //początkowa normalizacja funkcji celu
	for(unsigned int iter = 0; iter < _populationSize; ++iter)
		_chromosome[iter] = drand48()*pow(2,CHROMOSOME_LENGTH);
}

void Algorithm::Mutate()
{
	for(unsigned int iterPop = 0; iterPop<_populationSize; ++iterPop)
	{
		for(unsigned int iterChrom = 0; iterChrom<CHROMOSOME_LENGTH; ++iterChrom)
		{
			if(drand48()<_pm) _chromosome[iterPop] ^= (1<<iterChrom);
		}
	}
	return;
}

void Algorithm::Reproduce()
{
	float norm = 0;
	unsigned short i = 0;
	unsigned short j = 0;
	for(i = 0; i < _populationSize; ++i)
		norm += _roulette[i] = GetFitness(_chromosome[i]);

	for(i = 0; i < _populationSize; ++i)
	{
		_histogram[i] = 0;
		do
		{
			j = round(drand48()*_populationSize);
		}
		while(drand48()*norm >= _roulette[j]);
		_chromosomeChild[i] = _chromosome[j];
	}

	for(i = 0; i < _populationSize; ++i)
		_chromosome[i] = _chromosomeChild[i];

	return;
}

void Algorithm::NormalizeFitness()
{
	float C = 0;
	for(unsigned int iter = 0; iter < pow(2,CHROMOSOME_LENGTH); ++iter)
		C += _alpha*( pow(sin(iter*_dR),2)-0.5 ) / pow( 1+0.001*pow(iter*_dR,2) ,2);
	_beta = (1-C) / (100*sqrt(2));
}

float Algorithm::GetFitness(const unsigned short &r) const
{
	return _alpha*( pow(sin(1.*r*_dR),2)-0.5 ) / pow( 1.+0.001*pow(1.*r*_dR,2),2) + _beta;
}

void Algorithm::Crossover()
{
	unsigned short position;
	unsigned short mask;
	unsigned short tmp = 0;
	for(unsigned short i = 0; i < _populationSize; ++i)
		for(unsigned short j = 0; j < _populationSize; ++j)
			if(drand48() < _pc)
			{
				position = floor(drand48()*(CHROMOSOME_LENGTH-1))+1; // position can be only from 1-9 range
				mask = pow(2, position+1) - 1;
				tmp = _chromosome[i] & mask;
				_chromosome[i] = (_chromosome[i] & ~mask) | (_chromosome[j] & mask);
				_chromosome[j] = (_chromosome[j] & ~mask) | tmp;
			}
}

void Algorithm::Launch(const int stepDraw)
{
	_numberOfSteps = 0;
	std::fstream file("status.out");
	for(unsigned long i = 0; i < _maximumIterationCount; ++i)
	{
		Reproduce();
		Crossover();
		Mutate();
		// if 50% of population is "somewhere", finish
		if(i % _stepCheck == 0)
			if(IsConverged())
			{
				_numberOfSteps = i;
				break;
			}
	#if 1
		if((i+1) % 50 == 0)
			std::cout << "i:\t" << i+1 << " /\t" << _maximumIterationCount << std::endl;
		if(i % 1 == 0)
		{	
			float mean = 0;
			for(int j = 0; j < _populationSize; ++j)
				mean += _chromosome[j];
			mean /= _populationSize;
			file << mean << "\t";
			for(int j = 0; j < _populationSize; ++j)
				file << _chromosome[j] << "\t";
			file << std::endl;
		}
	#endif
		// TODO: zmontować tutaj callback
		// if(stepDraw != 0 && i%_stepDraw == 0) DrawHist(i+1);
	}
	file.close();
	if(_numberOfSteps == 0)
		_numberOfSteps = _maximumIterationCount;
}

bool Algorithm::IsConverged()
{
	for(unsigned int i = 0; i < _populationSize; ++i)
		++_histogram[_chromosome[i]];
	for(unsigned int i = 0; i < _populationSize; ++i)
		if(_histogram[i] >= 0.6*_populationSize)
		{
			_result = 1.*i*_dR;
			return true;
		}
	return false;
}