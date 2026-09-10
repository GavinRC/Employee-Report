#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

struct employee_data {
    std::string name;
    int employee_number;
    double hourly_rate;
    double hours_worked;
    double gross_pay;
};

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

            employees.push_back(employee);
        }
        std::cout << employees.size() << " employees" << std::endl;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}