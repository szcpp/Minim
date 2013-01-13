#ifndef _ALGORITHM_HPP_
#define _ALGORITHM_HPP_

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <QObject>

#define CHROMOSOME_LENGTH 10
#define MAXIMUM_CHROMOSOME_VALUE 1024 // 2^CHROMOSOME_LENGTH
#define POPULATION_SIZE 1000

class Algorithm: public QObject
{
	Q_OBJECT
	friend class Plot;
private:
	float _alpha;
	float _beta;
	float _pc;
	float _pm;
	float _roulette[POPULATION_SIZE];
	unsigned short _chromosomeChild[POPULATION_SIZE];
	const float _dR;
	const unsigned short _populationSize;
	unsigned long _maximumIterationCount;
	unsigned short _chromosome[POPULATION_SIZE];
	const unsigned short _stepCheck;
	unsigned short _histogram[MAXIMUM_CHROMOSOME_VALUE];
	float _result;
	short _numberOfSteps;
	float _exponentialFactor;
signals:
	void replotAG();
public:
	Algorithm(float alpha, float pc, float pm, unsigned int populationSize, long maximumIterationCount, unsigned short stepCheck, float exponentialFactor);
	~Algorithm(){}

	float GetAlpha() const { return _alpha; }
	void SetAlpha(const float &alpha) {	_alpha = alpha; }
	float GetBeta() const {return _beta; }
	void SetBeta(const float &beta) { _beta = beta; }
	float GetPc() const {return _pc; }
	void SetPc(const float &pc) { _pc = pc; }
	float GetPm() const {return _pm; }
	void SetPm(const float &pm) { _pm = pm; }
	unsigned short GetPopulationSize() const {return _populationSize; }
	const float& GetdR() const { return _dR; }
	// void SetPopulationSize(const float &populationSize) { _populationSize = populationSize; }
	unsigned long GetMaximumIterationCount() const { return _maximumIterationCount; }
	void SetMaximumIterationCount(unsigned long const &iterationCount) { _maximumIterationCount = iterationCount; }
	unsigned short GetStepCheck() const {return _stepCheck;}
	float GetResult() const {return _result;}
	unsigned short GetNumberOfSteps() const { return _numberOfSteps; }
	float GetExponentialFactor() const { return _exponentialFactor; }
	void SetExponentialFactor(float const &exponentialFactor){ _exponentialFactor = exponentialFactor;}

	void Crossover();
	void Mutate();
	void Reproduce();
	void NormalizeFitness();
	float GetFitness(const unsigned short& r) const;
	unsigned short int GetChromosome(int index) const {return _chromosome[index];}
	bool IsConverged();
	void Launch(const int stepDraw = 0);
};

#endif
