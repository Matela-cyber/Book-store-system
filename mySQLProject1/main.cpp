// +----------------------------------+
// |          HEADER FILES            |
// +----------------------------------+
#include <windows.h>
#include <iostream>
#include <windows.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql.h>
#include <sstream>
#include <conio.h>


#include "suppliers.h"
#include "purchases.h"
#include "employees.h"
#include "members.h"
#include "sales.h"

// Database connection
#define HOST "127.0.0.1"
#define USER "root"
#define PASS "123456"
#define DATABASE "BookshopDB"
#define PORT 3306


using namespace std;


// my_bool result;


// +---------------------------+
// | Functions  prototypes     |
// +---------------------------+

void book_menu();
void sup_menu();
void pur_menu();
void emp_menu();
void mem_menu();
void sal_menu();
bool login();
void authentication();
void main_menu();




// +------------------------------+
// |		Main Function 	      |
// +------------------------------+

int main() {
    authentication();
    system("cls");
    try {
        // Attempt to establish a connection to the database
        conn = mysql_init(0);
        if (conn == nullptr) {
            throw runtime_error("Error initializing MySQL connection.");
        }

        conn = mysql_real_connect(conn, HOST, USER, PASS, DATABASE, PORT, NULL, 0);
        if (conn == nullptr) {
            throw runtime_error("Error connecting to database.");
        }

        // Database connection successful, proceed with the program logic
        int choice;
        while (true) {
            system("cls");
            
            main_menu();
        }
    }
    catch (const exception& e) {
        cout << "Exception occurred: " << e.what() << endl;
        cout << "Contact Tech Expert." << endl;
        _getch();
    }

    return 0;
}
// +--------------------------------------+
// | menus definations and other function |
// +--------------------------------------+

bool login() {
    string password;
    cout << "Enter password: ";
    cin >> password;
    return password == "123456";

}

 void authentication() {
    while (login()==0) {
        system("cls");
        cout << "login unssuccess try 123456" << endl;
        bool login();

    }
}

// main menu

void main_menu()
{
    int c;
    cout << "*************************************************" << endl;
    cout << "         BOOKSHOP MANGEMENT SYSTEM" << endl;
    cout << "*************************************************" << endl;
    cout << "   1. BOOKS" << endl;
    cout << "   2. SUPPLIERS" << endl;
    cout << "   3. PURCHASES" << endl;
    cout << "   4. EMPLOYEES" << endl;
    cout << "   5. MEMBERS" << endl;
    cout << "   6. SALES" << endl;
    cout << "   7. EXIT" << endl << endl << endl;
    cout << "Enter Your Choice : ";
    cin >> c;
    switch (c)
    {
    case 1:
        system("cls");
        book_menu();
        _getch();
        break;
    case 2:
        system("cls");
        sup_menu();
        _getch();
        break;
    case 3:
        system("cls");
        pur_menu();
        _getch();
        break;
    case 4:
        system("cls");
        emp_menu();
        _getch();
        break;
    case 5:
        system("cls");
        mem_menu();
        _getch();
        break;
    case 6:
        system("cls");
        sal_menu();
        _getch();
        break;
    case 7:
        exit(1);
        default:
        system("cls");
        cout << "Wrong Input" << endl << endl << "Invalid input";
        _getch();
        break;
    }
    return;
}

// book menu

void book_menu()
{
    int c;
    books b;
    cout << "*************************************************" << endl;
    cout << "                  BOOK MENU" << endl;
    cout << "*************************************************" << endl;
    cout << "   1. ADD" << endl;
    cout << "   2. UPDATE PRICE" << endl;
    cout << "   3. SEARCH" << endl;
    cout << "   4. UPDATE STATUS" << endl;
    cout << "   5. DISPLAY ALL" << endl;
    cout << "   6. RETURN TO MAIN MENU" << endl << endl << endl;
    cout << "Enter Your Choice : ";
    cin >> c;
    switch (c)
    {
    case 1:
        b.add();
        break;
    case 2:
        b.update_price();
        break;
    case 3:
        b.search();
        break;
    case 4:
        b.update();
        break;
    case 5:
        b.display();
        break;
    case 6:
        return;
        break;
    default:
        cout << "Wrong Input" << endl << "Invalid input";
        break;
    }
    return;
}

// supp menu

void sup_menu()
{
    int c;
    suppliers s;
    cout << "*************************************************" << endl;
    cout << "                SUPPLIER MENU" << endl;
    cout << "*************************************************" << endl;
    cout << "   1. ADD" << endl;
    cout << "   2. REMOVE" << endl;
    cout << "   3. SEARCH" << endl;
    cout << "   4. RETURN TO MAIN MENU" << endl << endl << endl;
    cout << "Enter Your Choice : ";
    cin >> c;
    switch (c)
    {
    case 1:
        s.add_sup();
        break;
    case 2:
        s.remove_supplier();
        break;
    case 3:
        s.search_id();
        break;
    case 4:
        return;
    default:
        cout << "Wrong Input" << endl << "Invalid input";
        break;
    }
}

// purchase menu

void pur_menu()
{
    int c;
    purchases p;
    cout << "*************************************************" << endl;
    cout << "                PURCHASES MENU" << endl;
    cout << "*************************************************" << endl;
    cout << "   1. New Order" << endl;
    cout << "   2. View All" << endl;
    cout << "   3. Cancel Order" << endl;
    cout << "   4. Recieved Order" << endl;
    cout << "   5. RETURN TO MAIN MENU" << endl << endl << endl;
    cout << "Enter Your Choice : ";
    cin >> c;
    switch (c)
    {
    case 1:
        p.new_ord();
        break;
    case 2:
        p.view();
        break;
    case 3:
        p.mar_cancel();
        break;
    case 4:
        p.mark_reciv();
        break;
    case 5:
        return;
    default:
        cout << "Wrong Input" << endl << "Invalid input";
        break;
    }
}

// emp_menu

void emp_menu()
{
    int c;
    employees e;
    cout << "*************************************************" << endl;
    cout << "                 EMPLOYEE MENU" << endl;
    cout << "*************************************************" << endl;
    cout << "   1. New Employee" << endl;
    cout << "   2. Search Employee" << endl;
    cout << "   3. Assign Manager" << endl;
    cout << "   4. View All" << endl;
    cout << "   5. Update Salary" << endl;
    cout << "   6. RETURN TO MAIN MENU" << endl << endl << endl;
    cout << "Enter Your Choice : ";
    cin >> c;
    switch (c)
    {
    case 1:
        e.add_emp();
        break;
    case 2:
        e.search_emp();
        break;
    case 3:
        e.assign_mgr_stat();
        break;
    case 4:
        e.display();
        break;
    case 5:
        e.update_sal();
        break;
    case 6:
        return;
    default:
        cout << "Wrong Input" << endl << "Invalid input";
        break;
    }
}


// mem menu

void mem_menu()
{
    int c;
    members m;
    m.refresh();
    cout << "*************************************************" << endl;
    cout << "                 MEMBERS MENU" << endl;
    cout << "*************************************************" << endl;
    cout << "   1. New Member" << endl;
    cout << "   2. Search Member" << endl;
    cout << "   3. RETURN TO MAIN MENU" << endl << endl << endl;
    cout << "Enter Your Choice : ";
    cin >> c;
    switch (c)
    {
    case 1:
        m.add_mem();
        break;
    case 2:
        m.search_mem();
        break;
    case 3:
        return;
    default:
        cout << "Wrong Input" << endl << "Invalid input";
        break;
    }
}

// sal_menu

void sal_menu()
{
    int c;
    sales s;
    cout << "*************************************************" << endl;
    cout << "                 SALES MENU" << endl;
    cout << "*************************************************" << endl;
    cout << "   1. Add New Bill" << endl;
    cout << "   2. Total Sales Of The Year" << endl;
    cout << "   3. RETURN TO MAIN MENU" << endl << endl << endl;
    cout << "Enter Your Choice : ";
    cin >> c;
    switch (c)
    {
    case 1:
        s.add();
        break;
    case 2:
        s.find_total_sales();
        break;
    case 3:
        return;
    default:
        cout << "Wrong Input" << endl << "Invalid input";
        break;
    }
}

