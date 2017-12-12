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
#include <cstring>
#include <cstdlib>
#include <iomanip>
using namespace std;

static int DonutSelectCallBack(void* db, int argc, char **argv, char **colNames);
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

	//
	sql = "SELECT * FROM Donuts;";
	return_code = sqlite3_exec(donutBase,
			sql.c_str(),
			DonutSelectCallBack,
			(void*)"Donuts Select",
			&ErrMsg);

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

static int DonutSelectCallBack(void* db, int argc, char **argv, char **colNames){
	string nullHandler;
	Donut *tempDonut = new Donut();
	for (int i = 0; i < argc; i++){
		nullHandler = argv[i] ? argv[i] : "NULL";
		if(strcmp(colNames[i], "Flavor") == 0){
			tempDonut->Flavor = nullHandler;
		}
		else if(strcmp(colNames[i], "Price") == 0){
			tempDonut->Price = stod(argv[i]);
		}
		else if(strcmp(colNames[i], "Cost") == 0){
			tempDonut->Cost = stod(argv[i]);
		}
		else if(strcmp(colNames[i], "Calories") == 0){
			tempDonut->Calories = atoi(argv[i]);
		}
		else if(strcmp(colNames[i], "Filling") == 0){
			tempDonut->Filling = nullHandler;
		}
		else{
			cout << "Error in EmpSelectCallBack" << endl;
		}
	}
	donutVect.push_back(tempDonut);
	//Probably have a memory leak here
	//cout << endl;
	return 0;
}
void PrintAllDonuts(sqlite3* database){
	for (unsigned int i = 0; i < donutVect.size(); i++){
		cout << setw(15) << left << "Donut Menu   " << endl;
		cout << setw(15) << "-------------" << endl;
		cout << setw(15) << "Flavor: " << donutVect[i]->Flavor << endl;
		cout << setw(15) << "Filling: " << donutVect[i]->Filling << endl;
		cout << setw(15) << "Calories: " << donutVect[i]->Calories << endl;
		cout << setw(15) << "Cost: " << donutVect[i]->Cost << endl;
		cout << setw(15) << "Price: " << donutVect[i]->Price << endl;
		cout << endl;
	}
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
