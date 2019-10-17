//
// Created by user on 10/16/19.
//

#include "menu.h"

Menu::Menu()=default;


void Menu::print_menu(const std::vector<std::tuple<int, std::string, int>>& m) {
    for (auto i : m) {
        std::cout << std::get<0>(i) << " " <<  std::get<1>(i) << " " << std::get<2>(i) << std::endl;
    }
    std::cout << "\n\n" << std::endl;
}

