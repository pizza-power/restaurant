#include <iostream>
#include <vector>
#include <tuple>

#include "customer.h"
#include "fns.h"

// customer class and member functions

Customer::Customer(std::string new_first_name, std::string new_last_name, std::string new_street_address,
                   std::string new_city, std::string new_state)
        : first_name(new_first_name), last_name(new_last_name), street_address(new_street_address),
          city(new_city), state(new_state) {}


void Customer::print_customer(const Customer& this_customer) {

    std::cout << first_name + " " +  last_name + "\n" + street_address + " " + city + ", " + state << std::endl;

}

// build the customer object
Customer customer_creator() {

    /** the menu and the menu printing needs to be moved elsewhere
     * the menu can go it it's own file, and then another function
     * can be used to print the menu
     */

    std::string first_name;
    std::string last_name;
    std::string street_address;
    std::string city;
    std::string state;
    std::string zip;

    std::cout << "\nPlease enter your first and last name.\n" << std::endl;
    std::cout << "First Name: ";
    std::cin >> first_name;
    std::cout << "\nLast Name: ";
    std::cin >> last_name;
    std::cout << std::endl;

    std::cout << "Please enter your street address: ";
    std::cin.ignore();
    getline(std::cin, street_address);

    std::cout << "\nPlease enter your city: ";
    getline(std::cin, city);

    std::cout << "\nPlease enter your state in two letter abbreviation form: ";
    std::cin >> state;

    std::cout << "\nPlease enter your zip code: ";
    std::cin >> zip;

    std::cout << "\n" << std::endl;

    // create a customer object
    Customer thiscustomer(first_name, last_name, street_address, city, state);

    return thiscustomer;

}