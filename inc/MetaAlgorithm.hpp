#ifndef _METAALGORITHM_HPP_
#define _METAALGORITHM_HPP_

#include "Algorithm.hpp"

#define META_POPULATION_SIZE 5000
#define META_CHROMOSOME_LENGTH 10

class MetaAlgorithm
{
private:
	float 
		_m_pc,
		_m_pm,
		_alpha,
		_pc,
		_pm;
	unsigned short int		
		_m_populationSize,
		_populationSize,
		_m_stepCheck,
		_stepCheck;
	long
		_meta_maximumIterationCount,
		_maximumIterationCount;

	Algorithm *_algorithms[META_POPULATION_SIZE];
public:
	MetaAlgorithm(float m_pc, float m_pm, unsigned short int m_populationSize, long meta_maximumIterationCount, unsigned short m_stepCheck, float alpha, float pc, float pm, unsigned short int populationSize, long maximumIterationCount, unsigned short stepCheck);
	~MetaAlgorithm(){};

	void Launch();
	unsigned short int GetPopulationSize() const {return _m_populationSize;}
	float GetAlgPm(int index) const {return _algorithms[index]->GetPm();}
	float GetAlgPc(int index) const {return _algorithms[index]->GetPc();}
};

#endif
