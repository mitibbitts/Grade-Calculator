#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
#include<fstream>
#include<sstream>
#include<string>
#include "aClass.h"

#pragma once

class UserInterface {
	private:
		std::string inFName;
		std::string outFName;
		bool fileIn;
		Class thisClass;

	public:
		UserInterface();
		void promptFileIO();
		void addSingleUnit();
		void addMultipleUnits();
		void promptClassEntry();
		void getOut();
		void sort();
		void addGrade();
		void getGradePercentage();
		void getTotalPercentage();
		void promptFileGeneration();
		void readFile();
		void primaryInterface();

};
