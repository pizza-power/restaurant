#ifndef CUSTOMER_H
#define CUSTOMER_H


#include <iostream>
#include <string>
#include <vector>
#include <tuple>

// class to hold customer data, some of this stuff is currently held in the order object

class Customer {

public:
    std::string first_name;
    std::string last_name;
    std::string street_address;
    std::string city;
    std::string state;

    //constructor
    Customer(std::string new_first_name, std::string new_last_name, std::string new_street_address,
             std::string new_city, std::string new_state);

    void change_info();

    void print_customer(const Customer&);

    void order_history();

};

#endif

Customer customer_creator();