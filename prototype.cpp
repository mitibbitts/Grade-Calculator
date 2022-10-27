#include<iostream>
#include<vector>
//#include"string.h"
#include<algorithm>
#include<numeric>
#include<fstream>
#include<sstream>
#include<string>

class Units {
    private:
        double gradeAchieved;
        double gradePossible;
        std::string unitType;
        std::string unitName;
        bool graded;

    public:
        Units(double gA, double gP, std::string t, std::string n){
            gradeAchieved = gA;
			gradePossible = gP;
            unitType = t;
            unitName = n;
            graded = true;
        }

        Units(double gP, std::string t, std::string n){
            gradeAchieved = 0;
            gradePossible = gP;
            unitType = t;
            unitName = n;
            graded = false;
        }

        Units(){}

        std::string toString(){
            std::string gP = std::to_string(gradePossible);
            std::string gA = std::to_string(gradeAchieved);
            std::string grade = "Graded";
            if(graded == false){
                grade = "Ungraded";
            }
            return gP + " " + gA + " " + unitName + " " + unitType + " " + grade;
        }

        double getGrade(){
            return gradeAchieved;
        }

        double getMaxPoints(){
            return gradePossible;
        }

        std::string getName(){
            return unitName;
        }

        std::string getType(){
            return unitType;                                                           
        }

        void setGrade(double gA){
            gradeAchieved = gA;
        }

		bool getGraded(){
			return graded;
		}
		void setGraded(bool g){
			graded = true;
		}
};

class Class : public Units{
    private:
        std::vector<std::string> *typeVector = new std::vector<std::string>;
        std::vector<Units> *newUnitVector = new std::vector<Units>;
        int numUnits;
		std::string outputFile;
		std::string inputFile;
	    std::vector<double> *categorizedGrades = new std::vector<double>;
		std::vector<double> *wGradeTotals = new std::vector<double>;
		std::vector<double> weightVec;

    public:
        Class(double gP, std::string t, std::string n, int nUnits) : Units(gP, t, n){
            numUnits = nUnits;
        }

		Class(std::string outFName){
			outputFile = outFName;
		}
		
		Class(std::string inFName, std::string outFName){
			inputFile = inFName;
			outputFile = outFName;
		}

        Class() {}

        void addUngradedUnit(double gP, std::string t, std::string n){
            Units unitAdd = Units(gP, t, n);
            newUnitVector->push_back(unitAdd);
        }

		void addGradedUnit(double gP, std::string t, std::string n, double gA){
			Units unitAdd = Units(gA, gP, t, n);
			newUnitVector->push_back(unitAdd);
		}


        void sortByType(){
			std::sort(newUnitVector->begin(), newUnitVector->end(), [](Units arg1, Units arg2){
				return arg1.getType() > arg2.getType();
				});
        }

        int getClassSize(){
            return newUnitVector->size();
        }

        void outputClass(){
            for(int i= 0; i<newUnitVector->size(); i++){
                std::cout <<i+1 << ". "<< (*newUnitVector)[i].toString() << std::endl;
            }
        
		}

		void establishType(std::string enteredType){
			typeVector->push_back(enteredType);
		
		}
		void alterGrade(int unitNum, double grade){
			(*newUnitVector)[unitNum].setGrade(grade);		
			(*newUnitVector)[unitNum].setGraded(true);
		}



		void sumType(){
			int incType;	
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

		double sumGradesOfType(std::string desiredType){
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
			return gradeOfType;
		}

		void sumTotalGrades(){
			for(int i = 0; i < typeVector->size(); i++){
				double catPerc = sumGradesOfType((*typeVector)[i]);
				categorizedGrades->push_back(catPerc);
			}
		}

		double numType(std::string type){
			double numType = 0;
			for(int i = 0; i < newUnitVector->size(); i++){
				std::string currentType = (*newUnitVector)[i].getType();
				if(type == currentType){
					numType++;
				}
			}
			return numType; 
		}

		std::string getCategory(double index){
			return (*typeVector)[index];
		}
		
		double getCatGrade(double index){
			return (*categorizedGrades)[index];
		}

		double getTypeVecSize(){
			return typeVector->size();
		}

		void setWeight(double tempWeight){
			weightVec.push_back(tempWeight);
		}

		void calcWeightedGrade(){
			for(int i = 0; i < categorizedGrades->size(); i++){
				double weightedGrade = (weightVec[i]/100)*((*categorizedGrades)[i]);
				wGradeTotals->push_back(weightedGrade);
			}
		}

		double getWeightSize(){
			return wGradeTotals->size();
		}
		double outputWeightedGrade(int index){
			return (*wGradeTotals)[index];
		}

		double sumWeightedGrades(){
			double totalGrade = std::accumulate(wGradeTotals->begin(), wGradeTotals->end(), 0);
			return totalGrade;
		}


		void writeClassToFile(std::string fileName){
			std::ofstream outputFile(fileName);
			int weightsLength = weightVec.size();
			std::string gradeType;
			std::string weight;
			std::string weightOut;
			for(int i = 0; i < newUnitVector->size(); i++){
				outputFile << (*newUnitVector)[i].toString();
				outputFile << "\n";
			}

			outputFile << "\nGrade Weights: \n";
			for(int i = 0; i < weightsLength; i++){
				gradeType = (*typeVector)[i];
				weight = std::to_string(weightVec[i]);
				weightOut = gradeType + ": " + weight + "\n"; 
				outputFile << weightOut;
			}
		}


		void readClassFile(std::string fileName){
			std::vector<std::string> lineVec;
			std::string line;
			double gA;
			double gP; 
			bool graded;
			std::istringstream input;
			std::string key = "Graded";

			std::ifstream inputFile(fileName);
			inputFile.open("test1.txt");
				
			
			if(inputFile.is_open()){
				std::cout << "hello";
				//std::cout << "Hello";
				while(getline(inputFile, line)){
					std::cout << "oop" << std::endl;
					inputFile >> line;
				}
			}


			inputFile.close();
			//for(int i = 0; i < lineVec.size(); i++){
			//	std::cout << lineVec[i] << std::endl;
			//}
		}
		
};

class UserInterface{
	private:
		std::string inFName;
		std::string outFName;
		bool fileIn; 

		Class thisClass;
		friend class Class;
	public:
		UserInterface() {};	
		
		
		void promptFileIO(){
			std::string yn;	
			std::cout << "Would you like to input a file to be read? [Y/n]" << std::endl;
			std::cin >> yn;
		    if(yn == "N"){
				fileIn = false;
			}	
			else{
				fileIn = true;
			}
			if(fileIn == true){
				std::cout<<"Please enter the name of the file: ";
				std::cin >> inFName;
				outFName = inFName;
				thisClass = Class(inFName, outFName);
			}
			else{
				std::cout<< "Please enter an output file name: ";
				std::cin >> outFName;
			
			thisClass = Class(outFName);
			}		
		}

		void addSingleUnit(){
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

		void addMultipleUnits(){
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

		void promptClassEntry(){
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
		void getOut(){
			thisClass.outputClass();
		}

		void sort(){
			thisClass.sortByType();
		}
		void addGrade(){
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
	
		void getGradePercentage(){
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

		void getTotalPercentage(){
		
			double tempWeight;
			double runningTotal = 0;
			for(int i = 0; i<thisClass.getTypeVecSize(); i++){
				
				std::cout << "Enter the weight for the total in the " << thisClass.getCategory(i) << " category: ";
				std::cin >> tempWeight;
				thisClass.setWeight(tempWeight);
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
		

		void promptFileGeneration(){
			std::string selection;
			std::cout << "Would you like to generate a save file now? [Y/N] ";
			std::cin >> selection;
			if(selection == "Y" || selection == "y"){
				thisClass.writeClassToFile(outFName);
			}
		}

		void testFile(){
			thisClass.readClassFile("test1.txt");	
		}
};

int main(){ 
	UserInterface interfaceInstance = UserInterface();
	//interfaceInstance.testFile();
	
	interfaceInstance.promptFileIO();	
	interfaceInstance.promptClassEntry();
	interfaceInstance.sort();
	interfaceInstance.addGrade();
	interfaceInstance.getGradePercentage();
	interfaceInstance.getTotalPercentage();
	interfaceInstance.promptFileGeneration();
    interfaceInstance.getOut();
	
	return 0;
}
