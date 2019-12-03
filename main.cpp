#include <iostream>
#include <tuple>

#include "mysqlx/xdevapi.h"
#include "customer.h"
#include "order.h"
#include "fns.h"
#include "menu.h"

int main() {

    // ask if it is carryout or delivery,
    // todo: this probably doesn't need to be here, could probably go into the order function
    char order_type;
    order_type = intro_routine();
    if (order_type == 'X' || (order_type == 'x')) {
        quit_order();
        return 0;
    }

    // todo: open a log file and log what the program is doing

    // create database connection
    mysqlx::Session mySession(mysqlx::SessionOption::HOST, "localhost",
                              mysqlx::SessionOption::PORT, 33060,
                              mysqlx::SessionOption::USER, "root",
                              mysqlx::SessionOption::PWD, "");
    mysqlx::Schema database = mySession.getSchema("restaurant");

    // load menu from the database
    Menu menu(database);

    // create a customer
    Customer customer(customer_creator(database));

    // create an order
    Order order(order_type, customer, menu, database);

    // add items to order
    while (order.create_order(menu.menu_items())) {

    }

    // print out the final order
    order.print_order(customer);

    // todo: get rid of this, move elsewhere, etc
    quit_order();

    // close the mysqlx session
    mySession.close();

    return 0;
}
