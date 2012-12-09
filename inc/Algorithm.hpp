#include <cstdlib>

#define CHROMOSOME_LENGTH 10

class Algorithm
{
private:
	float _alpha;
	float _beta;
	float _pc;
	float _pm;
	unsigned int _populationSize;
	unsigned short int _chromosome[10000]; // byc moze przerobic na tablice dynamiczna?
public:
	Algorithm(float alpha, float beta, float pc, float pm, unsigned int populationSize) : 
		_alpha(alpha),
		_beta(beta),
		_pc(pc),
		_pm(pm),
		_populationSize(populationSize)
	{}
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

	void Crossover(const Algorithm&, Algorithm&, Algorithm&) const;
};