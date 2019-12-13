
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "customer.h"
#include "menu.h"

class Order {

    std::string order_type;
    // std::string orderNumber;
    std::vector<std::tuple<int, std::string, double>> order_items;
    Customer customer;
    Menu menu;
    double total_cost;
    mysqlx::Schema database;

public:

    // Constructor
    Order(Customer this_customer, Menu this_menu, mysqlx::Schema database);

    bool create_order(std::vector<std::tuple<int, std::string, double>>);
    void print_order(Customer&);
    void cancel_order();
    void modify_order();
    void submit_order();

};