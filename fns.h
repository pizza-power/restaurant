#ifndef RESTAURANT_FNS_H
#define RESTAURANT_FNS_H

#endif //RESTAURANT_FNS_H

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

void print_menu(const std::vector<std::tuple<int, std::string, int>>& );
void quit_order();

// class to hold customer data, some of this stuff is currently held in the order object

class Customer {

    // futures attributes
    // std::vector order history?

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

Customer customer_creator();

class Order {

    char order_type;
    std::string orderNumber;
    std::vector<std::tuple<int, std::string, int>> order_items;
    Customer this_customer;

public:

    // Constructor
    Order(char new_order_type, std::string new_orderNumber, Customer this_customer);

    bool add_items(Order&, std::vector<std::tuple<int, std::string, int>>);
    void remove_item();
    void print_order(Customer);
};



// menu class with functions to print, add item to menu, remove item from menu, etc

