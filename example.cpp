#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

// Global variable
int security_tax = 10;

class Employee
{
    private:
        int employee_ID;
        string employee_name;
        string employee_position;
        string employee_type;
        string start_date;
        double basic_salary;

    public:
        // Getter methods
        int getEmployeeID() { return employee_ID; }
        string getName() { return employee_name; }
        string getPosition() { return employee_position; }
        string getEmployeeType() { return employee_type; }
        string getStartDate() { return start_date; }
        double getBasicSalary() { return basic_salary; }

        // Default constructor
        Employee() : employee_ID(0), employee_name(""), employee_position(""), employee_type(""), start_date(""), basic_salary(0) {}

    // Set employee data
    void setData()
    {
        cout << "Enter Employee ID: ";
        cin >> employee_ID;
        cin.ignore(); // Clear input buffer
        cout << "Enter Employee Name: ";
        getline(cin, employee_name);

        // Loop until a valid employee position is entered
        while (true)
        {
            cout << "Enter Employee Position: ";
            getline(cin, employee_position);

            if (employee_position == "Barista" || employee_position == "barista")
            {
                basic_salary = 1920;
                employee_type = "fulltime";
                break;
            }
            else if (employee_position == "Cashier" || employee_position == "cashier")
            {
                basic_salary = 1790;
                employee_type = "fulltime";
                break;
            }
            else if (employee_position == "Cleaner" || employee_position == "cleaner")
            {
                basic_salary = 1400;
                employee_type = "parttime";
                break;
            }
            else if (employee_position == "Kitchen Staff" || employee_position == "kitchen staff")
            {
                basic_salary = 1850;
                employee_type = "parttime";
                break;
            }
            else if (employee_position == "Waiter" || employee_position == "waiter" || employee_position == "Waitress" || employee_position == "waitress")
            {
                basic_salary = 1700;
                employee_type = "parttime";
                break;
            }
            else if (employee_position == "Supervisor" || employee_position == "supervisor")
            {
                basic_salary = 2400;
                employee_type = "fulltime";
                break;
            }
            else
            {
                cout << "Invalid Employee Position. Please try again." << endl;
            }
        }

        cout << "Enter Employee Start Date (dd/mm/yy): ";
        cin >> start_date;
    }

    void getData()
    {
        // Set width and alignment for the table
        cout << left << setw(20) << "ID" << ": " << setw(20) << employee_ID << endl;
        cout << left << setw(20) << "Name" << ": " << setw(20) << employee_name << endl;
        cout << left << setw(20) << "Position" << ": " << setw(20) << employee_position << endl;
        cout << left << setw(20) << "Type" << ": " << setw(20) << employee_type << endl;
        cout << left << setw(20) << "Start Date" << ": " << setw(20) << start_date << endl;
        cout << left << setw(20) << "Basic Salary" << ": $" << setw(20) << fixed << setprecision(2) << basic_salary << endl;
    }
};

class FullTime : public Employee
{
    private:
        int leave_days;
        double overtime_hours = 0;
        double bonus = 0;
        double overtime_fees = 0;
        double total_amount = 0;
        double tax_salary = 0;
        double net_salary = 0;

    public:
        FullTime() : leave_days(0), overtime_hours(0.0) {}

    void setFullTimeData()
    {
        setData(); // Set common data from Employee
        cout << "Enter number of leave days: ";
        cin >> leave_days;
        cout << "Enter overtime hours: ";
        cin >> overtime_hours;

        // Calculate bonus based on leave days
        if (leave_days == 0)
        {
            bonus = 300;
        }
        else if (leave_days == 1)
        {
            bonus = 200;
        }
        else if (leave_days == 2)
        {
            bonus = 100;
        }
        else
        {
            bonus = 0;
        }

        // Explicitly calculate total salary to update dependent fields
        calculateFulltimeTotalSalary();
    }

    // Calculate total salary
    double calculateFulltimeTotalSalary()
    {
        double salary = getBasicSalary();

        // Calculate overtime fees
        overtime_fees = (((salary / 30) / 8) * overtime_hours) * 2;        

        // Calculate total amount considering leave days and overtime
        if (leave_days < 4 && overtime_hours >= 0)
        {
            total_amount = salary + bonus + overtime_fees;
            // Calculate tax on salary
            tax_salary = (total_amount / 100) * 2;
        }
        else if (leave_days > 4 && overtime_hours > 0)
        {
            total_amount = salary - ((salary / 100) * 1) + overtime_fees - bonus;
            // Calculate tax on salary
            tax_salary = (total_amount / 100) * 2;
        }
        else
        {
            total_amount = salary - bonus + overtime_fees;
            // Calculate tax on salary
            tax_salary = (total_amount / 100) * 2;
        }

        return total_amount;
    }

    double calculateFulltimeTotalNetSalary()
    {
        if (total_amount == 0) // Ensure total_amount is calculated
            calculateFulltimeTotalSalary();

        // Calculate net salary after deductions
        net_salary = total_amount - ((total_amount / 100) * 2) - security_tax;
        return net_salary;
    }

    void getFullTimeData()
    {
        // Ensure all calculations are up-to-date
        calculateFulltimeTotalSalary();
        calculateFulltimeTotalNetSalary();

        // Display all details
        getData();
        cout << left << setw(20) << "Leave Days" << ": " << setw(20) << leave_days << endl;
        cout << left << setw(20) << "Overtime Hours" << ": " << setw(20) << fixed << setprecision(2) << overtime_hours << endl;
        cout << left << setw(20) << "Overtime Fees" << ": $" << setw(20) << fixed << setprecision(2) << overtime_fees << endl;
        cout << left << setw(20) << "Bonus" << ": $" << setw(20) << fixed << setprecision(2) << bonus << endl;
        cout << left << setw(20) << "Tax Deduction" << ": $" << setw(20) << fixed << setprecision(2) << tax_salary << endl;
        cout << left << setw(20) << "Security Deduction" << ": $" << setw(20) << security_tax << endl;
        cout << left << setw(20) << "Total Amount" << ": $" << setw(20) << fixed << setprecision(2) << total_amount << endl;
        cout << left << setw(20) << "Total Net Amount" << ": $" << setw(20) << fixed << setprecision(2) << net_salary << endl;
        cout << endl;
    }
};

class PartTime : public Employee
{
private:
    double hourly_wage = 0;
    double working_hours = 0;
    double total_amount = 0;
    double tax_deduction = 0;
    double net_salary = 0;

public:
    PartTime() : working_hours(0) {}

    void setParttimeData()
    {
        setData(); // Set common data from Employee
        cout << "Enter working hours (Monthly): ";
        cin >> working_hours;

        // Calculate salary components after setting data
        calculateParttimeTotalNetSalary();
    }

    double calculateParttimeTotalNetSalary()
    {
        // Calculate hourly wage from basic salary
        double salary = getBasicSalary();
        hourly_wage = (salary / 30) / 8;

        // Calculate gross total amount based on working hours
        total_amount = hourly_wage * working_hours;

        // Calculate tax deduction (2% of total amount)
        tax_deduction = (total_amount / 100) * 2;

        // Calculate net salary after tax and security deduction
        net_salary = total_amount - tax_deduction - security_tax;

        return net_salary;
    }

    void getParttimeData()
    {
        // Ensure calculations are updated
        calculateParttimeTotalNetSalary();

        // Display part-time employee data
        getData();
        cout << left << setw(20) << "Working Hours" << ": " << setw(20) << fixed << setprecision(2) << working_hours << endl;
        cout << left << setw(20) << "Hourly Wage" << ": $" << setw(20) << fixed << setprecision(2) << hourly_wage << endl;
        cout << left << setw(20) << "Total Amount" << ": $" << setw(20) << fixed << setprecision(2) << total_amount << endl;
        cout << left << setw(20) << "Tax Deduction" << ": $" << setw(20) << fixed << setprecision(2) << tax_deduction << endl;
        cout << left << setw(20) << "Security Deduction" << ": $" << setw(20) << security_tax << endl;
        cout << left << setw(20) << "Total Net Amount" << ": $" << setw(20) << fixed << setprecision(2) << net_salary << endl;
        cout << endl;
    }
};

vector<FullTime> Fulltime_Employees;
vector<PartTime> PartTime_Employees;

// Calculate total monthly payment for all employees
void calculateTotalMonthlyPayment()
{
    int fullTimeCount = 0, partTimeCount = 0;
    double fullTimeTotal = 0, partTimeTotal = 0;

    // Calculate totals for full-time employees
    for (auto& emp : Fulltime_Employees)
    {
        fullTimeCount++;
        fullTimeTotal += emp.calculateFulltimeTotalNetSalary();
    }

    // Calculate totals for part-time employees
    for (auto& emp : PartTime_Employees)
    {
        partTimeCount++;
        partTimeTotal += emp.calculateParttimeTotalNetSalary();
    }

    // Display the results in a table format
    cout << "\nMonthly Payment Summary\n";
    cout << "---------------------------------------------------\n";
    cout << left << setw(25) << "Employee Type" 
         << setw(10) << "Count" 
         << "Total Net Salary\n";
    cout << "---------------------------------------------------\n";
    cout << left << setw(25) << "Full-time Employees" 
         << setw(10) << fullTimeCount 
         << "$" << fixed << setprecision(2) << fullTimeTotal << "\n";
    cout << left << setw(25) << "Part-time Employees" 
         << setw(10) << partTimeCount 
         << "$" << fixed << setprecision(2) << partTimeTotal << "\n";
    cout << "---------------------------------------------------\n";
    cout << left << setw(25) << "Total Employees" 
         << setw(10) << (fullTimeCount + partTimeCount) 
         << "$" << fixed << setprecision(2) << (fullTimeTotal + partTimeTotal) << "\n";
    cout << "---------------------------------------------------\n\n";
}

int main()
{   
    int opt;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "|              Java Jolt Cafe              |" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    while (opt!=7)
    {
        cout << "\nMenu" << endl;
        cout << "1. Insert Employee Data \n"
             << "2. View Fulltime Employees Reports \n"
             << "3. View Parttime Employees Reports \n"
             << "4. Display All Employees \n"
             << "5. Update Employee Data \n"
             << "6. Calculate Total Salaries for All Employees \n"
             << "7. Exit" << endl;
        cin >> opt;
        cin.ignore();

        switch (opt)
        {
        case 1:
        {
            int n = 0;
            cout << "\nHow many employees would you like to add?: ";
            cin >> n;
            cin.ignore(); // Clear input buffer

            for (int i = 0; i < n; i++)
            {
                cout << "Enter details for Employee " << i + 1 << ":" << endl;
                string employee_type;
                cout << "Which Type Of Employee Data You Want To Insert (fulltime/parttime): ";
                cin >> employee_type;

                if (employee_type == "fulltime")
                {
                    cout << "\nAvailable Positions and Basic Salaries:\n";
                    cout << "--------------------------------------\n";
                    cout << "Barista                     : $1920\n";
                    cout << "Cashier                     : $1790\n";
                    cout << "Supervisor                  : $2400\n";
                    cout << "--------------------------------------\n";

                    FullTime New_Employee;
                    New_Employee.setFullTimeData();
                    cout<<endl;
                    Fulltime_Employees.push_back(New_Employee);
                }
                else if (employee_type == "parttime")
                {
                    cout << "\nAvailable Positions and Basic Salaries:\n";
                    cout << "--------------------------------------\n";
                    cout << "Kitchen Staff (part-time)   : $1850\n";
                    cout << "Cleaner (part-time)         : $1400\n";
                    cout << "Waiter/waitress (part-time) : $1700\n";
                    cout << "--------------------------------------\n";

                    PartTime New_Employee;
                    New_Employee.setParttimeData();
                    cout<<endl;
                    PartTime_Employees.push_back(New_Employee);
                }
                else
                {
                    cout << "Invalid Employee Type!!!!" << endl;
                }
            }
            break;
        }
        case 2:
        {
            if (Fulltime_Employees.empty())
            {
                cout << "No Full-Time Employees Found!" << endl;
            }
            else
            {
                
                for (int i = 0; i < Fulltime_Employees.size(); i++)
                {
                    cout << "Full Time Employee Data " << i + 1 << ":" << endl;
                    Fulltime_Employees[i].getFullTimeData();
                }
            }
            break;
        }
        case 3:
        {
            if (PartTime_Employees.empty())
            {
                cout << "No Part-Time Employees Found!" << endl;
            }
            else
            {
                for (int i = 0; i < PartTime_Employees.size(); i++)
                {
                    cout << "Part Time Employee Data " << i + 1 << ":" << endl;
                    PartTime_Employees[i].getParttimeData();
                }
            }
            break;
        }
        case 4:
        {
            cout << "Full-Time Employees:" << endl;
            for (int i = 0; i < Fulltime_Employees.size(); i++)
            {
                Fulltime_Employees[i].getFullTimeData();
            }
            cout << "Part-Time Employees:" << endl;
            for (int i = 0; i < PartTime_Employees.size(); i++)
            {
                PartTime_Employees[i].getParttimeData();
            }
            break;
        }
        
        case 5:
        {
            int num;
            string type;
            bool found = false;

            cout << "Enter The Employee Type to Update Data (fulltime/parttime): ";
            cin >> type;

            if (type == "fulltime")
            {
                cout << "Enter Employee ID You Want To Update: ";
                cin >> num;
                for (int i = 0; i < Fulltime_Employees.size(); i++)
                {
                    if (num == Fulltime_Employees[i].getEmployeeID())
                    {
                        cout << "Updating data for Full-Time Employee ID: " << num << endl;
                        Fulltime_Employees[i].setFullTimeData();
                        Fulltime_Employees[i].calculateFulltimeTotalSalary();
                        Fulltime_Employees[i].calculateFulltimeTotalNetSalary();
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "No Full-Time Employee found with ID: " << num << endl;
                }
            }
            else if (type == "parttime")
            {
                cout << "Enter Employee ID You Want To Update: ";
                cin >> num;
                for (int i = 0; i < PartTime_Employees.size(); i++)
                {
                    if (num == PartTime_Employees[i].getEmployeeID())
                    {
                        cout << "Updating data for Part-Time Employee ID: " << num << endl;
                        PartTime_Employees[i].setParttimeData();
                        PartTime_Employees[i].calculateParttimeTotalNetSalary();
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "No Part-Time Employee found with ID: " << num << endl;
                }
            }
            else
            {
                cout << "Invalid Employee Type! Please enter 'fulltime' or 'parttime'." << endl;
            }

            break;
        }
        case 6:
            {
                calculateTotalMonthlyPayment();
                break;
            }
        case 7:
            return 0;
            
        default:
            cout << "Invalid option, please try again." << endl;
            break;
        }
    }
}