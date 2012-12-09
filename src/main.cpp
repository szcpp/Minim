#include <iostream>
#include <ctime>
#include "ConfigFile.hpp"
#include "Algorithm.hpp"

using namespace std;

int main()
{
	srand48(time(NULL));

	ConfigFile configFile("initialParameters.cfg");

	cout << "Minim v0.01a" << endl << endl;

	cout << "Initial Parameters:" << endl;
	cout << "\tpc:\t\t" << configFile.getValueOfKey<float>("pc") << endl;
	cout << "\tpm:\t\t" << configFile.getValueOfKey<float>("pm") << endl;
	cout << "\talpha:\t\t" <<  configFile.getValueOfKey<float>("alpha") << endl;
	cout << "\tbeta:\t\t" <<  configFile.getValueOfKey<float>("beta") << endl;
	cout << "\tpopulation:\t" <<  configFile.getValueOfKey<unsigned int>("population_size") << endl;

	Algorithm a(
		configFile.getValueOfKey<float>("alpha"),
		configFile.getValueOfKey<float>("beta"),
		configFile.getValueOfKey<float>("pc"),
		configFile.getValueOfKey<float>("pm"),
		configFile.getValueOfKey<unsigned int>("population_size"));

	cout << endl << "\tMem size:\t" << (sizeof a)/1000 << "K" << endl;
	return 0;
}
