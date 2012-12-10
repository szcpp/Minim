#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include "Plot.hpp"

#define CHROMOSOME_LENGTH 10
#define POPULATION_SIZE 10000

class Algorithm
{
private:
	float _alpha;
	float _beta;
	float _pc;
	float _pm;
	const unsigned short _populationSize;
	float _roulette[POPULATION_SIZE];
	unsigned short _chromosomeChild[POPULATION_SIZE];
	unsigned short _chromosome[POPULATION_SIZE]; // byc moze przerobic na tablice dynamiczna?
	unsigned long _maximumIterationCount;
	const float _dR;
public:
	Algorithm(float alpha, float pc, float pm, unsigned int populationSize, long maximumIterationCount);
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
	// void SetPopulationSize(const float &populationSize) { _populationSize = populationSize; }
	unsigned long GetMaximumIterationCount() const { return _maximumIterationCount; }
	void SetMaximumIterationCount(unsigned long const &iterationCount) { _maximumIterationCount = iterationCount; }

	void Crossover();
	void Mutate();
	void Reproduce();
	void Launch(int stepDraw);
	void NormalizeFitness();
	float GetFitness(unsigned short r);
};
