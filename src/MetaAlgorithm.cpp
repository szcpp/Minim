#include "MetaAlgorithm.hpp"

MetaAlgorithm::MetaAlgorithm(float m_pc, float m_pm, unsigned short int m_populationSize, long meta_maximumIterationCount, unsigned short m_stepCheck, float alpha, float pc, float pm, unsigned short int populationSize, long maximumIterationCount, unsigned short stepCheck) :
	_m_pc(m_pc),
	_m_pm(m_pm),
	_alpha(alpha),
	_pc(pc),
	_pm(pm),
	_m_populationSize(m_populationSize),
	_populationSize(populationSize),
	_m_stepCheck(stepCheck),
	_stepCheck(stepCheck),
	_meta_maximumIterationCount(meta_maximumIterationCount),
	_maximumIterationCount(maximumIterationCount)
{
	const unsigned short maximumChromosomeValue = pow(2,META_CHROMOSOME_LENGTH);
	for(unsigned int i = 0; i < _m_populationSize; ++i)
	{
		_algorithms[i] = new Algorithm(alpha, pc*round(maximumChromosomeValue*drand48())/maximumChromosomeValue, pm*round(maximumChromosomeValue*drand48())/maximumChromosomeValue, populationSize, maximumIterationCount, _stepCheck);
	}
};

void MetaAlgorithm::Launch()
{
	for(unsigned int i = 0; i < _m_populationSize; ++i)
	{
		_algorithms[i]->Launch();
		std::cout << "Algorytm " << i+1 << ":" << std::endl << "\tr=\t" << _algorithms[i]->GetResult() << "\t\tkrokow:\t" << _algorithms[i]->GetNumberOfSteps() << std::endl;
		std::cout << "\tpc:\t" << _algorithms[i]->GetPc() << "\tpm:\t" << _algorithms[i]->GetPm() << std::endl << std::endl;

	}
}
