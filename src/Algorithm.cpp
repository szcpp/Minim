#include "Algorithm.hpp"

Algorithm::Algorithm(float alpha, float beta, float pc, float pm, unsigned int populationSize) : 
		_alpha(alpha),
		_beta(beta),
		_pc(pc),
		_pm(pm),
		_populationSize(populationSize)
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
