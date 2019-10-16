#include <iostream>
#include <tuple>

#include "customer.h"
#include "order.h"
#include "fns.h"

int main() {
    // create the menu, this should be put in its own file
    std::vector<std::tuple<int, std::string, int>> menu;
    menu.push_back(std::make_tuple(1, "pizza", 999));
    menu.push_back(std::make_tuple(2, "hotdog", 299));
    menu.push_back(std::make_tuple(3, "drink", 199));

    // add this to "intro routine" or something
    std::cout << "\n\nWelcome to Matt's Pizza Palace!\n\nPress 'Y' or order or 'X' to cancel: ";
    char order_verify;
    std::cin >> order_verify;

    if (order_verify == 'Y'){
        std::cout << "\nWill this be for Carryout 'C' or Delivery 'D'? ";
        char order_type;
        std::cin >> order_type;

        // create a customer
        Customer this_customer(customer_creator());

        // create an order, get orderNumber from DB?
        std::string orderNumber = "10021331";
        Order orderName(order_type, orderNumber, this_customer);

        // add items to order
        while (orderName.add_items(orderName, menu)) {
        }

        // print out the final order
       orderName.print_order(this_customer);

    } else {
        quit_order();
        return 0;
    }

    return 0;
}