//
// Created by user on 10/16/19.
//

#include "menu.h"

Menu::Menu()=default;

void Menu::print_menu(const std::vector<std::tuple<int, std::string, int>>& m) {

    for (auto i : m) {
        std::cout << "Item Number " << " Item " << " Price " << std::endl;
        std::cout << std::get<0>(i) << ")\t" <<  std::get<1>(i) << "\t " << std::get<2>(i) << std::endl;

    }
    std::cout << std::endl;
}