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
};