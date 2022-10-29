#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<fstream>
#include<sstream>
#include<string>
#include"Units.h"

#pragma once


class Class : public Units {

private:
	std::vector<std::string> *typeVector = new std::vector<std::string>;
	std::vector<Units> *newUnitVector = new std::vector<Units>;
	int numUnits;
	std::string outFile;
	std::string inFile;
	std::vector<double> *categorizedGrades = new std::vector<double>;
	std::vector<double> *wGradeTotals = new std::vector<double>;
	std::vector<double> weightVec;

public:

	Class(double gP, std::string t, std::string n, int nUnits); 
	Class(std::string outFName);
	Class(std::string inFName, std::string outFName);
	Class();
	void addUngradedUnit(double gP, std::string t, std::string n);
	void addGradedUnit(double gP, std::string t, std::string n, double gA);
	void sortByType();
	int getClassSize();
	void outputClass();
	void establishType(std::string enteredType);
	void alterGrade(int unitNum, double grade);
	void sumType();
	double sumGradesOfType(std::string desiredType);
	void sumTotalGrades();
	double numType(std::string type);
	std::string getCategory(double index);
	double getCatGrade(double index);
	double getTypeVecSize();
	void setWeight(double tempWeight);
	void calcWeightedGrade();
	double getWeightSize();
	void viewGradeProgress();
	double outputWeightedGrade(int index);
	double sumWeightedGrades();
	void writeClassToFile();
	bool readClassFile(std::string inFName);
};
