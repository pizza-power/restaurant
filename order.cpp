#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <string>
#include <ctime>        // std::time_t, struct std::tm, std::localtime
#include <chrono>       // std::chrono::system_clock

#include "order.h"
#include "fns.h"
#include "menu.h"
#include "mysqlx/xdevapi.h"

// Order Constructor

Order::Order(char new_order_type, Customer new_customer, Menu new_menu, mysqlx::Schema new_database)
        :order_type(new_order_type), customer(new_customer), menu(new_menu),
        database(new_database) {}

bool Order::create_order(std::vector<std::tuple<int, std::string, double>> menu) {

    // get the previous order id in order to increment it by 1 later to make a new order id
    mysqlx::Table orders = this->database.getTable("orders");
    mysqlx::RowResult max_order_id_getter =  orders.select("id").orderBy("id DESC").execute();
    mysqlx::Row row;

    // todo: bug here, will crash if db has zero orders in it
    row = max_order_id_getter.fetchOne();
    int prev_max_order_id = row[0];
    if (order_type == 'X' || (order_type == 'x')) {
        quit_order();
        return false;
    }

    std::cout << "Please, choose from the following options.\n" << std::endl;
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

        while ((item_number <= menu.size()) && item_number > 0 ) {
            this->order_items.push_back(menu[item_number - 1]);
            std::cout << "\n" << std::get<1>(menu[item_number-1]) << " has been added successfully!\n" << std::endl;
            std::cout << "Please make another choice, or press 0 to exit: ";
            std::cin >> item_number;

            //update cost
            this->total_cost = this->total_cost + std::get<2>(menu[item_number -1]);

            // if you press 0 it goes back to the start of this fucntion so that is undeeded probably
            // could this be done recursively

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
        // if the order is quit, then the row int he table should be deleted, or else you could automate an
        // endless order loop where you add items and the quit and this would DOS app
        quit_order();
        return false;
    } else if (pressed_key == 4) {
        // so we need to go back and update the customer id in the db

        // can skip this if customer id is modifed up front then just use customer.id here
        std::cout << customer.phone_number << std::endl;

        auto timenow =
                std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << ctime(&timenow) << std::endl;
        
        // add order to the restaurant db
        mysqlx::TableInsert(orders).values(0, prev_max_order_id + 1, customer.customer_id, ctime(&timenow), this->total_cost,
                                           this->order_type).execute();
        return false;
    }

    return true;
}

void Order::print_order(Customer& customer) {
    std::cout << std::setfill ('x') << std::setw (80) << "\n" << std::endl;

    // get order id instead of 89876
    std::cout << "\nOrder Number: " << 89876 << "\nC/O or Delivery: " << order_type
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
    // food and drink tax rate 0.02
    std::cout << "Total Cost: " << this->total_cost * 1.02 << std::endl;
    std::cout << "\n" << std::endl;
}

// to be implemented;
void Order::cancel_order() {}
void Order::modify_order() {}
void Order::submit_order() {}

