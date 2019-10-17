#include <iostream>
#include <vector>
#include <tuple>

#include "order.h"
#include "fns.h"
#include "menu.h"


// Order Constructor

Order::Order(char new_order_type, std::string new_orderNumber, Customer new_this_customer, Menu new_this_menu)
        :order_type(new_order_type), orderNumber(new_orderNumber), this_customer(new_this_customer), this_menu(new_this_menu) {}

//bool Order::add_items(Order& this_order, std::vector<std::tuple<int, std::string, int>> menu) {
bool Order::add_items(Order& this_order, std::vector<std::tuple<int, std::string, int>> menu) {

    /** probably need to add an option to add to an already existing order
    // could pass the existing order in as a reference, and then edit it
    // for now we won't do that
    // this function should probabbly not be a bool, it just doesn't seem right to be true or false
    // maybe add code to main so this function becomes void
    **/

    if (order_type == 'X') {
        quit_order();
        return false;
    }

    std::cout << "Press the number of the item that you would like to add to your order, or press "
                 "'X' to cancel your order, press 'M' to see the menu, or press 'D' when done. "<< std::endl;
    char pressed_key;
    std::cout << "Your choice: ";
    std::cin >> pressed_key;

    if (pressed_key == 'X') {
        quit_order();
        return false;
    } else if (pressed_key == 'M') {
        this_menu.print_menu(this_menu.menu_items);
        return true;
    } else if (pressed_key == 'D') {
        return false;
    } else {
        int item_number = pressed_key - '0';
        this_order.order_items.push_back(menu[item_number - 1]);

        return true;

    }
}

void Order::remove_item() {
    std::cout << "Please press the number of the item you want to remove: ";
    int pressed_key;
    std::cin >> pressed_key;

    // write routing to find this item in the order, count how many times it occurs and ask to remove how many
    // error check to non real item numbers etc


}

// print the order
void Order::print_order(Customer customer) {

    std::cout << "\nOrder Number: " << orderNumber << "\nC/O or Delivery: " << order_type
              << "\nCustomer Name: " << customer.first_name + " " + customer.last_name <<"\n\nCustomer Address: " <<
              customer.street_address + " " + customer.city + ", " + customer.state << std::endl;


    // update to use empty() instead of code below it, and a range based for loop
    if (order_items.empty()) {
        std::cout << "\nNO ITEMS IN ORDER" << std::endl;
    } else {
        std::cout << "\n\nITEM\tPRICE" << std::endl;
        for (auto i : order_items) {
            std::cout << std::get<1>(i) << "\t" << std::get<2>(i)<< std::endl;
        }

    }
    std::cout << "\n\n" << std::endl;
}