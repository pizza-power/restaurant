#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iomanip>      // std::put_time
#include <ctime>        // std::time_t, struct std::tm, std::localtime
#include <chrono>       // std::chrono::system_clock

#include "order.h"
#include "fns.h"
#include "menu.h"

// Order Constructor

Order::Order(char new_order_type, std::string new_orderNumber, Customer new_this_customer, Menu new_this_menu)
        :order_type(new_order_type), orderNumber(new_orderNumber), this_customer(new_this_customer), this_menu(new_this_menu) {}

bool Order::add_items(Order& this_order, std::vector<std::tuple<int, std::string, double>> menu) {

    /** probably need to add an option to add to an already eixisting order
    // could pass the existing order in as a reference, and then edit it
    // for now we won't do that
    // this function should probabbly not be a bool, it just doesn't seem right to be true or false
    // maybe add code to main so this function becomes void
    **/

    // more robust input checking is needed, then put all code below under if y, ternary expression?
    // if y or Y this or quit?

    if (order_type == 'X' || (order_type == 'x')) {
        quit_order();
        return false;
    }

    std::cout << "Please, choose from the following options.\n" << std::endl;
    std::cout << "1) Add items to your order.\n2) Remove an item from order.\n3) Cancel order.\n4) Complete order.\n" << std::endl;
    std::cout << "Your choice: ";
    int pressed_key;
    std::cin >> pressed_key;
    std::cout << std::endl;

    if (pressed_key == 1) {
        this_menu.print_menu();
        std::cout << "Enter the number of item you would like to order, or press 0 to exit: ";
        int item_number;
        std::cin >> item_number;

        while ((item_number <= menu.size()) && item_number > 0 ) {
            this_order.order_items.push_back(menu[item_number - 1]);
            std::cout << "\n" << std::get<1>(menu[item_number-1]) << " has been added successfully!\n" << std::endl;
            std::cout << "Please make another choice, or press 0 to exit: ";
            std::cin >> item_number;
        }
        return true;
    } else if (pressed_key == 2) {

        // if order empty return tru
        if (order_items.empty()) {
            std::cout << "No items to remove!\n" << std::endl;
            return true;
        }
        std::cout << "Your current order is: " << std::endl;
        std::cout << "\nITEM\tPRICE" << std::endl;
        int k = 1;
        for (auto i : order_items) {
            std::cout << k << ") " << std::get<1>(i) << "\t" << std::get<2>(i)<< std::endl;
            k += 1;
        }
        std::cout << "\n\nPress the number of the item you want to remove: ";
        int pressed_key;
        std::cin >> pressed_key;
        std::cout << pressed_key << std::endl;
        order_items.erase(order_items.begin()+pressed_key-1);
        return true;
    } else if (pressed_key == 3) {
        quit_order();
        return false;
    } else if (pressed_key == 4) {
        return false;
    }
        return true;
}
void Order::print_order(Customer customer) {
    std::cout << std::setfill ('x') << std::setw (80) << "\n" << std::endl;

    std::cout << "\nOrder Number: " << orderNumber << "\nC/O or Delivery: " << order_type
              << "\nCustomer Name: " << customer.first_name + " " + customer.last_name <<"\n\nCustomer Address: " <<
              customer.street_address + " " + customer.city + ", " + customer.state <<  "\n" << std::endl;

    using std::chrono::system_clock;
    std::time_t tt = system_clock::to_time_t (system_clock::now());

    struct std::tm * ptm = std::localtime(&tt);
    std::cout << std::put_time(ptm,"%c") << '\n';

    if (order_items.empty()) {
        std::cout << "\nNO ITEMS IN ORDER" << std::endl;
    } else {
        std::cout << "\n\nITEM\tPRICE" << std::endl;
        int j = 1;
        for (auto i : order_items) {
            std::cout << j << ") " << std::get<1>(i) << "\t" << std::get<2>(i)<< std::endl;
            j += 1;
        }

    }
    std::cout << "\n" << std::endl;
}
