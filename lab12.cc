/**
 *    @file: lab12.cc
 *  @author: Josh Marusek
 *    @date: 2021-11-12
 *   @brief: Loads an employee file and prints a report based on the data.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Employee {
    int id;
    string firstName;
    string lastName;
    int salary;
};

void loadEmployees (ifstream &dataFile, vector<Employee> &employees);
void printReport(vector<Employee> employees);
int calculateTotalSalary(vector<Employee> employees);

int main()
{
    ifstream dataFile;
    vector <Employee> employees;

    dataFile.open("employees.txt");

    if (dataFile.fail()) {
        cout << "Failed to open file." << endl;
         exit(0);
    }

    loadEmployees(dataFile, employees);
    dataFile.close();

    printReport(employees);

    return (EXIT_SUCCESS);
}


void loadEmployees (ifstream &dataFile, vector<Employee> &employees) {
    string nextLine;

    while (getline(dataFile, nextLine)) {
        Employee nextEmployee;
        int spaceIndex = -1;
        int prevSpaceIndex;
        
        prevSpaceIndex = spaceIndex + 1;
        spaceIndex = nextLine.find(' ', prevSpaceIndex);
        nextEmployee.id = stoi(nextLine.substr(prevSpaceIndex, (spaceIndex - prevSpaceIndex)));

        prevSpaceIndex = spaceIndex + 1;
        spaceIndex = nextLine.find(' ', prevSpaceIndex);
        nextEmployee.firstName = nextLine.substr(prevSpaceIndex, (spaceIndex - prevSpaceIndex));

        prevSpaceIndex = spaceIndex + 1;
        spaceIndex = nextLine.find(' ', prevSpaceIndex);
        nextEmployee.lastName = nextLine.substr(prevSpaceIndex, (spaceIndex - prevSpaceIndex));
        
        prevSpaceIndex = spaceIndex + 1;
        spaceIndex = nextLine.find(' ', prevSpaceIndex);
        nextEmployee.salary = stoi(nextLine.substr(prevSpaceIndex, (spaceIndex - prevSpaceIndex)));

        employees.push_back(nextEmployee);
    }
}

void printReport(vector<Employee> employees) {
    cout << "Sorted by name" << endl;
    cout << left << setw(8) << "ID" << left << setw(20) << "Name" << "Salary" << endl;
    cout << string(36, '-') << endl;

    for (size_t i = 0; i < employees.size(); i++) {
        cout << left << setw(8) << employees[i].id;
        cout << left << setw(20) << (employees[i].firstName + " " + employees[i].lastName);
        cout << "$" << employees[i].salary << ".00" << endl;
    }

    cout << endl;
    cout << "Total Payroll: $" << calculateTotalSalary(employees) << ".00" << endl;
}

int calculateTotalSalary(vector<Employee> employees) {
    int total = 0;
    for (size_t i = 0; i < employees.size(); i++) {
        total += employees[i].salary;
    }
    
    return total;
}