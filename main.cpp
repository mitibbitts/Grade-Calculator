#include <iostream>
#include "aClass.h"
#include "Units.h"
#include "UserInterface.h"
#include "aClass.cpp"
#include "Units.cpp"
#include "UserInterface.cpp"

int main() {
	UserInterface interfaceInstance = UserInterface();
	interfaceInstance.primaryInterface();
	return 0;
}
