#include <iostream>
#include <tuple>

#include "mysqlx/xdevapi.h"
#include "customer.h"
#include "order.h"
#include "fns.h"
#include "menu.h"

int main() {
    char order_type;
    order_type = intro_routine();

    if (order_type == 'X' || (order_type == 'x')) {
        quit_order();
        return 0;
    }

    // create database connection
    mysqlx::Session mySession(mysqlx::SessionOption::HOST, "localhost",
                              mysqlx::SessionOption::PORT, 33060,
                              mysqlx::SessionOption::USER, "root",
                              mysqlx::SessionOption::PWD, "");
    mysqlx::Schema db = mySession.getSchema("restaurant");


    // create new menu, use print menu
    Menu new_menu(db);

    // old create a customer
    // Customer this_customer(customer_creator());
    // new create a customer, sends to db, should I lookup old customer?

    // create an order, get orderNumber from DB?
    std::string orderNumber = "10021331";
    Order orderName(order_type, orderNumber, this_customer, new_menu);

    // add items to order
    while (orderName.add_items(orderName, new_menu.menu_items())) {
    }

    // print out the final order
    orderName.print_order(this_customer);

    quit_order();

    return 0;
}
