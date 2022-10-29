# Grade-Calculator
Member Names: 

## Summary:
This implementation is meant to be simple to use. We identified a few metrics that we felt would be most useful to know during the course of a semester.
We also determined that we wanted to be able to read and write save files because this would allow us to significantly reduce the amount of time a user would
need to spend entering data for a class which they have already previously calculated. 

## Features: 
- Read and Write a Save file. 
- Edit and create new units.
- Get the completion percentage of the class
- View the category grades for the class
- View the weighted category grades and the weighted total grade for the class

## Pseudocode:
class Units:
 - instantiate units with:
    1. max grade possible
    2. grade earned
    3. category of unit
    4. name of unit
    5. whether or not the unis has been grade

class Class:
 -  create a vector of units
 -  add units
 -  modify grades
 -  calculate the completion percentage of the class
 -  calculate the total grade
 -  calculate category grades
 -  sort the units by type
 -  write the vector to a file


class UserInterface:
-  ask whether a file should be read
-  either generate a blank class or one with the contents of the file
-  prompt the user if they would like to operate on the contents of the class
-  determine if the user would like to view various attributes of the class
-  ask the user if they would like to see the current grade
-  ask the user if they would like to write the class to the file to be saved for later
-  
-  end


## Flowchart:


  Inputs: a single file or none
  Outputs: same file, generated file, or none
  Reason: 

How to compile: g++ main.cpp UserInterface.cpp Units.cpp aClass.cpp -o prog; when run the program will ask for an imput file, if no it will ask for a name for the output file. Note: when using an imput file the program will ask the number of catagories (type) included, make sure to put the number of types not number of assignments.
