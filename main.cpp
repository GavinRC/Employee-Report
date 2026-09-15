#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

struct employee_data {
    std::string name;
    int employee_number;
    double hourly_rate;
    double hours_worked;
    double gross_pay;
};

void printTable(std::vector<employee_data> &employees);;

void printTable(std::vector<employee_data> &employees) {
    std::cout << std::left << std::setw(15) << "NAME:" << std::setw(15) << "EMPNUMBER" << std::right << std::setw(15) << "HOURLY RATE:" << std::setw(15) << "HOURS WORKED" << std::setw(15) << "GROSS PAY:" << "\n----------------------------------------------------------------------" << std::endl;

    std::cout << std::fixed << std::setprecision(2);
    for (employee_data employee:employees) {
        std::cout << std::left << std::setw(17) << employee.name << std::setw(18) << employee.employee_number << std::right << "$" << employee.hourly_rate << std::setw(15) << employee.hours_worked << std::setw(11) << "$" << employee.gross_pay << std::endl;
    }
}
std::string data_directory = "C:/Users/gavin/CLionProjects/Employee-Report";

std::vector<employee_data> employees;
int main() {
    try {
        std::ifstream data;
        data.open("EmployeeData.csv");

        std::string line;
        std::getline(data, line);
        while (std::getline(data, line)) {
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
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}