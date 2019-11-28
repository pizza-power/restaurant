
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "customer.h"
#include "menu.h"

class Order {

    char order_type;
    std::string orderNumber;
    std::vector<std::tuple<int, std::string, int>> order_items;
    Customer this_customer;
    Menu this_menu;

public:

    // Constructor
    Order(char new_order_type, std::string new_orderNumber, Customer this_customer, Menu this_menu);

    bool add_items(Order&, std::vector<std::tuple<int, std::string, int>>);
    //void remove_item(Order&, int&, std::vector<std::tuple<int, std::string, int>>);
    void print_order(Customer);
};
