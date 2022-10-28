#include"UserInterface.h"
#include"Units.h"
#include"aClass.h"

UserInterface::UserInterface() {};	
		
	
void UserInterface::promptFileIO(){
	std::string yn;	
	std::cout << "Would you like to input a file to be read? [Y/n]" << std::endl;
	std::cin >> yn;
	if(yn == "N" || yn == "n"){
		fileIn = false;
	}	
	else{
		fileIn = true;
	}
	if(fileIn == true){
		std::cout<<"Please enter the name of the file: ";
		std::cin >> inFName;
		bool found = thisClass.readClassFile(inFName);
		if(!found){
			std::cout << "Would you like to try a different file name? [y/n]" << std::endl;
			std::cin >> yn;
			if(yn == "Y" || yn == "y"){
				promptFileIO();
			}
		}
		if(found){
			outFName = inFName;
			thisClass = Class(inFName, outFName);
		}
	}
	else{
		std::cout<< "Please enter an output file name: ";
		std::cin >> outFName;
	
	thisClass = Class(outFName);
	}		
}

void UserInterface::addSingleUnit(){
	std::string type;
	double gradePossible;
	double gradeAchieved;
	std::string name;
	std::string graded;
	std::string isUniqueType;


	std::cout << "Has this unit been graded? [Y/n]  ";
	std::cin >> graded;
	std::cout << "Enter the name of the Unit: ";
	std::cin >> name;
	std::cout << "Enter the type of the Unit: ";
	std::cin >> type;

	std::cout << "Is this the first time units of this type have been added to the Class? [Y/N] ";
	std::cin >> isUniqueType;
	if(isUniqueType == "Y" || isUniqueType == "y"){
		thisClass.establishType(type);
	}	
	std::cout << "Enter the maximum grade possible for the Unit: ";
	std::cin >> gradePossible;
	if(graded == "N"|| graded == "n"){
		thisClass.addUngradedUnit(gradePossible, type, name);		
	}
	if(graded == "Y" || graded == "y"){
		std::cout << "Enter the grade received on the unit: ";
		std::cin >> gradeAchieved;
		thisClass.addGradedUnit(gradePossible, type, name, gradeAchieved);
	}	
}

void UserInterface::addMultipleUnits(){
	int numUnits;
	std::string unitType;
	int unitTypeGrade;
	int numExistingUnits;
	std::string isUniqueType;
	std::cout<< "What type of unit would you like to add? ";
	std::cin >> unitType;	
	std::cout<<"How many " << unitType << " units would you like to add?  ";
	std::cin >> numUnits;
	std::cout << "Enter the maximum grade possible for a given " << unitType<<": ";	
	std::cin >> unitTypeGrade;
	numExistingUnits = thisClass.numType(unitType);
	for(int i = 0; i < numUnits; i++){
		std::string name = unitType + std::to_string(i+1+numExistingUnits);	
		thisClass.addUngradedUnit(unitTypeGrade, unitType, name);
		
	}
	std::cout << "Is this the first time units of this type have been added to the Class? [Y/N] ";
	std::cin >> isUniqueType;
	if(isUniqueType == "Y" || isUniqueType == "y"){
		thisClass.establishType(unitType);
	}	
}

void UserInterface::promptClassEntry(){
	int unitSel;
	std::cout << "Press 1 to enter multiple units" << std::endl; 
	std::cout << "Press 2 to enter a single unit" << std::endl;
	std::cout << "Press 3 to stop adding units" << std::endl;
	std::cin >> unitSel;
	while(unitSel != 3){
			if(unitSel == 1){
				addMultipleUnits();
			}	
			else if(unitSel == 2){
				addSingleUnit();
			}
			std::cout << "Make another selection or press 3 to stop adding units: ";
			std::cin >> unitSel;
	}
}
void UserInterface::getOut(){
	thisClass.outputClass();
}

void UserInterface::sort(){
	thisClass.sortByType();
}
void UserInterface::addGrade(){
	double gradeAchieved;
	int unitSelection;
	std::string addMore;
	

	std::cout << "Enter the number next to the unit for which you would like to add a grade:"<< std::endl;
	thisClass.outputClass();
	std::cin >> unitSelection;
	std::cout << "Enter the grade received: ";
	std::cin >> gradeAchieved;

	
	unitSelection--;
	thisClass.alterGrade(unitSelection, gradeAchieved);
	

	std::cout << "Would you like to add another grade? [Y/N]";
	std::cin >> addMore;
	if(addMore == "Y"|| addMore == "y"){
		this->addGrade();
	}
	else{}
}

void UserInterface::getGradePercentage(){
	std::string type;
	double gradePerc;
	std::string repeat;
	std::cout << "Enter the category for which you would like the grade Percentage: ";
	std::cin >> type;
	gradePerc = thisClass.sumGradesOfType(type);
	std::cout << "Your grade for this category is " << gradePerc<< "%" << std::endl;
	
	std::cout << "Would you like to view the grade for another category? [Y/N]";
	std::cin >> repeat;
	if(repeat == "Y"||repeat == "y"){
		this->getGradePercentage();
	}
	else{}
}

void UserInterface::getTotalPercentage(){

	double tempWeight;
	if(thisClass.getWeightSize() == 0){
		for(int i = 0; i<thisClass.getTypeVecSize(); i++){
			std::cout << "Enter the weight for the total in the " << thisClass.getCategory(i) << " category: ";
			std::cin >> tempWeight;
			thisClass.setWeight(tempWeight);
		}
	}
	thisClass.sumTotalGrades();
	thisClass.calcWeightedGrade();
	double weightedGrade = thisClass.sumWeightedGrades();
	
	for(int i = 0; i< thisClass.getTypeVecSize(); i++){
		double wCatGrade = thisClass.outputWeightedGrade(i);
		std::cout << "Your weighted grade for the " << thisClass.getCategory(i) << " category is: " <<wCatGrade<<"%"<< std::endl;
	}

	std::cout << "Your Weighted Grade For the Class is " << weightedGrade << "%" << std::endl;
}


void UserInterface::promptFileGeneration(){
	std::string selection;
	std::cout << "Would you like to generate a save file now? [Y/N] ";
	std::cin >> selection;
	if(selection == "Y" || selection == "y"){
		thisClass.writeClassToFile(outFName);
	}
}

void UserInterface::readFile(){
	int numCat;
	std::string tempCat;
	promptFileIO();
	if(fileIn == true){
		std::cout << "You have elected to read the file " << inFName << std::endl;
		thisClass.readClassFile(inFName);
		getOut();
		std::cout << "Since you read a file, you'll need to manually specify categories and their weights. How many categories do you have?";
		std::cin >> numCat;
		for(int i = 0; i < numCat; i++){
			std::cout << "Enter Category " << i << ": ";
			std::cin >> tempCat;
			thisClass.establishType(tempCat);
		}
	}

}

void UserInterface::primaryInterface(){
	int menuSel;
	std::cout<< "Hello! Welcome to the Grade Calculator!" << std::endl;
	readFile();
	
	std::cout << "What would you like to do next?" << std::endl;
	std::string menu = "1. Add Units \n2. Edit Grades\n3. Get Category Percentages\n4. Get Total Weighted Grade\n -1. Exit the calculator";
	std::cout << menu << std::endl;
	std::cin >> menuSel;
	while(menuSel != -1){
		if(menuSel == 1){
			promptClassEntry();
			sort();
		}
		else if(menuSel == 2){
			addGrade();
		}
		else if(menuSel == 3){
			getGradePercentage();
		}
		else if(menuSel == 4){
			getTotalPercentage();
		}
		else if(menuSel == -1){
			std::cout << "Thanks for using the grade Calculator!";
		}
		else{
		std::cout << "Sorry, that's not a valid selection.";	
		}

		if(menuSel!= -1){
			std::cout << menu;
			std::cin >> menuSel;
		}
	}
	promptFileGeneration();
}
