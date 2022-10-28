#include <iostream>
#include "aClass.h"
#include "Units.h"
#include "UserInterface.h"
#include "UserInterface.cpp"
#include "aClass.cpp"
#include "Units.cpp"

int main(){ 
	UserInterface interfaceInstance = UserInterface();
	interfaceInstance.primaryInterface();
	return 0;
}
