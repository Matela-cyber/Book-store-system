#pragma once
// employees.h
// This file contains the declaration of the employees class and its methods.

#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include <iostream>
#include <mysql.h>
#include <sstream>

using namespace std;


class employees {
    int id;                // Primary Key
    string name;
    string location;
    long int phn;
    date date_of_joining;
    long int salary;
    string mgr_status;     // Check(T or F) def f
public:
    // Constructor
    employees() {
        id = 0;
        name = "";
        location = "";
        phn = 0;
        date_of_joining = date(); // Assuming date() initializes to default value
        salary = 0;
        mgr_status = 'F';
    }

    // Destructor
    ~employees() {
        cout << "employees object destroyed" << endl;
    }

    void add_emp();        // Method to add a new employee
    void search_emp();     // Method to search for an employee by ID
    void assign_mgr_stat(); // Method to assign manager status
    void display();        // Method to display employee details
    void update_sal();     // Method to update employee salary
};

#endif // EMPLOYEES_H

// ---------------------
// employees functions
// ---------------------

void employees::add_emp() {
    try {
        // Prompt user for ID verification
        cout << "Enter Your Id for verification : ";
        cin >> id;

        // Construct SQL query to check manager status of employee
        stmt.str("");
        stmt << "Select mgr_stat from employees where id  = " << id << ";";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to verify employee ID!";
        }

        // Store query result
        res_set = mysql_store_result(conn);

        // If employee not found, inform the user and return
        if ((row = mysql_fetch_row(res_set)) == NULL) {
            cout << "Employee Not Found!!" << endl << endl << endl;
            return;
        }
        else {
            // Check manager status
            mgr_status = (char*)row[0];
            if (mgr_status == "T") {
                cout << "You Do Not have Manager Rights!!!" << endl << endl;
                return;
            }
        }

        // Prompt user to enter details of new employee
        cout << "Enter The details of new employees!!" << endl;
        cout << "Enter The name of the employee : ";
        cin >> name;
        cout << "Enter the Address (in 3 lines) : " << endl;
        cin >> location;
        cout << "Enter phone no.";
        cin >> phn;
        cout << "Enter the salary : ";
        cin >> salary;

        // Construct SQL query to insert new employee into database
        stmt.str("");
        stmt << "Insert into employees (name, location, phone_no, salary, mgr_status) values ('" << name << "','" << location << "'," << phn << "," << salary << ",'" << mgr_status << "');";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to add new employee!";
        }

        // Inform user that the new employee has been added successfully
        cout << endl << endl << "Employee Added Succesfully!" << endl << endl << endl;
    }
    catch (const char* msg) {
        // Catch and handle exceptions related to input validation and database operations
        cerr << "Error: " << msg << endl;
    }
    catch (...) {
        // Catch and handle unexpected exceptions
        cerr << "An unexpected error occurred." << endl;
    }
}


void employees::assign_mgr_stat() {
    try {
        // Prompt user for ID verification
        cout << "Enter Your Id for verification : ";
        cin >> id;

        // Construct SQL query to check manager status of employee
        stmt.str("");
        stmt << "Select mgr_status from employees where id  = " << id << ";";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to verify employee ID!";
        }

        // Store query result
        res_set = mysql_store_result(conn);

        // If employee not found, inform the user and return
        if ((row = mysql_fetch_row(res_set)) == NULL) {
            cout << "Employee Not Found!!" << endl << endl << endl;
            return;
        }
        else {
            // Check manager status
            mgr_status = (char*)row[0];
            if (mgr_status == "T") {
                cout << "You Do Not have Manager Rights!!!" << endl << endl;
                return;
            }
        }

        // Prompt user to enter the employee ID to grant Manager status
        cout << "Enter the employee id to grant Manager status : ";
        cin >> id;

        // Construct SQL query to update employee's manager status
        stmt.str("");
        stmt << "update employees set mgr_stat = 'T' where id = " << id << ";";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to grant Manager status!";
        }

        // Inform user that Manager status has been granted successfully
        cout << endl << endl << endl;
        cout << "Manager Status granted";
        cout << endl << endl << endl;
    }
    catch (const char* msg) {
        // Catch and handle exceptions related to input validation and database operations
        cerr << "Error: " << msg << endl;
    }
    catch (...) {
        // Catch and handle unexpected exceptions
        cerr << "An unexpected error occurred." << endl;
    }
}


void employees::search_emp() {
    try {
        // Prompt user to enter the ID for searching an employee
        cout << "Enter the id for searching an employee : ";
        cin >> id;

        // Construct SQL query to retrieve employee details by ID
        stmt.str("");
        stmt << "Select * from employees where id  = " << id << ";";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to search for employee!";
        }

        // Store query result
        res_set = mysql_store_result(conn);

        // If employee found, display their details
        if ((row = mysql_fetch_row(res_set)) != NULL) {
            cout << "Employees Details" << endl;
            cout << "Name : " << row[1] << endl;
            cout << "location : " << row[2] << endl;
                cout << "salary : " << row[3] << endl;
            cout << "mgr_status  : " << row[4] << endl << endl << endl;
        }
        else {
            // If no employee is found with the given ID, inform the user
            cout << "No Employee Found!!" << endl << endl << endl;
        }
    }
    catch (const char* msg) {
        // Catch and handle exceptions related to input validation and database operations
        cerr << "Error: " << msg << endl;
    }
    catch (...) {
        // Catch and handle unexpected exceptions
        cerr << "An unexpected error occurred." << endl;
    }
}


void employees::display() {
    try {
        int i = 0;

        // Construct SQL query to retrieve all employees
        query = "Select * from employees;";
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to retrieve employees!";
        }

        // Store query result
        res_set = mysql_store_result(conn);

        // If employees found, display their details
        if ((row = mysql_fetch_row(res_set)) != NULL) {
            do {
                cout << "Employees Details of Emp no." << ++i << endl;
                cout << "Name : " << row[1] << endl;
                cout << "location : " << endl << row[2] << endl << row[3] << endl << row[4] << endl;
                cout << "salary : " << row[6] << endl;
                cout << "mgr_status : " << row[8] << endl;
                cout << endl << endl << endl << endl;
            } while ((row = mysql_fetch_row(res_set)) != NULL);
        }
        else {
            // If no employees found, inform the user
            cout << "Employees Not found!" << endl;
        }
    }
    catch (const char* msg) {
        // Catch and handle exceptions related to input validation and database operations
        cerr << "Error: " << msg << endl;
    }
    catch (...) {
        // Catch and handle unexpected exceptions
        cerr << "An unexpected error occurred." << endl;
    }
}


void employees::update_sal() {
    try {
        // Prompt user to enter the ID and updated salary for an employee
        cout << "Enter the id to update the salary of an employee : ";
        cin >> id;
        cout << "Enter the updated salary : ";
        cin >> salary;

        // Construct SQL query to update employee's salary
        stmt.str("");
        stmt << "Update employees set salary = " << salary << " where id  = " << id << ";";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to update employee salary!";
        }

        // Inform user that the salary has been updated successfully
        cout << endl << endl << endl << endl;
        cout << "Salary update Successfully";
        cout << endl << endl << endl << endl;
    }
    catch (const char* msg) {
        // Catch and handle exceptions related to input validation and database operations
        cerr << "Error: " << msg << endl;
    }
    catch (...) {
        // Catch and handle unexpected exceptions
        cerr << "An unexpected error occurred." << endl;
    }
}

