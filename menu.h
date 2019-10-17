#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

class Menu {

public:

    Menu();

    std::vector<std::tuple<int, std::string, int>> menu_items;

    void print_menu(const std::vector<std::tuple<int, std::string, int>>& );

    std::vector<std::tuple<int, std::string, int>> add_item(std::tuple<int, std::string, int>);

};

#endif //MENU_H