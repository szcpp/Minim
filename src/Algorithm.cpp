#include "Algorithm.hpp"

Algorithm::Algorithm(float alpha, float pc, float pm, unsigned int populationSize) : 
		_alpha(alpha),
		_pc(pc),
		_pm(pm),
		_populationSize(populationSize)
{
	SetFitness(); //początkowa normalizacja funkcji celu
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
	unsigned short int childSize = 0;
	for(unsigned int iterPop = 0; iterPop<_populationSize; ++iterPop)
	{
		for( unsigned int iterRep = 0;
			iterRep< Fitness(_chromosome[iterPop]) * _populationSize; //obliczanie funkcji celu dla kazdego chromosomu
			++iterRep ) 
		{
			_chromosome[childSize] = _chromosome[iterPop];
			childSize++;
		}
	}
	for(unsigned int iterPop = 0; iterPop<_populationSize; ++iterPop)
		_chromosome[iterPop] = _chromosomeChild[iterPop];
	return;
}

void Algorithm::SetFitness()
{
	float C = 0;
	for(unsigned int iter = 0; iter < pow(2,CHROMOSOME_LENGTH); ++iter)
		C += _alpha*( pow(sin(iter*DR),2)-0.5 ) / pow( 1+0.001*pow(iter*DR,2) ,2);
	_beta = (1-C) / (100*sqrt(2));
}

float Algorithm::Fitness(float r)
{
	return _alpha*( pow(sin(r*DR),2)-0.5 ) / pow( 1+0.001*pow(r*DR,2) ,2) + _beta;
}

void Algorithm::InternalCrossover()
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

void Algorithm::Crossover(const Algorithm &parent, Algorithm &child1, Algorithm &child2) const
{
	;
}
