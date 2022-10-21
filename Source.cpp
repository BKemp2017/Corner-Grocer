/*Blake Kemp
*Southern New Hampshire University
*CS 210 Project 3
*10/15/2022
*/

#include <Python.h>
#include <iostream>
#include <iomanip>
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void DrawMenu() {
	//initialize the method variables
	int menuLoop = 0;
	int wordCount = 0;
	int itemQuantity = 0;
	string searchTerm;
	string itemName;
	ifstream fileInput; //open ifstream for file

	while (menuLoop != 4) {
		//Prompt and collect the user input 
		std::cout << "[1] Calculate the number of times each item appears" << std::endl;
		std::cout << "[2] Calculate the frequency of a specific item" << std::endl;
		std::cout << "[3] Create a histogram based on the number of appearances of each item" << std::endl;
		std::cout << "[4] Quit" << std::endl;

		std::cin >> menuLoop;

		//Check if user input is valid. If not, prompt for correct input
		while (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please input a valid selection: ";
			std::cin >> menuLoop;
		}

		//Switch statement: Executes the proper command based on the user input 
		switch (menuLoop) {
			//Case 1: Calculate the number of times each item will appear, then print you a list
		case 1:
			system("CLS"); //clears the screen 
			CallProcedure("CountAll"); //Calls the python function "CountAll"
			std::cout << std::endl;
			break;

			//Case 2: Calculate the number of times a specific item appears, then prints the result
		case 2:
			system("CLS"); //Clears the screen 
			std::cout << "Which item would you like to search for?" << std::endl;
			std::cin >> searchTerm;

			//Call python function with the search term, then return an integer word count value.
			wordCount = callIntFunc("CountInstances", searchTerm);
			//Print statement with retured word count.
			std::cout << std::endl << searchTerm << " : " << wordCount << std::endl << std::endl;
			break;

			//Case 3: Print a histogram based on how many times each item appears. similar to case 1 but with stars
		case 3:
			system("CLS");
			CallProcedure("CollectData"); //Call the python function "CollectData"
			fileInput.open("frequency.dat"); // Open frequency.dat
			fileInput >> itemName; //Collect first item on the list
			fileInput >> itemQuantity;

			//For each line in the file, print a histogram 
			while (!fileInput.fail()) {

				//Prints the item name, then setus it up for the histogram
				std::cout << std::setw(14) << std::left << itemName << std::setw(6);

				//Print the item quantity as number of asterisks
				for (int i = 0; i < itemQuantity; i++) {
					std::cout << right << "*";
				}


				//Prepare the next line, then set the items name and quantity
				std::cout << std::endl;
				fileInput >> itemName;
				fileInput >> itemQuantity;
			}

			//Close frequency.dat, then break
			fileInput.close();
			break;

			//Case 4: Quits the program
		case 4:
			return;
			//Default case: Invalid input
		default:
			std::cout << "Please input a valid selection.";
			std::cout << std::endl;
			break;
		}
	}
}

//Main method. Calls the DrawMenu method to collect the user input 
int main() {
	//Draw the user menu
	DrawMenu();
}