#include <iostream>
#include <ctime>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include "MetaAlgorithm.hpp"
#include "ConfigFile.hpp"
#include "Plot.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	srand48(time(NULL));

	//wczytywanie konfiguracji
	ConfigFile configFile("initialParameters.cfg");
	cout << "Minim v0.01a" << endl << endl;
	cout << "Initial Parameters:" << endl;
	cout << "\tpc:\t\t" << configFile.getValueOfKey<float>("pc") << endl;
	cout << "\tpm:\t\t" << configFile.getValueOfKey<float>("pm") << endl;
	cout << "\talpha:\t\t" <<  configFile.getValueOfKey<float>("alpha") << endl;
	cout << "\tpopulation:\t" <<  configFile.getValueOfKey<unsigned short>("population_size") << endl << endl;
	cout << "Metaalgorithm configuration:" << endl;
	cout << "\tpc:\t\t" << configFile.getValueOfKey<float>("meta_pc") << endl;
	cout << "\tpm:\t\t" << configFile.getValueOfKey<float>("meta_pm") << endl;
	cout << "\tpopulation:\t" <<  configFile.getValueOfKey<unsigned short>("meta_population_size") << endl;
	
	MetaAlgorithm metaAlgorithm(
		configFile.getValueOfKey<float>("meta_pc"),
		configFile.getValueOfKey<float>("meta_pm"),
		configFile.getValueOfKey<unsigned short>("meta_population_size"),
		configFile.getValueOfKey<unsigned long>("meta_maximum_iteration_count"),
		configFile.getValueOfKey<unsigned short>("meta_step_check"),
		configFile.getValueOfKey<float>("alpha"),
		configFile.getValueOfKey<float>("pc"),
		configFile.getValueOfKey<float>("pm"),
		configFile.getValueOfKey<unsigned short>("population_size"),
		configFile.getValueOfKey<unsigned long>("maximum_iteration_count"),
		configFile.getValueOfKey<unsigned short>("step_check"));

	cout << "rysuje" << endl;
	//start okienka
	QApplication app(argc, argv);
	QWidget all;
	Plot plot(metaAlgorithm, configFile.getValueOfKey<int>("step_draw"));

	//Przyciski
	QPushButton* quit = new QPushButton("Quit", &all);
	quit->setFont(QFont("Times", 18, QFont::Bold));
	QObject::connect(quit, SIGNAL(clicked()), &app, SLOT(quit()));
	QPushButton* draw = new QPushButton("Minimalizuj", &all);
	draw->setFont(QFont("Times", 18, QFont::Bold));
	QObject::connect(draw, SIGNAL(clicked()), &plot, SLOT(Launch()));

	//layouty
	QVBoxLayout *mainLayout = new QVBoxLayout();
	QHBoxLayout *buttonsLayout = new QHBoxLayout();
	QWidget* buttons = new QWidget();
	buttonsLayout->addWidget(quit);
	buttonsLayout->addWidget(draw);
	buttons->setLayout(buttonsLayout);
	mainLayout->addWidget(buttons);
	mainLayout->addWidget(&plot);
	all.setLayout(mainLayout);
	all.show();
	all.resize(600,600);


	//QLabel *label = new QLabel(QApplication::translate("windowlayout", "Name:"));
	//QLineEdit *lineEdit = new QLineEdit();
	return app.exec();
}
