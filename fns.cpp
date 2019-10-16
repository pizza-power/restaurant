#include <iostream>
#include <string>
#include <vector>
#include <tuple>


#include "fns.h"

//print the menu
void print_menu(const std::vector<std::tuple<int, std::string, int>>& m) {
    for (auto i : m) {
        std::cout << std::get<0>(i) << " " <<  std::get<1>(i) << " " << std::get<2>(i) << std::endl;
    }
    std::cout << "\n\n" << std::endl;
}

// quit order function
void quit_order() {
    std::cout << "Thank you! Have a nice Day!\n\n\n\n" << std::endl;
}




