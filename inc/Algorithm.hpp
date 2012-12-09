#include <cstdlib>
#include <cmath>

#define CHROMOSOME_LENGTH 10
#define DR 100*sqrt(2)/pow(2,CHROMOSOME_LENGTH)

class Algorithm
{
private:
	float _alpha;
	float _beta;
	float _pc;
	float _pm;
	unsigned short _populationSize;
	unsigned short _chromosomeChild[10000];
	unsigned short _chromosome[10000]; // byc moze przerobic na tablice dynamiczna?
public:
	Algorithm(float alpha, float pc, float pm, unsigned int populationSize);
	~Algorithm(){}

	float GetAlpha() const { return _alpha; }
	void SetAlpha(const float &alpha) {	_alpha = alpha; }
	float GetBeta() const {return _beta; }
	void SetBeta(const float &beta) { _beta = beta; }
	float GetPc() const {return _pc; }
	void SetPc(const float &pc) { _pc = pc; }
	float GetPm() const {return _pm; }
	void SetPm(const float &pm) { _pm = pm; }
	float GetPopulationSize() const {return _populationSize; }
	void SetPopulationSize(const float &populationSize) { _populationSize = populationSize; }

	void InternalCrossover();
	void Crossover(const Algorithm&, Algorithm&, Algorithm&) const;
	void Mutate();
	void Reproduce();
	void SetFitness();
	float Fitness(float r);
};
