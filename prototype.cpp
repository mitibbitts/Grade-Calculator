#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>

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

        void setGrade(int gA){
            gradeAchieved = gA;
        }
};

class Class : public Units{
    private:
        std::vector<std::string> *typeVector = new std::vector<std::string>;
        std::vector<Units> *newUnitVector = new std::vector<Units>;
        int numUnits;

    public:
        Class(double gP, std::string t, std::string n, int nUnits) : Units(gP, t, n){
            numUnits = nUnits;
        }

        Class() {}

        void addUngradedUnit(double gP, std::string t, std::string n){
            Units unitAdd = Units(gP, t, n);
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
                std::cout << (*newUnitVector)[i].toString() << std::endl;
            }
        
		}

		void establishType(std::string enteredType){
			typeVector->push_back(enteredType);
		
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

};

class UserInterface{
	private:
		std::string inFName;
		std::string outFName;
		friend class Class;
	public:
		UserInterface() {};	
		Class thisClass = Class();
		void doShit(){
			thisClass.establishType("Homework");
			thisClass.establishType("Test");
			thisClass.establishType("Project");
			thisClass.addUngradedUnit(10, "Homework", "Hw1");
			thisClass.addUngradedUnit(10, "Test", "Test1");
			thisClass.addUngradedUnit(10, "Project", "Proj1");
			thisClass.addUngradedUnit(10, "Homework", "Hw1");
			thisClass.addUngradedUnit(10, "Test", "Test1");
			thisClass.addUngradedUnit(10, "Project", "Proj2");
			thisClass.sortByType();
			thisClass.sumType();
			thisClass.outputClass();
	}
};

int main(){ 
	UserInterface interfaceInstance = UserInterface();
	interfaceInstance.doShit();	
	/**   	
    Class thisClass = Class();
	thisClass.establishType("Homework");
	thisClass.establishType("Test");
	thisClass.establishType("Project");
    thisClass.addUngradedUnit(10, "Homework", "Hw1");
    thisClass.addUngradedUnit(10, "Test", "Test1");
    thisClass.addUngradedUnit(10, "Project", "Proj1");
    thisClass.addUngradedUnit(10, "Homework", "Hw1");
    thisClass.addUngradedUnit(10, "Test", "Test1");
    thisClass.addUngradedUnit(10, "Project", "Proj2");
    thisClass.sortByType();
    thisClass.sumType();
	thisClass.outputClass();
*/
    //thisClass.outputUnit(); 
    //std::vector<Units> *newUnitVector = new std::vector<Units>;
    //Units newUnit = Units(10, "Hello", "Hi");
    //newUnitVector->push_back(newUnit);
    //std::cout << (*newUnitVector)[0].toString() << std::endl;

    return 0;
}
