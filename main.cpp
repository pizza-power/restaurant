#include <iostream>
#include <tuple>
#include <fstream>

#include "customer.h"
#include "order.h"
#include "fns.h"
#include "menu.h"

// TODO: overall todos; store monetary values as long doubles? will need to update menu functions, inventory, orders
// TODO: all inputs need validation/sanitization

int main() {

    // TODO: open a log file and log what the program is doing
    std::ofstream log ("log.log", std::ios::out | std::ios::app);
    if (log.is_open()) {
        log << "program initialized" << std::endl;
        log.close();
    }

    if (intro_routine()) {

        // create database connection
        // TODO: put in it's own class?
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
        Order order(customer, menu, database);

        // add items to order
        while (order.create_order(menu.menu_items())) {}

        // print out the final order
        // TODO: should print order go by order_id instead? probably want it to be sep function not depending on cust?
        order.print_order(customer);

        quit_order();

        // close the mysqlx session
        mySession.close();

    } else {
        quit_order();
    }
    return 0;
}
