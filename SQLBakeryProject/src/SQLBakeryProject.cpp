//============================================================================
// Name        : SQLBakeryProject.cpp
// Author      : Bryce Hoecker
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sqlite3.h>
#include "Donut.hpp"
#include <vector>
using namespace std;

void PrintAllDonuts(sqlite3* database);
void AddADonut(sqlite3* database);
void DeleteADonut(sqlite3* database);
void UpdateDonutPrice(sqlite3* database);
void UpdateDonutCost(sqlite3* database);
void DeleteAllDonuts(sqlite3* database);

static vector<Donut*> donutVect;

int main() {
	int userChoice = 1;
	int return_code;
	sqlite3 *donutBase;
	char *ErrMsg = 0;
	string sql;

	return_code = sqlite3_open("DonutDB.DB", &donutBase);
	if (return_code){
		cout << "Error opening the database" << endl;
	}
	else{
		cout << "Database opened successfully" << endl;
	}

	cout << "Welcome to the Bakery!" << endl;
	//Get userChoice
	if (userChoice == 1){
		PrintAllDonuts(donutBase);
	}
	else if (userChoice == 2){
		AddADonut(donutBase);
	}
	else if (userChoice == 3){
		DeleteADonut(donutBase);
	}
	else if (userChoice == 4){
		UpdateDonutPrice(donutBase);
	}
	else if (userChoice == 5){
		UpdateDonutCost(donutBase);
	}
	else if (userChoice == 6){
		DeleteAllDonuts(donutBase);
	}
	else if (userChoice == 7){
		cout << "Thanks for visiting!" << endl;
	}
	else{
		cout << "Invalid input, please try again" << endl;
	}
	sqlite3_close(donutBase);
	cout << "Program ending, Have a nice day!" << endl; // prints Program ending, Have a nice day!
	return 0;
}

void PrintAllDonuts(sqlite3* database){

}
void AddADonut(sqlite3* database){

}
void DeleteADonut(sqlite3* database){

}
void UpdateDonutPrice(sqlite3* database){

}
void UpdateDonutCost(sqlite3* database){

}
void DeleteAllDonuts(sqlite3* database){

}
