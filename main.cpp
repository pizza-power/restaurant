#include <iostream>
#include <tuple>

#include "customer.h"
#include "order.h"
#include "fns.h"
#include "menu.h"

int main() {

    char order_type;
    order_type = intro_routine();

    if (order_type == 'X') {
        quit_order();
        return 0;
    }
    // create new menu, use print menu
    Menu new_menu;

    // add items to the menu, this will be done on initial program boot by querying db
    new_menu.menu_items.emplace_back(std::make_tuple(1, "pizza", 999));
    new_menu.menu_items.emplace_back(std::make_tuple(2, "htodog", 299));
    new_menu.menu_items.emplace_back(std::make_tuple(3, "soda", 199));

    // create a customer
    Customer this_customer(customer_creator());

    // create an order, get orderNumber from DB?
    std::string orderNumber = "10021331";
    Order orderName(order_type, orderNumber, this_customer, new_menu);

    // add items to order
    while (orderName.add_items(orderName, new_menu.menu_items)) {
    }

    // print out the final order
    orderName.print_order(this_customer);

    quit_order();

    return 0;
}