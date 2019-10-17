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


// interactive function to build a customer
Customer customer_creator() {

    /** the menu and the menu printing needs to be moved elsewhere
     * the menu can go it it's own file, and then another function
     * can be used to print the menu
     */


    char pressed_key;

    std::string first_name;
    std::string last_name;
    std::string street_address;
    std::string city;
    std::string state;

    std::cout << "\nPlease enter your first and last name.\n" << std::endl;
    std::cout << "First Name: ";
    std::cin >> first_name;
    std::cout << "\nLast Name: ";
    std::cin >> last_name;
    std::cout << std::endl;

    std::cout << "\nPlease enter your street address: ";
    std::cin.ignore();
    getline(std::cin, street_address);

    std::cout << "\nPlease enter you city: ";

    getline(std::cin, city);

    std::cout << "\nPlease enter your state in two letter abbreviation form, please: ";
    std::cin >> state;
    std::cout << "\n" << std::endl;

    // create a customer object
    Customer thiscustomer(first_name, last_name, street_address, city, state);

//    // See the menu
//    std::cout << "Welcome " << first_name << "! ";
//    std::cout << "Press 'M' for the menu, or 'X' to Order: ";
//
//    std::cin >> pressed_key;
//
//    if (pressed_key == 'M') {
//        std::cout << "\n\nPrinting menu... \n" << std::endl; // move this to the function
//        menu.print_menu(menu.menu_items);
//        std::cout << "change this so menu is printed, may need to pass menu to function?" << std::endl;
//    } else if (pressed_key == 'X') {
//        quit_order();
//        return thiscustomer;
//    }
    return thiscustomer;

}