#include "aClass.h"
#include "Units.h"
#include<vector>
Class::Class(double gP, std::string t, std::string n, int nUnits){ 
	numUnits = nUnits;
}

Class::Class(std::string outFName){
	outputFile = outFName;
}

Class::Class(std::string inFName, std::string outFName){
	inputFile = inFName;
	outputFile = outFName;
}

Class::Class() {}

void Class::addUngradedUnit(double gP, std::string t, std::string n){
	Units unitAdd = Units(gP, t, n);
	newUnitVector->push_back(unitAdd);
}

void Class::addGradedUnit(double gP, std::string t, std::string n, double gA){
	Units unitAdd = Units(gA, gP, t, n);
	newUnitVector->push_back(unitAdd);
}


void Class::sortByType(){
	std::sort(newUnitVector->begin(), newUnitVector->end(), [](Units arg1, Units arg2){
		return arg1.getType() > arg2.getType();
		});
}

int Class::getClassSize(){
	return newUnitVector->size();
}

void Class::outputClass(){
	for(int i= 0; i<newUnitVector->size(); i++){
		std::cout <<i+1 << ". "<< (*newUnitVector)[i].toString() << std::endl;
	}

}

void Class::establishType(std::string enteredType){
	typeVector->push_back(enteredType);

}
void Class::alterGrade(int unitNum, double grade){
	(*newUnitVector)[unitNum].setGrade(grade);		
	(*newUnitVector)[unitNum].setGraded(true);
}



void Class::sumType(){
	int increment = 0;
		for(int j = 0; j < typeVector->size(); j++){
			std::string currentType = (*typeVector)[j];

			double sumPos = 0;
			double sumAch = 0;
			for(int i =0; i<newUnitVector->size(); i++){
				if((*newUnitVector)[i].getType() == currentType){
				sumPos += (*newUnitVector)[increment].getMaxPoints();
				sumAch += (*newUnitVector)[increment].getGrade();
				}
			}
		std::cout<<currentType << "  " << sumPos << "   " << sumAch << std::endl;
	}
}

double Class::sumGradesOfType(std::string desiredType){
	double typeGradePossible;
	double typeGradeAchieved;
	double gradeOfType;
	for(int i = 0; i < newUnitVector->size(); i++){
		bool graded = (*newUnitVector)[i].getGraded();
		if((*newUnitVector)[i].getType()== desiredType && graded == true){
			typeGradePossible += (*newUnitVector)[i].getMaxPoints();
			typeGradeAchieved += (*newUnitVector)[i].getGrade();
		}
	}
	gradeOfType = typeGradeAchieved/typeGradePossible*100;
	typeGradePossible = 0;
	typeGradeAchieved = 0;
	return gradeOfType;
}

void Class::sumTotalGrades(){
	for(int i = 0; i < typeVector->size(); i++){
		double catPerc = sumGradesOfType((*typeVector)[i]);
		categorizedGrades->push_back(catPerc);
	}
}

double Class::numType(std::string type){
	double numType = 0;
	for(int i = 0; i < newUnitVector->size(); i++){
		std::string currentType = (*newUnitVector)[i].getType();
		if(type == currentType){
			numType++;
		}
	}
	return numType; 
}

std::string Class::getCategory(double index){
	return (*typeVector)[index];
}

double Class::getCatGrade(double index){
	return (*categorizedGrades)[index];
}

double Class::getTypeVecSize(){
	return typeVector->size();
}

void Class::setWeight(double tempWeight){
	weightVec.push_back(tempWeight);
}

void Class::calcWeightedGrade(){
	for(int i = 0; i < categorizedGrades->size(); i++){
		double weightedGrade = (weightVec[i]/100)*((*categorizedGrades)[i]);
		wGradeTotals->push_back(weightedGrade);
	}
}

double Class::getWeightSize(){
	return wGradeTotals->size();
}
double Class::outputWeightedGrade(int index){
	return (*wGradeTotals)[index];
}

double Class::sumWeightedGrades(){
	double totalGrade = std::accumulate(wGradeTotals->begin(), wGradeTotals->end(), 0);
	wGradeTotals->erase(wGradeTotals->begin(), wGradeTotals->end());
	return totalGrade;
}


void Class::writeClassToFile(std::string fileName){
	std::ofstream outputFile(fileName);
	//outputFile.open();
	int weightsLength = weightVec.size();
	std::string gradeType;
	std::string weight;
	std::string weightOut;
	for(int i = 0; i < newUnitVector->size(); i++){
		outputFile << (*newUnitVector)[i].toString();
		outputFile << "\n";
	}
	
	outputFile << "Grade Weights: \n";
	for(int i = 0; i < weightsLength; i++){
		gradeType = (*typeVector)[i];
		weight = std::to_string(weightVec[i]);
		weightOut = gradeType + ": " + weight + "\n"; 
		outputFile << weightOut;
	}
	//outputFile.close();
}


bool Class::readClassFile(std::string fileName){
	bool opened = true;
	int pos;
	std::string line;
	double gA;
	double gP; 
	bool graded;
	std::string word;
	std::istringstream input;
	std::string key = "Graded";
	
	std::ifstream inputFile(fileName);
	if(!inputFile.is_open()){
		opened = false;
		std::cout << "That file could not be found." << std::endl;	
		return opened;
	}	
	
	if(inputFile.is_open()){
		while(std::getline(inputFile, line)){
			
			std::vector<std::string> lineVec;
			
			if(line == "Grade Weights: "){
				break;
			}
			std::istringstream parsedLine(line);
			while(parsedLine >> word){
				if(word == "Grade"){
					break;
				}
				lineVec.push_back(word);
				//std::cout << word << std::endl;
			}
			
			if(lineVec[4] == "Graded"){
				addGradedUnit(std::stoi(lineVec[0]), lineVec[3], lineVec[2], std::stoi(lineVec[1]));
			}

			else if (lineVec[4] == "Ungraded"){
				addUngradedUnit(std::stoi(lineVec[0]), lineVec[3], lineVec[2]);
			}
		
		}
		//return opened;
	}

	
	inputFile.close();
	return opened;
}
