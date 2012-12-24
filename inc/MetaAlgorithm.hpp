#ifndef _METAALGORITHM_HPP_
#define _METAALGORITHM_HPP_

//#include <QObject>
#include "Algorithm.hpp"

#define META_POPULATION_SIZE 5000
#define META_CHROMOSOME_LENGTH 10
#define META_MAXIMUM_CHROMOSOME_VALUE 1024 // 2^META_CHROMOSOME_LENGTH

class MetaAlgorithm //: public QObject
{
//     Q_OBJECT 
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
	float _roulette[META_POPULATION_SIZE];
	unsigned short _histogramPc[META_MAXIMUM_CHROMOSOME_VALUE];
	unsigned short _histogramPm[META_MAXIMUM_CHROMOSOME_VALUE];
//signals:
//	void replot();
public:
	MetaAlgorithm(float m_pc, float m_pm, unsigned short int m_populationSize, long meta_maximumIterationCount, unsigned short m_stepCheck, float alpha, float pc, float pm, unsigned short int populationSize, long maximumIterationCount, unsigned short stepCheck);
	~MetaAlgorithm(){};

	static unsigned short ExtractChromosome(const float& value, const float& maximum);
	void Crossover();
	void Launch();
	void Mutate();
	void Reproduce();
	float GetFitness(unsigned short int);
	bool IsConverged();
	unsigned short int GetPopulationSize() const {return _m_populationSize;}
	float GetAlgPm(int index) const {return _algorithms[index]->GetPm();}
	float GetAlgPc(int index) const {return _algorithms[index]->GetPc();}
};

#endif
