#pragma once
// suppliers.h
// This file contains the declaration of the suppliers class and its methods.

#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#include <iostream>
#include <mysql.h>
#include <sstream>

using namespace std;

class suppliers {
    int id;                // Primary Key
    string name;
    long int phn;
    string location;
public:
    suppliers() {
        id = 0;
        name = "";
        phn = 0;              //constructor
        location = "";
       
    }
    
    ~suppliers() {
        cout << "suppliers object destroyed" << endl;    //distructor 
    }
    void add_sup();          // Method to add a new supplier
    void remove_supplier();  // Method to remove a supplier
    void search_id();        // Method to search for a supplier by ID
};

#endif // SUPPLIERS_H


// ---------------------
//suppliers  functions
// ----------------------

void suppliers::add_sup() {
    cout << "Enter the Supplier Name : ";
    cin >> name;
    cout << "Enter Phone no. : ";
    cin >> phn;
    cout << "Enter the location :";
    cin >> location;

    // Clear previous stringstream content
    stmt.str("");

    // Build SQL query
    stmt << "INSERT INTO suppliers(name, phone, location) VALUES ('" << name << "','" << phn << "','" << location << "');";

    // Get the query string
    query = stmt.str();
    const char* q = query.c_str();

    try {
        // Execute the SQL query
        if (mysql_query(conn, q)) {
            // Error occurred during query execution
            throw runtime_error("MySQL query execution failed");
        }
        else {
            // Query executed successfully
            cout << endl << endl << "Supplier Record Inserted Successfully" << endl << endl << endl;
        }
    }
    catch (const exception& e) {
        // Exception occurred
        cerr << "Error: " << e.what() << endl;
        cerr << "Contact Technical Team" << endl << endl;
    }
}


void suppliers::remove_supplier() {
    try {
        // Prompt user for the supplier id to remove
        cout << "Enter the supplier id to remove the Supplier : ";
        if (!(cin >> id)) {
            throw runtime_error("Invalid input for supplier id");
        }

        // Prepare SQL statement to delete supplier
        stmt.str("");
        stmt << "DELETE FROM suppliers WHERE id = " << id << ";";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query to delete supplier
        if (mysql_query(conn, q) != 0) {
            throw runtime_error(mysql_error(conn));
        }

        // Display success message
        cout << "Supplier Removed." << endl;
    }
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }
}

void suppliers::search_id() {
    try {
        // Prompt user to enter the supplier ID
        cout << "Enter the supplier id to find the Supplier details : ";
        cin >> id;
        // Check if input is valid
        if (cin.fail()) {
            throw "Invalid input! Please enter a valid integer for supplier id.";
        }

        // Construct SQL query to search for supplier details by ID
        stmt.str("");
        stmt << "Select * from suppliers where id = " << id << ";";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "MySQL query execution failed!";
        }

        // Store query result
        res_set = mysql_store_result(conn);
        if (!res_set) {
            throw "Failed to retrieve data from the database!";
        }

        // If supplier details are found, display them
        if ((row = mysql_fetch_row(res_set)) != NULL) {
            cout << "Details of Supplier Id : " << row[0] << endl;
            cout << "Name : " << row[1] << endl;
            cout << "Phone no. : " << row[2] << endl;
            cout << "location :" << row[3] << endl;
        }
        else {
            // If no supplier is found with the given ID, inform the user
            cout << "No Supplier Found!!";
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
