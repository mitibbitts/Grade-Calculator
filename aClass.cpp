#include "aClass.h"
#include "Units.h"
#include<vector>


//*****************************Constructors******************************* 
//
//
//
//We want some basic ways to construct class objects. There are more here than are
//used but they could be useful for extended applications of this class
Class::Class(double gP, std::string t, std::string n, int nUnits){ 
	numUnits = nUnits;
}
//This constructor is used when no file is specified
Class::Class(std::string outFName){
	outFile = outFName;
}
//This constructor is used when an input file is specified
Class::Class(std::string inFName, std::string outFName){
	inFile = inFName;
	outFile = outFName;
}

//Default constructor
Class::Class() {}

// *************************Functions Which Interract with the Units class***************************** 
//
//
//
// It should be noticed that these functions both generate new Unit objects as well as push them
// into a vector of objects. This is done through an inheritance relationship.
// One of the primary facets of this structure is to enforce that a Class
// is nothing more than a vector of Units.
void Class::addUngradedUnit(double gP, std::string t, std::string n){
	//instantiate a Units object with the gradePossible, the type, and the name
	Units unitAdd = Units(gP, t, n);
	newUnitVector->push_back(unitAdd);
}

void Class::addGradedUnit(double gP, std::string t, std::string n, double gA){
	//instantiate a Units object with the gradeAchieved, the gradePossible, the type, and the name
	Units unitAdd = Units(gA, gP, t, n);
	newUnitVector->push_back(unitAdd);
}

// This function allows the user to change the grade of a unit.
void Class::alterGrade(int unitNum, double grade){
	(*newUnitVector)[unitNum].setGrade(grade);		
	(*newUnitVector)[unitNum].setGraded(true);
}


//*******************Functions Which Operate Internally in the Class********************
//
//
//
// This function returns the number of Units in the Class
int Class::getClassSize(){
	return newUnitVector->size();
} 

// This function will sort the category names of units int the class. It implements the
// sort function from the built-in algorithm class and a lambda expression which compares the
// names of the categories
void Class::sortByType(){
	std::sort(newUnitVector->begin(), newUnitVector->end(), [](Units arg1, Units arg2){
		return arg1.getType() > arg2.getType();
		});
}

// This function will output the entire contents of the class to the console
void Class::outputClass(){
	for(int i= 0; i<newUnitVector->size(); i++){
		std::cout <<i+1 << ". "<< (*newUnitVector)[i].toString() << std::endl;
	}

}

// This function sums the grade values after they have been weighted
void Class::sumTotalGrades(){
	for(int i = 0; i < typeVector->size(); i++){
		double catPerc = sumGradesOfType((*typeVector)[i]);
		categorizedGrades->push_back(catPerc);
	}
}
// This function is used to calculate the weighted grade for a given category
void Class::calcWeightedGrade(){
	for(int i = 0; i < categorizedGrades->size(); i++){
		double weightedGrade = (weightVec[i]/100)*((*categorizedGrades)[i]);
		wGradeTotals->push_back(weightedGrade);
	}
}
// This function is used to sum the grades in the weighted grade vector so that
// the entire weighted grade for the class can be viewed
double Class::sumWeightedGrades(){
	double totalGrade = std::accumulate(wGradeTotals->begin(), wGradeTotals->end(), 0);
	wGradeTotals->erase(wGradeTotals->begin(), wGradeTotals->end());
	return totalGrade;
}

// This function sums the graded units, divides them by the total number of units entered
// and pushes the completion percentage to the console 
void Class::viewGradeProgress(){
	double gradedUnits = 0;
	double percentCompletion;
	double size = newUnitVector->size();
	for(int i = 0; i < size; i++){
		if((*newUnitVector)[i].getGraded() == true){
			gradedUnits++;
		}
	}
	percentCompletion = (gradedUnits/size)*100;
	std::cout << "You have completed " << percentCompletion << "% of coursework." << std::endl;
}



//*******************Functions Which Take Parameters from the User Interface***************
//
//
//
// This function adds category types which are passed to fill a vector 
void Class::establishType(std::string enteredType){
	typeVector->push_back(enteredType);
}


// This function sums the grades in a given category by iterating through the entire vector
// and determining which objects have the same category type
double Class::sumGradesOfType(std::string desiredType){
	double typeGradePossible = 0;
	double typeGradeAchieved = 0;
	double gradeOfType = 0;
	for(int i = 0; i < newUnitVector->size(); i++){
		bool graded = (*newUnitVector)[i].getGraded();
		if((*newUnitVector)[i].getType()== desiredType && graded == true){
			typeGradePossible += (*newUnitVector)[i].getMaxPoints();
			typeGradeAchieved += (*newUnitVector)[i].getGrade();
		}
	}
	if(typeGradePossible > 0){
		gradeOfType = typeGradeAchieved/typeGradePossible*100;
	}
	else{
		std::cout << "Sorry, that category has no grades." << std::endl;
		gradeOfType = 0;
	}
	//typeGradePossible = 0;
	//typeGradeAchieved = 0;
	return gradeOfType;
}


// This function describes the number of objects in the vector with a passed in category
// type
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



//************************Functions to Get and Set Various Values ************************
//
//
//
// Return a specific category
std::string Class::getCategory(double index){
	return (*typeVector)[index];
}

// Returns a the grade in a specific category
double Class::getCatGrade(double index){
	return (*categorizedGrades)[index];
}

// Returns the number of categories in the vector of Units objects
double Class::getTypeVecSize(){
	return typeVector->size();
}

// Takes a passed in weight and pushes it into a vector which has the weights of the class
void Class::setWeight(double tempWeight){
	weightVec.push_back(tempWeight);
}

// returns the number of weighted grades
double Class::getWeightSize(){
	return wGradeTotals->size();
}

// returns the weighted grade for a passed in type
double Class::outputWeightedGrade(int index){
	return (*wGradeTotals)[index];
}


//***********************************File I/O **************************************
//
//
//
// This class will write a file to the specified filename with which the Class object
// was constructed
void Class::writeClassToFile(){
	std::ofstream outputFile(outFile);
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
}

// Because the input file name needs to be tested for existence, this
// function both reads the input file and determines if it can be opened. 
// It returns a boolean which describes the ability to be opened
bool Class::readClassFile(std::string inFName){
	bool opened = true;
	int pos;
	std::string line;
	double gA;
	double gP; 
	bool graded;
	std::string word;
	std::istringstream input;
	std::string key = "Graded";
	
	std::ifstream inputFile(inFName);
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
			}
			if(lineVec[4] == "Graded"){
				addGradedUnit(std::stoi(lineVec[0]), lineVec[3], lineVec[2], std::stoi(lineVec[1]));
			}
			else if (lineVec[4] == "Ungraded"){
				addUngradedUnit(std::stoi(lineVec[0]), lineVec[3], lineVec[2]);
			}
		}
	}
	inputFile.close();
	return opened;
}
