//
//  utilities.h
//  CPPUtilities
//
//  Created by Bill Komanetsky on 1/29/15.
//  Copyright (c) 2015 Bill Komanetsky. All rights reserved.
//

#ifndef __CPPUtilities__utilities__
#define __CPPUtilities__utilities__

#include <cmath>
#include <stdio.h>
#include <iostream>
using namespace std;

//
//Prototypes for utilities.cpp
//
string makeUpperCase(string);
string makeLowerCase(string);
void clearCIN(void);
string inputString(string, unsigned int, unsigned int);
int inputInt(string, int, int, int);
double inputDouble(string, double, double, double);
string centerString(string, int);
int getRandomInt(int, int);
double getRandomDouble(int, int, int);
bool verifyAction(string);
char askOverWrite(void);
string getRandomString(int, int);


#endif /* defined(__CPPUtilities__utilities__) */
