#pragma once
// purchases.h
// This file contains the declaration of the purchases class and its methods.

#ifndef PURCHASES_H
#define PURCHASES_H

#include <iostream>
#include <mysql.h>
#include <sstream>

using namespace std;

// Struct to store date information
typedef struct {
    int date;
    int month;
    int year;
} date;
class purchases {
    int ord_id;            // Primary Key
    int book_id;           // FK ref (books)
    int sup_id;            // FK ref (suppliers)
    int qty;
    date dt_ordered;
    int eta;
    char received;         
    int inv;
public:
    // Constructor
    purchases() {
        ord_id = 0;
        book_id = 0;
        sup_id = 0;
        qty = 0;
        // Initialize other variables to their default values
        dt_ordered = date(); // Assuming date() initializes to default value
        eta = 0;
        received = 'F';
        inv = 0;
    }
    ~purchases() {
        cout << "purchases object destroyed" << endl;    //distructor 
    }

    void new_ord();        // Method to add a new order
    void view();           // Method to view orders
    void mar_cancel();     // Method to mark an order as cancelled
    void mark_reciv();     // Method to mark an order as received
};


#endif // PURCHASES_H


// -----------------------
//  Purchases functions
// -----------------------

void purchases::new_ord() {
    try {
        // Prompt user to enter details for a new order
        cout << "Enter the book Id : ";
        cin >> book_id;
        if (cin.fail()) {
            throw "Invalid input! Please enter a valid integer for book id.";
        }

        cout << "Enter Supplier Id : ";
        cin >> sup_id;
        if (cin.fail()) {
            throw "Invalid input! Please enter a valid integer for supplier id.";
        }

        cout << "Enter the Quantity : ";
        cin >> qty;
        if (cin.fail()) {
            throw "Invalid input! Please enter a valid integer for quantity.";
        }

        cout << "Estimated expected Delivery (in days) : ";
        cin >> eta;
        if (cin.fail()) {
            throw "Invalid input! Please enter a valid integer for estimated delivery.";
        }

        // Construct SQL query to insert new order into database
        stmt.str("");
        stmt << "Insert into purchases (book_id, sup_id, qty, dt_ordered, eta) values ( " << book_id << ", " << sup_id << ", " << qty << ", curdate(), Date_add(curdate(), INTERVAL " << eta << " DAY));";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to add new order!";
        }

        // Inform user that the new order has been added successfully
        cout << "New order Added!!";
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


void purchases::mark_reciv() {
    try {
        // Prompt user to enter the order ID for marking as received
        cout << "Enter the order id for order received : ";
        cin >> ord_id;
        if (cin.fail()) {
            throw "Invalid input! Please enter a valid integer for order id.";
        }

        // Construct SQL query to update purchase record to mark it as received
        stmt.str("");
        stmt << "Update purchases set received = 'T' where ord_id = " << ord_id << ";";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to mark order as received!";
        }

        // Inform user that the order has been successfully marked as received
        cout << "Received Marked successfully";
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

void purchases::mar_cancel() {
    try {
        // Prompt user to enter the order ID for marking as cancelled
        cout << "Enter the order id for order cancelled : ";
        cin >> ord_id;
        if (cin.fail()) {
            throw "Invalid input! Please enter a valid integer for order id.";
        }

        // Construct SQL query to update purchase record to mark it as cancelled
        stmt.str("");
        stmt << "Update purchases set received = 'C' where ord_id = " << ord_id << ";";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to mark order as cancelled!";
        }

        // Inform user that the order has been successfully marked as cancelled
        cout << "Cancelled Marked successfully";
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


void purchases::view() {
    try {
        int c;
        char received;

        // Display options for viewing orders
        cout << "Select an Option" << endl;
        cout << "1. View orders not Received" << endl;
        cout << "2. View orders Cancelled" << endl;
        cout << "3. View orders Received" << endl;
        cout << "Enter Your choice : ";
        cin >> c;

        // Validate user input and set 'received' flag accordingly
        if (c == 1)
            received = 'F';
        else if (c == 2)
            received = 'C';
        else if (c == 3)
            received = 'T';
        else
            return;

        // Construct SQL query to retrieve orders based on received status
        stmt.str("");
        stmt << "Select * from purchases where received = '" << received << "';";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to retrieve orders!";
        }

        // Store query result
        res_set = mysql_store_result(conn);

        // Display orders based on user's choice
        if (c == 1)
            cout << endl << "Orders not received are" << endl;
        else if (c == 2)
            cout << endl << "Orders Cancelled are" << endl;
        else if (c == 3)
            cout << endl << "Orders received are" << endl;

        // Output order details
        while ((row = mysql_fetch_row(res_set)) != NULL) {
            cout << endl;
            cout << "Order Id : " << row[0] << endl;
            cout << "Book Id : " << row[1] << endl;
            cout << "Supplier Id :" << row[2] << endl;
            cout << "Quantity : " << row[3] << endl;
            cout << "Date Ordered : " << row[4] << endl;
            cout << "Estimated Delivery date : " << row[5] << endl;
            cout << endl << endl << endl;
        }
        cout << endl << endl << endl << endl << endl;
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
