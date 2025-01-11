#pragma once
// members.h
// This file contains the declaration of the members class and its methods.

#ifndef MEMBERS_H
#define MEMBERS_H

#include <iostream>
#include <mysql.h>
#include <sstream>

using namespace std;

// Struct to store date information
class members {
    int id;                // Primary Key
    string name;
    string location;
    long int phn;
    date beg_date;
    date end_date;
    string valid;
public:
    // Constructor
    members() {
        id = 0;
        name = "";
        location = "";
        phn = 0;
        beg_date = date(); // Assuming date() initializes to default value
        end_date = date(); // Assuming date() initializes to default value
        valid = "No";
    }

    // Destructor
    ~members() {
        cout << "members object destroyed" << endl;
    }

    void add_mem();        // Method to add a new member
    void refresh();        // Method to refresh member information
    void search_mem();     // Method to search for a member by ID
};
;

#endif // MEMBERS_H


// +---------------------+
// | members functions   |
// +---------------------+

void members::add_mem() {
    try {
        // Prompt user to enter member details
        cout << "Enter the name of the member : ";
        cin >> name;
        cout << "Enter phone no. : ";
        cin >> phn;
        cout << "Enter location :" << endl;
        cin >> location;

        // Construct SQL query to insert new member into database
        stmt.str("");
        stmt << "insert into members (name, location, phone, beg_date, end_date, valid) values ('" << name << "','" << location << "','" << phn << "', curdate(), Date_add(curdate(), INTERVAL 1 YEAR), 'valid');";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to add member!";
        }

        // Fetching member ID
        stmt.str("");
        stmt << "Select id from members where phone_no = " << phn << ";";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to fetch member ID!";
        }

        // Store query result
        res_set = mysql_store_result(conn);
        row = mysql_fetch_row(res_set);

        // Inform user that the member has been added successfully and display their ID
        cout << endl << endl << endl << endl;
        cout << "Member Added successfully" << endl << endl << "Member Id : " << row[0];
        cout << endl << endl << endl << endl;
    }
    catch (const char* msg) {
        // Catch and handle exceptions related to database operations
        cerr << "Error: " << msg << endl;
    }
    catch (...) {
        // Catch and handle unexpected exceptions
        cerr << "An unexpected error occurred." << endl;
    }
}

void members::refresh() {
    try {
        // Construct SQL query to update membership status for expired members
        query = "Update members set valid = 'invalid' where end_date <= curdate();";
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to refresh membership status!";
        }
    }
    catch (const char* msg) {
        // Catch and handle exceptions related to database operations
        cerr << "Error: " << msg << endl;
    }
    catch (...) {
        // Catch and handle unexpected exceptions
        cerr << "An unexpected error occurred." << endl;
    }
}


void members::search_mem() {
    try {
        // Prompt user to enter member ID for searching
        cout << "Enter member id : ";
        cin >> id;

        // Construct SQL query to retrieve member details by ID
        stmt.str("");
        stmt << "Select * from members where id  = " << id << ";";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to search for member!";
        }

        // Store query result
        res_set = mysql_store_result(conn);

        // If member found, display their details
        if ((row = mysql_fetch_row(res_set)) != NULL) {
            cout << "Member Details" << endl;
            cout << "Name : " << row[1] << endl;
            cout << "Address : " << endl << row[2] << endl << row[3] << endl << row[4] << endl;
            cout << "State : " << row[5] << endl;
            cout << "Contact no. : " << row[6] << endl;
            cout << "Membership begin date : " << row[7] << endl;
            cout << "Membership end date  : " << row[8] << endl;
            cout << "Membership Status : " << row[9] << endl << endl << endl;
        }
        else {
            // If no member is found with the given ID, inform the user
            cout << "No Member Found!!" << endl << endl << endl;
        }
    }
    catch (const char* msg) {
        // Catch and handle exceptions related to database operations
        cerr << "Error: " << msg << endl;
    }
    catch (...) {
        // Catch and handle unexpected exceptions
        cerr << "An unexpected error occurred." << endl;
    }
}
