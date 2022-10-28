#include "Units.h"
#include "aClass.h"

Units::Units(double gA, double gP, std::string t, std::string n){
	gradeAchieved = gA;
	gradePossible = gP;
	unitType = t;
	unitName = n;
	graded = true;
}

Units::Units(double gP, std::string t, std::string n){
	gradeAchieved = 0;
	gradePossible = gP;
	unitType = t;
	unitName = n;
	graded = false;
}

Units::Units(){}

std::string Units::toString(){
	 
	std::string gP = std::to_string(gradePossible);
	std::string gA = std::to_string(gradeAchieved);
	std::string grade = "Graded";
	if(graded == false){
		grade = "Ungraded";
	}
	return gP + " " + gA + " " + unitName + " " + unitType + " " + grade;
}

double Units::getGrade(){

	return gradeAchieved;
}

double Units::getMaxPoints(){
	return gradePossible;
}

std::string Units::getName(){
	return unitName;
}

std::string Units::getType(){
	return unitType;                                                           
}

void Units::setGrade(double gA){
	gradeAchieved = gA;
}

bool Units::getGraded(){
	return graded;
}
void Units::setGraded(bool g){
	graded = true;
}
