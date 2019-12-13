#ifndef CUSTOMER_H
#define CUSTOMER_H


#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "include/mysqlx/xdevapi.h"

// class to hold customer data, some of this stuff is currently held in the order object

class Customer {

public:
    //constructor
    Customer(int customer_id, std::string phone_number, std::string new_first_name, std::string new_last_name,
            std::string new_street_address, std::string new_city, std::string new_state, std::string zip_code,
            std::string username, std::string password, mysqlx::Schema database);

    static void print_customer();
    static void change_customer_info();
    static void customer_order_history();


    int customer_id;
    std::string phone_number = "";
    std::string first_name = "";
    std::string last_name = "";
    std::string street_address = "";
    std::string city = "";
    std::string state = "";
    std::string zip_code = "";

private:
    std::string username = first_name + last_name;
    std::string password = "password";
    mysqlx::Schema database;
};

Customer customer_creator(mysqlx::Schema& database);
bool customer_lookup(std::string& phone_number, mysqlx::Schema& database);

#endif