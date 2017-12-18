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
#include "utilities.hpp"
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <sstream>
using namespace std;

static int DonutSelectCallBack(void* db, int argc, char **argv, char **colNames);
void PrintAllDonuts(sqlite3* database);
void AddADonut(sqlite3* database);
void DeleteADonut(sqlite3* database);
void UpdateDonutPrice(sqlite3* database);
void UpdateDonutCost(sqlite3* database);
void DeleteAllDonuts(sqlite3* database);
int FancyMenu(void);

static vector<Donut*> donutVect;

int main() {
	int userChoice = 0;
	//now get userChoice from the fancy menu function
	int return_code;
	sqlite3 *donutBase;
	char *ErrMsg = 0;
	string sql;

	cout << "Welcome to the Bakery Inventory system." << endl;

	return_code = sqlite3_open("DonutDB.DB", &donutBase);
	if (return_code){
		cout << "Error opening the database" << endl;
	}
	else{
		cout << "Database opened successfully" << endl;
	}

	//SELECT
//	sql = "SELECT * FROM Donuts;";
//	return_code = sqlite3_exec(donutBase,
//			sql.c_str(),
//			DonutSelectCallBack,
//			(void*)"Donuts Select",
//			&ErrMsg);

	//cout << "Welcome to the Bakery Inventory system." << endl;	//Makes more sense to welcome before trying to open DB
	//Get userChoice
	//Menu Loop
	while(userChoice != 7){
		sql = "SELECT * FROM Donuts;";
			return_code = sqlite3_exec(donutBase,
					sql.c_str(),
					DonutSelectCallBack,
					(void*)"Donuts Select",
					&ErrMsg);
		userChoice = FancyMenu();
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
		else if (userChoice == 7 || userChoice == -999){
			cout << "Thanks for using the inventory system." << endl;
			break;
		}
		else{
			cout << "Invalid input, please try again" << endl;
		}
		//Opening and closing DB for the loop. (REFRESHING DATABASE)
		//Closing
//		cout << endl;
//		cout << "Refreshing Database" << endl;
		for (unsigned int i = 0; i < donutVect.size(); i++){
			delete donutVect[i];
		}//for
		donutVect.clear();
//		sqlite3_close(donutBase);
//		//Opening
//		return_code = sqlite3_open("DonutDB.DB", &donutBase);
//		if (return_code){
//			cout << "Error opening the database" << endl;
//		}
//		else{
//			cout << "Database opened successfully" << endl;
//		}
//		//SELECT
//		sql = "SELECT * FROM Donuts;";
//		return_code = sqlite3_exec(donutBase,
//				sql.c_str(),
//				DonutSelectCallBack,
//				(void*)"Donuts Select",
//				&ErrMsg);
//		//END OF REFRESHING DATABASE
	}//while
	sqlite3_close(donutBase);
	for (unsigned int i = 0; i < donutVect.size(); i++){
		delete donutVect[i];
	}//for
	donutVect.clear();
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
	cout << "Printing all donuts." << endl;
	cout << setw(15) << left << "Donut Menu:  " << endl;
	for (unsigned int i = 0; i < donutVect.size(); i++){
		cout << setw(15) << "-------------" << endl;
		cout << setw(15) << "Flavor: " << donutVect[i]->Flavor << endl;
		cout << setw(15) << "Filling: " << donutVect[i]->Filling << endl;
		cout << setw(15) << "Calories: " << donutVect[i]->Calories << endl;
		cout << setw(15) << "Cost: " << donutVect[i]->Cost << endl;
		cout << setw(15) << "Price: " << donutVect[i]->Price << endl;
		cout << endl;
	}
	cout << "Done printing all donuts." << endl;
	//donutVect.clear();
}
void AddADonut(sqlite3* database){
	string sql;
	stringstream ss;
	int returnCode;
	char* errMsg;
	//cout << "Adding a donut." << endl;
	//
	string flavor;
//	cout << "Please enter a Donut Flavor: ";
//	getline(cin, flavor);
	flavor = inputString("Please enter a Donut Flavor: ", 0, 256);

	double price;
	price = inputDouble("Please enter the price: ", 0.01, 100.0, -999);
//	cout << "Please enter the Price: ";
//	cin >> price;
//	cin.clear();
//	cin.ignore(32768, '\n');

	double cost;
	cost = inputDouble("Please enter the cost: ", 0.01, 100.0, -999);
//	cout << "Please enter the Cost: ";
//	cin >> cost;
//	cin.clear();
//	cin.ignore(32768, '\n');

	int calories;
	calories = inputInt("Please enter the calories: ", 1, 10000, -999);
//	cout << "Please enter the Calories: ";
//	cin >> calories;
//	cin.clear();
//	cin.ignore(32768, '\n');

	string filling;
	filling = inputString("Please enter a Donut filling: ", 0, 256);
//	cout << "Please enter the Filling: ";
//	getline(cin, filling);

	//Build up the SQL Insert statement based on user input
	ss << "INSERT INTO Donuts (Flavor, Price, Cost, Calories, Filling) VALUES (";
	ss << "'" << flavor << "', ";
	ss << price << ", ";
	ss << cost << ", ";
	ss << calories << ", ";
	ss << "'" << filling << "'); ";

	sql = ss.str();
//	cout << "The sql string is: " << endl;
//	cout << sql << endl;

	returnCode = sqlite3_exec(database, sql.c_str(), DonutSelectCallBack, 0, &errMsg);

	if (returnCode != SQLITE_OK){
		cout << "Error inserting: " << sql << endl;
		cout << "Error message: " << errMsg << endl;
	    sqlite3_free(errMsg);
	}
	else{
		cout << "Donut sucessfully added!" << endl;
	}
	//cout << "Done Adding a donut." << endl;
	//donutVect.clear();
}
void DeleteADonut(sqlite3* database){
	string sql;
	stringstream ss;
	int returnCode;
	char* errMsg;
	//cout << "Deleting a donut." << endl;
	string userFlavor;
//	cout << "Please enter a Donut to Delete: ";
//	getline(cin, userFlavor);
	userFlavor = inputString("Please enter a Donut to Delete: ", 1, 256);

	//Build up the SQL Insert statement based on user input
	ss << "DELETE FROM Donuts ";
	ss << "WHERE Flavor = ";
	ss << "'" << userFlavor << "';";

	sql = ss.str();

//	cout << "The sql string is: " << endl;
//	cout << sql << endl;

	returnCode = sqlite3_exec(database, sql.c_str(), DonutSelectCallBack, 0, &errMsg);

	if (returnCode != SQLITE_OK){
		cout << "Error Deleting: " << sql << endl;
		cout << "Error message: " << errMsg << endl;
	    sqlite3_free(errMsg);
	}
	else{
		cout << "Donut sucessfully removed." << endl;
	}
	//donutVect.clear();
}
void UpdateDonutPrice(sqlite3* database){
	string sql;
	stringstream ss;
	int returnCode;
	char* errMsg;
	//cout << "Updating a donut." << endl;

	//
	string flavor;
//	cout << "Please enter a Donut Flavor for update: ";
//	getline(cin, flavor);
	flavor = inputString("Please enter a Donut Flavor for update: ", 1, 256);

	double price;
	cout << "Please enter the new Price: ";
	price = inputDouble("Please enter the new Price: ", 0.01, 100.5, -999);
//	cin >> price;
//	cin.clear();
//	cin.ignore(32768, '\n');

	//Build up the SQL Update statement based on user input
	ss << "UPDATE Donuts set Price = ";
	ss << price << " ";
	ss << " WHERE Flavor = ";
	ss << "'" << flavor << "';";

	sql = ss.str();
//	cout << "The sql string is: " << endl;
//	cout << sql << endl;

	returnCode = sqlite3_exec(database, sql.c_str(), DonutSelectCallBack, 0, &errMsg);

	if (returnCode != SQLITE_OK){
		cout << "Error inserting: " << sql << endl;
		cout << "Error message: " << errMsg << endl;
	    sqlite3_free(errMsg);
	}
	else{
		cout << "Donut Price sucessfully updated!" << endl;
	}
	//donutVect.clear();
}
void UpdateDonutCost(sqlite3* database){
	string sql;
	stringstream ss;
	int returnCode;
	char* errMsg;

	//
	string flavor;
//	cout << "Please enter a Donut Flavor for update: ";
//	getline(cin, flavor);
	flavor = inputString("Please enter a Donut Flavor for update: ", 1, 256);

	double cost;
//	cout << "Please enter the new Cost: ";
//	cin >> cost;
//	cin.clear();
//	cin.ignore(32768, '\n');
	cost = inputDouble("Please enter the new Cost: ", 0.01, 100.0, -999);


	//Build up the SQL Update statement based on user input
	ss << "UPDATE Donuts set Cost = ";
	ss << cost << " ";
	ss << " WHERE Flavor = ";
	ss << "'" << flavor << "';";

	sql = ss.str();
//	cout << "The sql string is: " << endl;
//	cout << sql << endl;

	returnCode = sqlite3_exec(database, sql.c_str(), DonutSelectCallBack, 0, &errMsg);

	if (returnCode != SQLITE_OK){
		cout << "Error inserting: " << sql << endl;
		cout << "Error message: " << errMsg << endl;
	    sqlite3_free(errMsg);
	}
	else{
		cout << "Donut Cost sucessfully updated!" << endl;
	}
	//donutVect.clear();
}
void DeleteAllDonuts(sqlite3* database){
	string sql;
	int returnCode;
	char* errMsg;

	cout << "Deleting ALL donuts." << endl;

	sql = "DELETE FROM Donuts";

//	cout << "The sql string is: " << endl;
//	cout << sql << endl;

	returnCode = sqlite3_exec(database, sql.c_str(), DonutSelectCallBack, 0, &errMsg);

	if (returnCode != SQLITE_OK){
		cout << "Error Deleting: " << sql << endl;
		cout << "Error message: " << errMsg << endl;
	    sqlite3_free(errMsg);
	}
	else{
		cout << "All Donuts sucessfully deleted." << endl;
	}
	//donutVect.clear();
}
int FancyMenu(void){
	int userInput = 0;
	cout << "Here are a list of operations that you can do: " << endl;
	cout << "1) Print all the donuts." << endl;
	cout << "2) Add a donut." << endl;
	cout << "3) Delete a donut." << endl;
	cout << "4) Update a donut's Price." << endl;
	cout << "5) Update a donut's Cost." << endl;
	cout << "6) Delete all the donuts." << endl;
	cout << "7) Exit the program." << endl;
	cout << "Please enter the number that relates with what you want to do." << endl;
	cin >> userInput;
	cin.clear();
	cin.ignore(32768, '\n');

	//userInput = inputInt("Please enter the number that relates with what you want to do.", 1, 7, 7);

	return userInput;
}
