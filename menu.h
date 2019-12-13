#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "include/mysqlx/xdevapi.h"

class Menu {

public:

    mysqlx::Schema database;

    Menu(mysqlx::Schema database);

    std::vector<std::tuple<int, std::string, double>> menu_items();

    void print_menu();

};

#endif //MENU_H