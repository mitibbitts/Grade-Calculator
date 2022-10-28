#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<fstream>
#include<sstream>
#include<string>

#pragma once

class Units {
private:
	double gradeAchieved;
	double gradePossible;
	std::string unitType;
	std::string unitName;
	bool graded;

public:
	Units(double gA, double gP, std::string t, std::string n);
	Units(double gP, std::string t, std::string n);
	Units();
	std::string toString();
	double getGrade();
	double getMaxPoints();
	std::string getName();
	std::string getType();
	void setGrade(double gA);
	bool getGraded();
	void setGraded(bool g);

	friend class UserInterface;
};
