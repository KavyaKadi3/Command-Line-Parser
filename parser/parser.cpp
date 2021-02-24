//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>
#include <valarray>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

int x_location;
int y_location;

bool locationCheck(int x_location, int y_location) {
    if (x_location<0 | y_location<0) {
        return true;
    }
}

int x_size;
int y_size;

bool sizeCheck(int x_size, int y_size) {
    if (x_size<0 | y_size<0) {
        return true;
    }
}

int inputAngle;

bool inputAngleCheck(int inputAngle) {
    if (!(inputAngle > 0 && inputAngle < 361)) {
        return true;
    }
}

bool existingName(string name) {
    int h;
    for (h=0; h<shapeCount; h++) {
        if (shapesArray[h] != nullptr) {
            if (name==shapesArray[h]->getName()) {
                         return true;
                     }
        }
    }
                        return false;
}

int main() {

    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input
    
    
    shapesArray = nullptr;
            
    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        string name; 
        string inputType;
        int x_location;
        int y_location;
        int x_size;
        int y_size;
        int inputAngle;
        
        string names[] = {"maxShapes", "create", "move", "rotate", "draw", "delete", "ellipse", "circle", "rectangle", "triangle"};
                
         if (command == "maxShapes") {
             if (shapesArray!=nullptr) {
             int g; 
                 for (g=0; g<max_shapes; g++) {
                     delete shapesArray[g];
                        shapesArray[g]=nullptr; 
                 }
                 delete[]shapesArray;
                 shapeCount=0;
            }
            int f;
            lineStream >> max_shapes;
            cout << "New database: max shapes is " << max_shapes << endl;
            shapesArray = new Shape* [max_shapes];
            for (f=0; f<max_shapes; f++) {
                shapesArray[f]=nullptr;
            }
         }
        
         else if (command == "create") {
             lineStream >> name; 
             lineStream >> inputType; 
             lineStream >> x_location; 
             lineStream >> y_location;
             lineStream >> x_size; 
             lineStream >> y_size;

             if (lineStream.fail() && (lineStream.eof())) {
                 cout << "Error: too few arguments" << endl;
             }
             else if (lineStream.fail()) {                 
                cout << "Error: invalid argument" << endl;	   
              }
             else if (name == names[0] || name == names[1] || name == names[2] || name == names[3] || name == names[4] || name == names[5] || name == names[6] || name== names[7] || name == names[8] || name == names[9] || name == "all") {
                 cout << "Error: invalid shape name\n";
             }
             else if ((existingName(name))==true) {
                 cout << "Error: shape name exists" << endl;
             }
             else if (inputType != shapeTypesList[0] && inputType != shapeTypesList[1] && inputType != shapeTypesList[2] && inputType != shapeTypesList[3]) {
                 cout << "Error: invalid shape type" << endl;
             }
             else if ((locationCheck(x_location, y_location)==true)) {
                 cout << "Error: invalid value" << endl;
             }
             else if (sizeCheck(x_size, y_size)==true) {
                 cout << "Error: invalid value" << endl;
             }
             else if (lineStream.peek() != EOF) {
                 cout << "Error: too many arguments" << endl;
             }       
             else if (shapeCount > max_shapes) {
                 cout << "Error: shape array is full" << endl;
             }
             else {
                 shapesArray[shapeCount] = new Shape (name, inputType, x_location, y_location, x_size, y_size);
                 shapeCount++;
                 cout << "Created " << name << ": " << inputType << " " << x_location << " " << y_location << " " << x_size << " " << y_size << endl;
             }
         }
        
         else if (command == "move") { 
             bool flag = false;
             lineStream >> name;
             flag = lineStream.fail();
             lineStream >> x_location;
             lineStream >> y_location;
             
            if (lineStream.fail() && (lineStream.eof())) {
                if (!flag) {
                    if ((existingName(name))==false) {
                 cout << "Error: shape " << name << " not found" << endl;
                    }
                }
                    else {
                        cout << "Error: too few arguments" << endl;
                    }
            }
             else if (lineStream.fail()) {                 
                cout << "Error: invalid argument" << endl;	   
              }
             else if (name == names[0] || name == names[1] || name == names[2] || name == names[3] || name == names[4] || name == names[5] || name == names[6] || name== names[7] || name == names[8] || name == names[9] || name == "all") {
                 cout << "Error: invalid shape name" << endl;
             }
             else if ((existingName(name))==false) {
                 cout << "Error: shape " << name << " not found" << endl;
             }
             else if ((locationCheck(x_location, y_location)==true)) {
                 cout << "Error: invalid value" << endl;
             }
             else if (sizeCheck(x_size, y_size)==true) {
                 cout << "Error: invalid value" << endl;
             }
             else if (lineStream.peek() != EOF) {
                 cout << "Error: too many arguments" << endl;
             }
             else if (shapeCount > max_shapes) {
                 cout << "Error: shape array is full" << endl;
             }                        
             else {
                 int j;
                 for (j=0; j<shapeCount; j++) {
                     if(shapesArray[j] != nullptr) {
                     if (shapesArray[j]->getName()==name) {
                         shapesArray[j]->setXlocation(x_location);
                         shapesArray[j]->setYlocation(y_location);
                     }
                     }
                 }
                 cout << "Moved " << name << "to " << x_location<< " " << y_location << endl;
             }
         }
        
         else if (command == "rotate") {
             lineStream >> name;
             lineStream >> inputAngle;
             
              if (lineStream.fail() && (lineStream.eof())) {
                 cout << "Error: too few arguments" << endl;
             }
             else if (lineStream.fail()) {                 
                cout << "Error: invalid argument" << endl;	   
              }
             else if (name == names[0] || name == names[1] || name == names[2] || name == names[3] || name == names[4] || name == names[5] || name == names[6] || name== names[7] || name == names[8] || name == names[9] || name == "all") {
                 cout << "Error: invalid shape name" << endl;
             }
             else if ((existingName(name))==false) {
                 cout << "Error: shape " << name << " not found" << endl;
             }
             else if (inputAngleCheck(inputAngle)==true) { 
	       cout << "Error: invalid value" << endl;
             }
             else if (lineStream.peek() != EOF) {
                 cout << "Error: too many arguments" << endl;
             }
             else if (shapeCount > max_shapes) {
                 cout << "Error: shape array is full" << endl;
             }                        
             else {
                 int k;
                 for (k=0; k<shapeCount; k++) {
                     if (shapesArray[k] != nullptr) {
                     if (name==shapesArray[k]->getName()) {
                         shapesArray[k]->setRotate(inputAngle);
                         cout << "Rotated " << name << " by " << inputAngle << " degrees" << endl;
                     }
                     }
                 }
             }
         }
        
         else if (command == "draw") {
             char check = lineStream.peek();
             lineStream >> name;
             if (check==EOF) {
                 cout << "Error: too few arguments" << endl;
             }
             else if (lineStream.fail()) {
                 cout << "Error: invalid argument" << endl;
             }
             else if ((existingName(name))==false && name != "all") {
                 cout << "Error: shape " << name << " not found" << endl;
             }
             else if (lineStream.peek() != EOF) {
                 cout << "Error: too many arguments" << endl;
             }               
             else {
                if (name =="all") {
                int m;
                    cout << "Drew all shapes" << endl; 
                    for (m=0; m < shapeCount; m++) {
                         if (shapesArray[m] != nullptr) {
                        shapesArray[m]->draw();
                    }
                    }
                }
                else {
                    int p;
                    for (p=0; p < shapeCount; p++) {
                        if (shapesArray[p] != nullptr) {
                        if (shapesArray[p]->getName()==name) {
                            shapesArray[p]->setXlocation(x_location);
                            shapesArray[p]->setYlocation(y_location);
                            cout << "Drew ";
                            shapesArray[p]->draw();
                            break;
                        }
                        }
                    }
                }
            }
         }
          
         else if (command == "delete") {
             lineStream >> name;
             
             if (lineStream.fail() && (lineStream.eof())) {
                 cout << "Error: too few arguments" << endl;
             }
             else if (lineStream.fail()) {                 
                cout << "Error: invalid argument" << endl;	   
              }
             else if ((existingName(name))==false && name != "all") {
                 cout << "Error: shape " << name << " not found" << endl;
             }
             else if (lineStream.peek() != EOF) {
                 cout << "Error: too many arguments" << endl;
             }                    
             else {
                if (name =="all") {
                    int y;
                    for (y=0; y<shapeCount; y++) {
                        delete shapesArray[y];
                        shapesArray[y]=nullptr; 
                    }
                    shapeCount=0;
                    cout << "Deleted: all shapes" << endl; 
                }
                else {
                    int z;
                    for (z=0; z<shapeCount; z++) {
                        if (shapesArray[z] != nullptr) { 
                        if(shapesArray[z]->getName()==name) {
                            delete shapesArray[z];
                            shapesArray[z]=nullptr;
                            cout << "Deleted shape " << name << endl;
                        }
                        }
                    }
                }
            }
         }
                              
         else if (command != "maxShapes" || command != "create" || command != "move" || command != "rotate" || command != "draw" || command != "delete") {
	     cout << "Error: invalid command" << endl;
         }
             
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

