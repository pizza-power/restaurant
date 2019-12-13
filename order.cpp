#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>
#include <string>
#include <ctime>        // std::time_t, struct std::tm, std::localtime
#include <chrono>        // std::chrono::system_clock

#include "order.h"
#include "fns.h"
#include "menu.h"
#include "include/mysqlx/xdevapi.h"


// Order Constructor

Order::Order(Customer new_customer, Menu new_menu, mysqlx::Schema new_database)
        :customer(new_customer), menu(new_menu), database(new_database) {}

bool Order::create_order(std::vector<std::tuple<int, std::string, double>> menu) {

    /*** this function returns a bool depending on if the order creation process is complete,
         the menu is stored as a vector of tuples and is passed as an argument

     ***/

     // TODO: input sanitization/validation, incorrect types and lengths
     // TODO: put this back in fns function? change intro function back to char?, don't really like that
     // TODO: change restaurant orders table order_type column to varchar

     if ((order_type != "C") & (order_type != "D")) {
         std::cout << "\nWill this be for Carryout 'C' or Delivery 'D'? ";
         std::string order_type;
         std::cin >> order_type;
         this->order_type = toupper(order_type[0]);
     }

    std::cout << "\nPlease, choose from the following options.\n" << std::endl;
    std::cout << "1) Add items to your order.\n2) Remove an item from order.\n3) Cancel order.\n4) Complete order.\n"
    << std::endl;
    std::cout << "Your choice: ";
    int pressed_key;
    std::cin >> pressed_key;
    std::cout << std::endl;

    if (pressed_key == 1) {
        this->menu.print_menu();
        std::cout << "Enter the number of item you would like to order, or press 0 to exit: ";
        int item_number;
        std::cin >> item_number;

        // update total cost of the order
        this->total_cost = this->total_cost + std::get<2>(menu[item_number -1]);

        // add items to the order
        while ((item_number <= int(menu.size())) && item_number > 0 ) {
            this->order_items.push_back(menu[item_number - 1]);
            std::cout << "\n" << std::get<1>(menu[item_number-1]) << " has been added successfully!\n" << std::endl;
            std::cout << "Please make another choice, or press 0 to exit: ";
            std::cin >> item_number;

            //update cost
            this->total_cost = this->total_cost + std::get<2>(menu[item_number -1]);
        }
        return true;
    } else if (pressed_key == 2) {
        // if order empty return true
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
        order_items.clear();
        if (order_items.empty()) {
            std::cout << "\nYour order has been cancelled!\n" << std::endl;
        }
        // reset cost to $0.00
        total_cost = 0.00;
        quit_order();
        return false;
    } else if (pressed_key == 4) {

        // get the previous order id in order to increment it by 1 later to make a new order id
        mysqlx::Table orders = database.getTable("orders");
        mysqlx::RowResult max_order_id_getter =  orders.select("id").orderBy("id DESC").execute();
        mysqlx::Row row;

        // if no order items, cost needs to be set to 0
        if (sizeof(order_items) == 0 ) {
            this->total_cost = 0.00;
        }

        // TODO: bug here, will crash if db has zero orders in it
        row = max_order_id_getter.fetchOne();
        int prev_max_order_id = row[0];
        int order_id = prev_max_order_id + 1;

        // get time to use as the order time in the database
        auto timenow =
                std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << ctime(&timenow) << std::endl;

        // add order to the restaurant db
        mysqlx::TableInsert(orders).values(0, order_id, customer.customer_id, ctime(&timenow),
                this->total_cost, order_type).execute();

        // add order items to the order items table
        mysqlx::Table order_items_table = database.getTable("order_items");
        for (auto item : order_items) {
            mysqlx::TableInsert(order_items_table).values(0, order_id , std::get<1>(item), std::get<0>(item), 1).execute();
        }
        return false;
    }
    return true;
}

void Order::print_order(Customer& customer) {
    std::cout << std::setfill ('x') << std::setw (80) << "\n" << std::endl;

    // TODO: get order id instead of 89876
    std::cout << "\nOrder Number: " <<  89876 << "\nC/O or Delivery: " << order_type
              << "\nCustomer Name: " << customer.first_name + " " + customer.last_name <<"\n\nCustomer Address: " <<
              customer.street_address + " " + customer.city + ", " + customer.state <<  "\n" << std::endl;

    auto timenow =
            std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << ctime(&timenow) << std::endl;

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
    // TODO: precision on cost output
    double FOOD_AND_DRINK_TAXRATE = 1.02;           // 2% food and drink tax rate
    std::cout << "\nTotal Cost: " << this->total_cost * FOOD_AND_DRINK_TAXRATE << std::endl;
    std::cout << "\n" << std::endl;
}

// TODO: implement
//int Order::order_id_getter() {}
void Order::cancel_order() {}
void Order::modify_order() {}
void Order::submit_order() {}

