#pragma once
// sales.h
// This file contains the declaration of the sales class and its methods.

#ifndef SALES_H
#define SALES_H

#include <iostream>
#include <mysql.h>
#include <sstream>

using namespace std;



// Database connection
#define HOST "127.0.0.1"
#define USER "root"
#define PASS "123456"
#define DATABASE "BookshopDB"
#define PORT 3306



class sales {
    int invoice_id;        // Primary key
    int member_id;         // FK ref member(id)
    int book_id;           // FK ref books(id)
    int qty;
    float amount;
    date date_of_sales;
public:
    // Constructor
    sales() {
        invoice_id = 0;
        member_id = 0;
        book_id = 0;
        qty = 0;
        amount = 0.00;
        // Assuming date() initializes to default value
        date_of_sales = date();
    }

    // Destructor
    ~sales() {
        cout << "sales object destroyed" << endl;
    }
    void add();            // Method to add a new sale
    void find_total_sales(); // Method to find total sales
};

#endif // SALES_H

// ------------------
// Sales functions
// ------------------

void sales::add() {
    try {
        // Prompt user to enter member ID, book ID, and quantity
        cout << "Enter Member id :";
        cin >> member_id;
        cout << "Enter the book id : ";
        cin >> book_id;
        cout << "Enter the quantity : ";
        cin >> qty;

        // Construct SQL query to calculate the bill amount based on book price and quantity
        stmt.str("");
        stmt << "select price*" << qty << " from books where id = " << book_id << ";";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to calculate the bill amount!";
        }

        // Store query result
        res_set = mysql_store_result(conn);

        // If book details are found, calculate the bill amount
        if ((row = mysql_fetch_row(res_set)) != NULL) {
            cout << "The bill amount : " << row[0] << endl << endl;
            amount = atoi(row[0]);
        }
        else {
            // If book ID is invalid, inform the user and return
            cout << "Book Id invalid!!" << endl;
            _getch();
            return;
        }

        // Construct SQL query to insert sales record into database
        stmt.str("");
        stmt << "insert into sales (member_id, book_id, qty, amount, date_of_sale) values (" << member_id << ", " << book_id << ", " << qty << ", " << amount << ", curdate());";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to insert sales record!";
        }

        // Fetching invoice ID
        stmt.str("");
        stmt << "select invoice_id from sales where member_id = " << member_id << " AND id = " << book_id << " AND qty = " << qty << " AND sales_date = curdate();";
        query = stmt.str();
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to fetch invoice ID!";
        }

        // Store query result
        res_set = mysql_store_result(conn);

        // If invoice ID is found, display it
        if ((row = mysql_fetch_row(res_set)) != NULL) {
            cout << "The Invoice id for the bill is " << row[0] << endl << endl << endl;
        }
        else {
            // If details entered are wrong, inform the user
            cout << "The entered details maybe wrong." << endl << "Please Recheck and Enter again" << endl << endl << endl;
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




void sales::find_total_sales() {
    try {
        // Construct SQL query to calculate total sales for the current year
        query = "select sum(amt) from sales where year(sales_date) = year(curdate());";
        q = query.c_str();

        // Execute SQL query
        if (mysql_query(conn, q) != 0) {
            throw "Failed to calculate total sales!";
        }

        // Store query result
        res_set = mysql_store_result(conn);

        // If total sales for the current year are found, display them
        if ((row = mysql_fetch_row(res_set)) != NULL) {
            cout << "Total sales this year : " << row[0] << endl << endl << endl << endl;
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
