#include "MetaAlgorithm.hpp"

MetaAlgorithm::MetaAlgorithm(float m_pc, float m_pm, unsigned short int m_populationSize, long meta_maximumIterationCount, unsigned short m_stepCheck, float alpha, float pc, float pm, unsigned short int populationSize, long maximumIterationCount, unsigned short stepCheck) :
	_m_pc(m_pc),
	_m_pm(m_pm),
	_alpha(alpha),
	_pc(pc),
	_pm(pm),
	_m_populationSize(m_populationSize),
	_populationSize(populationSize),
	_m_stepCheck(m_stepCheck),
	_stepCheck(stepCheck),
	_meta_maximumIterationCount(meta_maximumIterationCount),
	_maximumIterationCount(maximumIterationCount)
{
	for(unsigned int i = 0; i < _m_populationSize; ++i)
	{
		_algorithms[i] = new Algorithm(alpha, pc*round(META_MAXIMUM_CHROMOSOME_VALUE*drand48())/META_MAXIMUM_CHROMOSOME_VALUE, pm*round(META_MAXIMUM_CHROMOSOME_VALUE*drand48())/META_MAXIMUM_CHROMOSOME_VALUE, populationSize, maximumIterationCount, _stepCheck);
	}
	for(int index = 0; index < _m_populationSize; ++index )
		connect(_algorithms[index], SIGNAL(replotAG()), this, SLOT(replotSigAG()));
};
void MetaAlgorithm::replotSigAG()
{
	emit replotAG();
}
void MetaAlgorithm::Launch()
{
	std::fstream pm_file("status_pm.out");
	std::fstream pc_file("status_pc.out");
	for(unsigned int j = 0; j < _meta_maximumIterationCount; ++j)
	{
		if(_programOpened == false) break;
		for(unsigned int i = 0; i < _m_populationSize; ++i)
		{
			if(_programOpened == false) break;
			_generationMAG = j;
			_generationAG = i;
			_algorithms[i]->Launch();
			std::cout << "Iteracja " << j << " Algorytm " << i+1 << ":" << std::endl << "\tr=\t" << _algorithms[i]->GetResult() << "\t\tkrokow:\t" << _algorithms[i]->GetNumberOfSteps() << std::endl;
			std::cout << "\tpc:\t" << _algorithms[i]->GetPc() << "\tpm:\t" << _algorithms[i]->GetPm() << std::endl << std::endl;
		}
		emit replotMAG();
		Reproduce();
		Crossover();
		Mutate();
		for(int index = 0; index < _m_populationSize; ++index )
			connect(_algorithms[index], SIGNAL(replotAG()), this, SLOT(replotSigAG()));
		if(j % _m_stepCheck == 0)
			if(IsConverged())
				break;
		#if 1
		for(unsigned int k = 0; k < _m_populationSize; ++k)
		{
			if(k % 1 == 0)
			{	
				float meanPm = 0, meanPc = 0;
				for(int l = 0; l < _m_populationSize; ++l)
				{
					meanPm += ExtractChromosome(_algorithms[l]->GetPm(),_pm);
					meanPc += ExtractChromosome(_algorithms[l]->GetPc(),_pc);
				}
				meanPm /= _m_populationSize;
				meanPc /= _m_populationSize;
				pm_file << meanPm << "\t";
				pc_file << meanPc << "\t";
				for(int l = 0; l < _m_populationSize; ++l)
				{
					pm_file << ExtractChromosome(_algorithms[l]->GetPm(),_pm) << "\t";
					pc_file << ExtractChromosome(_algorithms[l]->GetPc(),_pc) << "\t";
				}
				pm_file << std::endl;
				pc_file << std::endl;
			}
		}
		#endif
	}
	pm_file.close();
	pc_file.close();
}

/*
 * Extracts binary form of chromosome (eg. 0b1010010100) from float value (eg. 0.012f).
 */
unsigned short MetaAlgorithm::ExtractChromosome(const float& value, const float& maximum)
{
	return round(value/maximum*META_MAXIMUM_CHROMOSOME_VALUE);
}

void MetaAlgorithm::Crossover()
{
	unsigned short
		position,
		mask,
		chromosomeI,
		chromosomeJ,
		tmp = 0,
		i,
		j,
		k;
	for(k = 0; k < _m_populationSize/2; ++k)
	{
		if(drand48() < _m_pc)
		{
			i = 2*k;
			j = 2*k+1;
			// pc part
			position = floor(drand48()*(META_CHROMOSOME_LENGTH-1))+1; // position can be only from 1-9 range
			mask = pow(2, position+1) - 1;
			chromosomeI = ExtractChromosome(_algorithms[i]->GetPc(),_pc);
			chromosomeJ = ExtractChromosome(_algorithms[j]->GetPc(),_pc);
			tmp = chromosomeI & mask;
			chromosomeI = (chromosomeI & ~mask) | (chromosomeJ & mask);
			chromosomeJ = (chromosomeJ & ~mask) | tmp;
			_algorithms[i]->SetPc(_pc*chromosomeI/META_MAXIMUM_CHROMOSOME_VALUE);
			_algorithms[j]->SetPc(_pc*chromosomeJ/META_MAXIMUM_CHROMOSOME_VALUE);

			// pm part
			position = floor(drand48()*(META_CHROMOSOME_LENGTH-1))+1; // position can be only from 1-9 range
			mask = pow(2, position+1) - 1;
			chromosomeI = ExtractChromosome(_algorithms[i]->GetPm(),_pm);
			chromosomeJ = ExtractChromosome(_algorithms[j]->GetPm(),_pm);
			tmp = chromosomeI & mask;
			chromosomeI = (chromosomeI & ~mask) | (chromosomeJ & mask);
			chromosomeJ = (chromosomeJ & ~mask) | tmp;
			_algorithms[i]->SetPm(_pm*chromosomeI/META_MAXIMUM_CHROMOSOME_VALUE);
			_algorithms[j]->SetPm(_pm*chromosomeJ/META_MAXIMUM_CHROMOSOME_VALUE);
		}
	}
}

void MetaAlgorithm::Mutate()
{
	unsigned short chromosome;
	for(unsigned int i = 0; i<_m_populationSize; ++i)
		for(unsigned short j = 0; j<META_CHROMOSOME_LENGTH; ++j)
		{
			if(drand48()<_m_pm)
			{
				chromosome = ExtractChromosome(_algorithms[i]->GetPc(),_pc) ^ (1<<j);
				_algorithms[i]->SetPc(_pc*chromosome/META_MAXIMUM_CHROMOSOME_VALUE);
			}			
			if(drand48()<_m_pm)
			{
				chromosome = ExtractChromosome(_algorithms[i]->GetPm(),_pm) ^ (1<<j);
				_algorithms[i]->SetPm(_pm*chromosome/META_MAXIMUM_CHROMOSOME_VALUE);
			}
		}
}

void MetaAlgorithm::Reproduce()
{
	float norm = 0;
	unsigned short i = 0;
	unsigned short j = 0;

	Algorithm *_algorithmsChild[META_POPULATION_SIZE];

	for(i = 0; i < _m_populationSize; ++i)
	{
		norm += _roulette[i] = GetFitness(i);
	}

	for(i = 0; i < _m_populationSize; ++i)
	{
		do
		{
			j = round(drand48()*_m_populationSize);
			// std::cout << norm << " @ " << _roulette[j] << std::endl;
		}
		while(drand48()*norm >= _roulette[j]);
		_algorithmsChild[i] = new Algorithm(
				_algorithms[j]->GetAlpha(),
				_algorithms[j]->GetPc(),
				_algorithms[j]->GetPm(),
				_algorithms[j]->GetPopulationSize(),
				_algorithms[j]->GetMaximumIterationCount(),
				_algorithms[j]->GetStepCheck()
			);
	}

	for(i = 0; i < _m_populationSize; ++i)
	{
		_algorithms[i] = _algorithmsChild[i];
	}
}


float MetaAlgorithm::GetFitness(unsigned short int index)
{
	if(_algorithms[index]->GetNumberOfSteps() == 0)
		return 1000;
	else
		return 1./_algorithms[index]->GetNumberOfSteps();
}

bool MetaAlgorithm::IsConverged()
{
	bool
		IsConvergedPc = false,
		IsConvergedPm = false;
	for(unsigned int i = 0; i < META_MAXIMUM_CHROMOSOME_VALUE; ++i)
	{
		_histogramPc[i] = 0;
		_histogramPm[i] = 0;
	}

	for(unsigned int i = 0; i < _m_populationSize; ++i)
	{
		++_histogramPc[ExtractChromosome(_algorithms[i]->GetPc(),_pc)];
		++_histogramPm[ExtractChromosome(_algorithms[i]->GetPm(),_pm)];
	}
	for(unsigned int i = 0; i < META_MAXIMUM_CHROMOSOME_VALUE; ++i)
	{
		//std::cout << _m_populationSize << ">> " << i << " :: " << _histogramPm[i] << " @@@ " << _histogramPc[i] << std::endl;
		if(_histogramPm[i] >= 0.6*_m_populationSize)
			IsConvergedPm = true;
		if(_histogramPc[i] >= 0.6*_m_populationSize)
			IsConvergedPc = true;
		if(IsConvergedPm && IsConvergedPc)
			return true;
	}	
	return false;
}
