#include <cstdlib>
#include <cmath>

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
	Algorithm(float alpha, float beta, float pc, float pm, unsigned int populationSize);
	~Algorithm(){}
	void Mutate();
	void Reproduce();
};
