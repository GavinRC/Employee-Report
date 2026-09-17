#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <random>
#include <algorithm>

struct employee_data {
    std::string name;
    int employee_number;
    double hourly_rate;
    double hours_worked;
    double gross_pay;
};
int generateRandomNumber(int min, int max);
void randomizeVector(std::vector<employee_data> &employees);
void printTable(std::vector<employee_data> &employees);
void sortVectorByGrossPay(std::vector<employee_data> &employees);

int generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

void printTable(std::vector<employee_data> &employees) {
    std::cout << std::left << std::setw(15) << "NAME" << std::setw(15) << "EMPNUMBER" << std::left << std::setw(15) << "HOURLY RATE" << std::setw(15) << "HOURS WORKED" << std::setw(15) << "GROSS PAY" << "\n----------------------------------------------------------------------" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    for (employee_data employee:employees) {
        std::cout << std::left << std::setw(17) << employee.name << std::setw(15) << employee.employee_number << std::right << "$" << employee.hourly_rate << std::setw(15) << employee.hours_worked << std::setw(9) << "$" << employee.gross_pay << std::endl;
    }
}

void randomizeVector(std::vector<employee_data> &employees) {
    std::vector<employee_data> copyVector = employees;
    std::vector<employee_data> tempVector;
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::shuffle(std::begin(employees), std::end(employees), gen);
    for (int i = 0; i < copyVector.size(); i++) {
        int index = generateRandomNumber(0, employees.size() - 1);
        tempVector.push_back(employees[index]);
        employees.erase(employees.begin() + index);
    }
    employees = tempVector;
}

void sortVectorByGrossPay(std::vector<employee_data> &employees) {
    std::vector<employee_data> emptyVector;
    while (employees.empty() != true) {
        int max = employees[0].gross_pay;
        int maxIndex = 0;
        for (int i = 1; i < employees.size(); i++) {
            if (employees[i].gross_pay > max) {
                max = employees[i].gross_pay;
                maxIndex = i;
            }
        }
        emptyVector.push_back(employees[maxIndex]);
        employees.erase(employees.begin() + maxIndex);
    }
    employees = emptyVector;
}

std::string data_directory = "C:/Users/gavin/CLionProjects/Employee-Report";

std::vector<employee_data> employees;
int main() {
    try {
        std::ifstream csvFile;
        csvFile.open("EmployeeData.csv");

        std::string line;
        std::getline(csvFile, line);
        while (std::getline(csvFile, line)) {
            employee_data employee;
            std::stringstream current_line(line);
            std::string value;

            std::getline(current_line, employee.name, ',');

            std::getline(current_line, value, ',');
            employee.employee_number = std::stoi(value);

            std::getline(current_line, value, ',');
            employee.hourly_rate = std::stod(value);

            std::getline(current_line, value, ',');
            employee.hours_worked = std::stod(value);

            employee.gross_pay = employee.hourly_rate * employee.hours_worked;

            employees.push_back(employee);
        }


        printTable(employees);
        randomizeVector(employees);
        printTable(employees);
        sortVectorByGrossPay(employees);
        printTable(employees);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}