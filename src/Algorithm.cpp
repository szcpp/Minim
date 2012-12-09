#include "Algorithm.hpp"

Algorithm::Algorithm(float alpha, float pc, float pm, unsigned int populationSize, long maximumIteractionCount) : 
		_alpha(alpha),
		_beta(0),
		_pc(pc),
		_pm(pm),
		_populationSize(populationSize),
		_maximumIterationCount(maximumIteractionCount)
{
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
	
	return;
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

void Algorithm::Launch()
{
	// TODO stop condition
	for(unsigned long i = 0; i < _maximumIterationCount; ++i)
	{
		Reproduce();
		Crossover();
		Mutate();
	}
}
